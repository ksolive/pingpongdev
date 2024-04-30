# Copyright (c) Open Enclave SDK contributors.
# Licensed under the MIT License.
add_custom_command(
  OUTPUT er_u.h er_u.c er_args.h
  DEPENDS ${CMAKE_SOURCE_DIR}/er.edl
  COMMAND
    openenclave::oeedger8r --untrusted ${CMAKE_SOURCE_DIR}/er.edl
    --search-path ${OE_INCLUDEDIR} --search-path
    ${OE_INCLUDEDIR}/openenclave/edl/sgx)

add_executable(er_host host.cpp
                               ${CMAKE_CURRENT_BINARY_DIR}/er_u.c)

if (WIN32)
  copy_oedebugrt_target(helloworld_host_oedebugrt)
  add_dependencies(helloworld_host helloworld_host_oedebugrt)
endif ()

target_include_directories(
  er_host PRIVATE # Needed for the generated file helloworld_u.h
                          ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(er_host openenclave::oehost)
