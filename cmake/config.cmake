find_package(Threads REQUIRED)

add_library(${CRYPTO_CONFIG} INTERFACE)

if(WIN32)
  target_compile_definitions(${CRYPTO_CONFIG} INTERFACE _CONSOLE _UNICODE UNICODE)
endif()

target_link_libraries(${CRYPTO_CONFIG} INTERFACE Threads::Threads)

if(CRYPTO_ENABLE_COVERAGE)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CRYPTO_CONFIG} INTERFACE -O0 -g --coverage)
    target_link_options(${CRYPTO_CONFIG} INTERFACE --coverage)
  endif()
elseif(CRYPTO_ENABLE_TESTING)
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CRYPTO_CONFIG} INTERFACE -O0)
  elseif(MSVC)
    target_compile_options(${CRYPTO_CONFIG} INTERFACE /Od)
  endif()
else()
  if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${CRYPTO_CONFIG} INTERFACE -O3)
  elseif(MSVC)
    target_compile_options(${CRYPTO_CONFIG} INTERFACE /O2)
  endif()
endif()