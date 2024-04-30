# # Copyright (c) Open Enclave SDK contributors.
# # Licensed under the MIT License.

# # Use the edger8r to generate C bindings from the EDL file.
# cmake_minimum_required(VERSION 3.11)

# add_custom_command(
#   OUTPUT er_t.h er_t.c er_args.h
#   DEPENDS ${CMAKE_SOURCE_DIR}/er.edl
#   COMMAND
#     openenclave::oeedger8r --trusted ${CMAKE_SOURCE_DIR}/er.edl
#     --search-path ${OE_INCLUDEDIR} --search-path
#     ${OE_INCLUDEDIR}/openenclave/edl/sgx)

# # TODO 
# add_library(oht INTERFACE)
# # set_property(TARGET oht PROPERTY CXX_STANDARD 11)
# target_include_directories(oht INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
# find_library(OPENSSL_CRYPTO_LIBRARY NAMES libcrypto.so HINTS /usr/local/lib64 REQUIRED)
# message(STATUS "OPENSSL_CRYPTO_LIBRARY: ${OPENSSL_CRYPTO_LIBRARY}")
# find_path(OPENSSL_INCLUDE_DIR openssl/evp.h HINTS /usr/local/include/)
# message(STATUS "OPENSSL_INCLUDE_DIR: ${OPENSSL_INCLUDE_DIR}")
# include_directories(${OPENSSL_INCLUDE_DIR})

# target_compile_options(oht INTERFACE -mavx2)
# target_compile_definitions(
#   oht INTERFACE
#   OHT_SNOOPY_AVX2=1
#   OHT_OBLSORT_STD_MULTITHREAD=1
# )
# # 

# add_executable(enclave 
#   enc.cpp 
#   ${CMAKE_CURRENT_BINARY_DIR}/er_t.c
#   oht_crypto_impl.cpp # TODO
#   snoopy_par_obl_primitives_impl.cpp # TODO
# )

# if (WIN32)
#   maybe_build_using_clangw(enclave)
# endif ()

# target_compile_definitions(enclave PUBLIC OE_API_VERSION=2)
# target_compile_features(enclave PUBLIC cxx_std_17)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
# # Need for the generated file helloworld_t.h
# target_include_directories(enclave PUBLIC ${CMAKE_CURRENT_BINARY_DIR})


# if (LVI_MITIGATION MATCHES ControlFlow)
#   # Helper to enable compiler options for LVI mitigation.
#   apply_lvi_mitigation(enclave)
#   # Link against LVI-mitigated libraries.
#   target_link_libraries(
#     enclave openenclave::oeenclave-lvi-cfg
#     openenclave::oecrypto${OE_CRYPTO_LIB}-lvi-cfg openenclave::oelibc-lvi-cfg
#     oht
#     ${OPENSSL_CRYPTO_LIBRARY}
#     openenclave::oeenclave
#     openenclave::oecrypto${OE_CRYPTO_LIB}
#     openenclave::oelibcxx
#   )
# else ()
#   target_link_libraries(
#     enclave openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB}
#     openenclave::oelibc
#     oht
#     ${OPENSSL_CRYPTO_LIBRARY}
#     openenclave::oeenclave
#     openenclave::oecrypto${OE_CRYPTO_LIB}
#     openenclave::oelibcxx
#   )
# endif ()

# # # new
# # cmake_minimum_required(VERSION 3.11)
# # project(er)

# # find_package(OpenEnclave CONFIG REQUIRED)

# # add_executable(er enc.cpp)
# # target_link_libraries(enclave PRIVATE openenclave::oeenclave)
# # set_property(TARGET enclave PROPERTY CXX_STANDARD 17)

# ____________________________________________________________

add_custom_command(
  OUTPUT er_t.h er_t.c er_args.h
  DEPENDS ${CMAKE_SOURCE_DIR}/er.edl
  COMMAND
    openenclave::oeedger8r --trusted ${CMAKE_SOURCE_DIR}/er.edl
    --search-path ${OE_INCLUDEDIR} --search-path
    ${OE_INCLUDEDIR}/openenclave/edl/sgx)

add_executable(enclave 
  enc.cpp 
  ${CMAKE_CURRENT_BINARY_DIR}/er_t.c
  oht_crypto_impl.cpp # TODO
  snoopy_par_obl_primitives_impl.cpp # TODO
)

if (WIN32)
  maybe_build_using_clangw(enclave)
endif ()
# find_package(OpenSSL REQUIRED)

target_compile_definitions(enclave 
  PUBLIC 
  OE_API_VERSION=2
  OHT_SNOOPY_AVX2=1  
  OHT_OBLSORT_STD_MULTITHREAD=1
)


# Need for the generated file er_t.h
target_include_directories(enclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(enclave PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

if (LVI_MITIGATION MATCHES ControlFlow)
  # Helper to enable compiler options for LVI mitigation.
  apply_lvi_mitigation(enclave)
  # Link against LVI-mitigated libraries.
  target_link_libraries(
    enclave 
    PUBLIC
    openenclave::oeenclave-lvi-cfg
    openenclave::oecrypto${OE_CRYPTO_LIB}-lvi-cfg openenclave::oelibc-lvi-cfg
    openenclave::oelibcxx
    INTERFACE
    # OpenSSL::Crypto
    # dl
  )
else ()
  target_link_libraries(
    enclave 
    PUBLIC
    openenclave::oeenclave openenclave::oecrypto${OE_CRYPTO_LIB}
    openenclave::oelibc
    openenclave::oelibcxx
    INTERFACE
    # OpenSSL::Crypto
  )
endif ()