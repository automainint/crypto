/*  test/unittests/c_integer.test.cpp
 *
 *  Copyright (c) 2021 Mitya Selivanov
 */

#include "../../crypto/integer.h"
#include <gtest/gtest.h>

namespace crypto::test {
  TEST(integer, empty) {
    auto i = integer<16> {};
    EXPECT_EQ(i.to_int64(), 0);
    EXPECT_DOUBLE_EQ(i.to_double(), .0);
  }

  TEST(integer, from_zero) {
    auto a = integer<16>::from_int64(0);
    auto b = integer<16>::from_double(.0);
  }

  TEST(integer, from_int) {
    EXPECT_EQ(integer<16>::from_int64(123456789).to_int64(),
              123456789);
  }

  TEST(integer, from_double) {
    EXPECT_DOUBLE_EQ(integer<16>::from_double(123456789.).to_double(),
                     123456789.);
  }

  TEST(integer, add_zero) {
    EXPECT_EQ(integer<16> {}.add(integer<16> {}).to_int64(), 0);
  }

  TEST(integer, sub_zero) {
    EXPECT_EQ(integer<16> {}.subtract(integer<16> {}).to_int64(), 0);
  }

  TEST(integer, bit_not) {
    EXPECT_EQ(
        integer<16> {}.from_uint64(0xf0f0).bit_not().to_uint64() &
            0xffff,
        0xf0f);
  }

  TEST(integer, bit_and) {
    EXPECT_EQ(integer<16> {}
                  .from_uint64(0xf0f0)
                  .bit_and(integer<16> {}.from_uint64(0x00ff))
                  .to_uint64(),
              0xf0);
  }

  TEST(integer, bit_or) {
    EXPECT_EQ(integer<16> {}
                  .from_uint64(0xf0f0)
                  .bit_or(integer<16> {}.from_uint64(0x00ff))
                  .to_uint64(),
              0xf0ff);
  }

  TEST(integer, bit_xor) {
    EXPECT_EQ(integer<16> {}
                  .from_uint64(0xf0f0)
                  .bit_xor(integer<16> {}.from_uint64(0x00ff))
                  .to_uint64(),
              0xf00f);
  }

  TEST(integer, increment) {
    EXPECT_EQ(integer<16> {}.from_int64(0).increment().to_int64(), 1);

    EXPECT_EQ(
        integer<16> {}.from_int64(0xffff).increment().to_int64(),
        0x10000);
  }

  TEST(integer, decrement) {
    EXPECT_EQ(integer<16> {}.from_int64(0).decrement().to_int64(),
              -1);

    EXPECT_EQ(
        integer<16> {}.from_int64(0x10000).decrement().to_int64(),
        0xffff);
  }

  TEST(integer, negate) {
    EXPECT_EQ(integer<16> {}.from_int64(5).negate().to_int64(), -5);

    EXPECT_EQ(integer<16> {}.from_int64(5000).negate().to_int64(),
              -5000);
  }

  TEST(integer, add_positive) {
    EXPECT_EQ(integer<16>::from_int64(123)
                  .add(integer<16>::from_int64(456))
                  .to_int64(),
              579);
  }

  TEST(integer, subtract_positive) {
    EXPECT_EQ(integer<16>::from_int64(579)
                  .subtract(integer<16>::from_int64(456))
                  .to_int64(),
              123);
  }
}
