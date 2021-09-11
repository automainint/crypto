cmake_minimum_required(VERSION 3.18)

# Allow to set up the options for the dependencies.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Allow to specify the MSVC runtime library for the dependencies.
set(CMAKE_POLICY_DEFAULT_CMP0091 NEW)

option(CRYPTO_ENABLE_EXE      "Enable executable"         ON)
option(CRYPTO_ENABLE_TESTING  "Enable testing"            OFF)
option(CRYPTO_ENABLE_COVERAGE "Enable coverage reporting" OFF)

set(CRYPTO_PROJECT    crypto)
set(CRYPTO_EXE        crypto)
set(CRYPTO_CONFIG     crypto-config)
set(CRYPTO_UNITTESTS  crypto-unittests)

set(CMAKE_CXX_STANDARD 20)

project(
  ${CRYPTO_PROJECT}
    VERSION 0.1.1
    DESCRIPTION "C++ project template."
    LANGUAGES CXX
)

include(cmake/fetch-deps.cmake)

if(CRYPTO_ENABLE_EXE)
  include(cmake/config.cmake)

  add_executable(${CRYPTO_EXE})
  add_subdirectory(source)

  target_compile_features(${CRYPTO_EXE} PRIVATE cxx_std_20)

  if(MSVC)
    target_link_options(${CRYPTO_EXE} PRIVATE "/SUBSYSTEM:CONSOLE")
  endif()

  target_link_libraries(
    ${CRYPTO_EXE}
      ${CRYPTO_CONFIG} gtest
  )

  if(CRYPTO_ENABLE_TESTING OR CRYPTO_ENABLE_COVERAGE)
    enable_testing()

    add_test(
      NAME ${CRYPTO_UNITTESTS}
      COMMAND ${CRYPTO_EXE}
    )

    set_tests_properties(
      ${CRYPTO_UNITTESTS}
        PROPERTIES
          TIMEOUT "40"
    )
  endif()
endif()

include(GNUInstallDirs)
