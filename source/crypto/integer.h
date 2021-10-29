/*  crypto/integer.h
 *
 *  Copyright (c) 2021 Mitya Selivanov
 */

#ifndef crypto_integer_h
#define crypto_integer_h

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace crypto {
  template <ptrdiff_t size_>
  class integer {
  public:
    [[nodiscard]] constexpr auto to_int64() const noexcept -> int64_t;

    [[nodiscard]] constexpr auto to_uint64() const noexcept
        -> uint64_t;

    [[nodiscard]] constexpr auto to_double() const noexcept -> double;

    [[nodiscard]] constexpr static auto from_int64(int64_t i) noexcept
        -> integer;

    [[nodiscard]] constexpr static auto from_uint64(
        uint64_t i) noexcept -> integer;

    [[nodiscard]] constexpr static auto from_double(double f) noexcept
        -> integer;

    [[nodiscard]] constexpr auto bit_not() const noexcept -> integer;

    [[nodiscard]] constexpr auto bit_and(
        integer const &other) const noexcept -> integer;

    [[nodiscard]] constexpr auto bit_or(
        integer const &other) const noexcept -> integer;

    [[nodiscard]] constexpr auto bit_xor(
        integer const &other) const noexcept -> integer;

    [[nodiscard]] constexpr auto is_negative() const noexcept -> bool;

    [[nodiscard]] constexpr auto increment() const noexcept
        -> integer;

    [[nodiscard]] constexpr auto decrement() const noexcept
        -> integer;

    [[nodiscard]] constexpr auto negate() const noexcept -> integer;

    [[nodiscard]] constexpr auto add(
        integer const &other) const noexcept -> integer;

    [[nodiscard]] constexpr auto subtract(
        integer const &other) const noexcept -> integer;

  private:
    std::array<uint8_t, size_> m_bytes;
  };

  using int128 = integer<16>;
  using int256 = integer<32>;
  using int512 = integer<64>;
}

#include "integer.impl.h"

#endif
