set(CMAKE_MODULE_PATH "${CONAN_CMAKE_MODULE_PATH}")
find_package(Protobuf ${SIPLAPSLAS_PROTOBUF_VERSION} REQUIRED)

add_conan_library(protobuf)

function(add_protobuf_library NAME)
    cmake_parse_arguments(
        PROTO
        "SHARED"
        ""
        "SOURCES"
        ${ARGN}
    )

    if(NOT PROTO_SOURCES)
        message(FATAL_ERROR "No sources given for the protobuf library '${NAME}'")
    endif()

    if(PROTO_SHARED)
        set(sharedLib SHARED)
    endif()

    protobuf_generate_cpp(sources headers ${PROTO_SOURCES})
    add_library(${NAME} ${sources} ${headers} ${sharedLib})
    if(NOT MSVC)
        target_compile_options(${NAME} PRIVATE -std=c++11)
    endif()
    target_link_libraries(${NAME} PUBLIC protobuf-conan)
    target_include_directories(${NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")

    message(STATUS "SIPLASPLAS PROTOBUF LIBRARY ${NAME}")
endfunction()
