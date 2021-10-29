target_sources(
  ${CRYPTO_EXE}
    PRIVATE
      c_integer.cpp main.cpp
    PUBLIC
      integer.h
)
