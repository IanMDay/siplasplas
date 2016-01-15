#ifndef SIPLASPLAS_UTILITY_PREPROCESSOR_HPP
#define SIPLASPLAS_UTILITY_PREPROCESSOR_HPP

#define SIPLASPLAS_PP_IMPL_CAT(x, y) x ## y
#define SIPLASPLAS_PP_CAT(x, y) SIPLASPLAS_PP_IMPL_CAT(x, y)

#define SIPLASPLAS_PP_IMPL_STR(x) #x
#define SIPLASPLAS_PP_STR(x) SIPLASPLAS_PP_IMPL_STR(x)

#endif // SIPLASPLAS_UTILITY_PREPROCESSOR_HPP
