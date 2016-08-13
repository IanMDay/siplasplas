#ifndef SIPLASPLAS_UTILITY_MEMORY_MANIP_HPP
#define SIPLASPLAS_UTILITY_MEMORY_MANIP_HPP

#include <memory>
#include <siplasplas/utility/export.hpp>

namespace cpp
{
    namespace detail
    {
        /**
         * \ingroup utility
         * \brief Returns an address aligned to an specific boundary
         *
         * \param pointer Starting address
         * \param alignment Alignment boundary. Must be a power of two
         *
         * \returns The next (upper) address from the given address that's aligned
         * to the required boundary
         */
        SIPLASPLAS_UTILITY_EXPORT char* aligned_ptr(char* pointer, std::size_t alignment);

        /**
         * \ingroup utility
         * \brief Returns an address aligned to an specific boundary
         *
         * \param pointer Starting address
         * \param alignment Alignment boundary. Must be a power of two
         *
         * \returns The next (upper) address from the given address that's aligned
         * to the required boundary
         */
        SIPLASPLAS_UTILITY_EXPORT void* aligned_ptr(void* pointer, std::size_t alignment);

        /**
         * \ingroup utility
         * \brief Checks if an address is aligned to a given boundary
         *
         * \param pointer Address to check
         * \param alignment Required alignment. Must be a power of two
         *
         * \returns true if \p pointer is aligned to \p alignment boundary. False otherwise.
         */
        SIPLASPLAS_UTILITY_EXPORT bool is_aligned(char* pointer, std::size_t alignment);

        /**
         * \ingroup utility
         * \brief Checks if an address is aligned to a given boundary
         *
         * \param pointer Address to check
         * \param alignment Required alignment. Must be a power of two
         *
         * \returns true if \p pointer is aligned to \p alignment boundary. False otherwise.
         */
        SIPLASPLAS_UTILITY_EXPORT bool is_aligned(void* pointer, std::size_t alignment);

        template<typename T>
        void write_at(char* pointer, const T& value, std::intptr_t offset = 0)
        {
            *(reinterpret_cast<T*>(pointer) + offset) = value;
        }

        template<typename T>
        void write_at(void* pointer, const T& value, std::intptr_t offset = 0)
        {
            write_at(reinterpret_cast<char*>(pointer), value, offset);
        }

        template<typename T>
        T read_at(const char* pointer, std::intptr_t offset = 0)
        {
            return *(reinterpret_cast<const T*>(pointer + offset));
        }

        template<typename T>
        T read_at(const void* pointer, std::intptr_t offset = 0)
        {
            return read_at<T>(reinterpret_cast<const char*>(pointer), offset);
        }

        template<typename T>
        void write_before(char* pointer, const T& value)
        {
            write_at(pointer, value, -sizeof(T));
        }

        template<typename T>
        void write_before(void* pointer, const T& value)
        {
            write_before(reinterpret_cast<char*>(pointer), value);
        }

        template<typename T>
        T read_before(const char* pointer)
        {
            return read_at<T>(pointer, - sizeof(T));
        }

        template<typename T>
        T read_before(const void* pointer)
        {
            return read_before<T>(reinterpret_cast<const char*>(pointer));
        }

        template<typename T>
        class RawReaderWriter
        {
        public:
            RawReaderWriter(void* at) :
                _at{reinterpret_cast<char*>(at)}
            {}

            T get() const
            {
                return detail::read_at<T>(_at);
            }

            operator T() const
            {
                return get();
            }

            T operator=(T value)
            {
                detail::write_at(_at, value);
                return value;
            }
        private:
            char* _at;
        };
    }
}

#endif // SIPLASPLAS_UTILITY_MEMORY_MANIP_HPP

