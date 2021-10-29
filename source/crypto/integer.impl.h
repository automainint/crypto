/*  crypto/integer.impl.h
 *
 *  Copyright (c) 2021 Mitya Selivanov
 */

#ifndef crypto_integer_impl_h
#define crypto_integer_impl_h

namespace crypto {
  template <ptrdiff_t size_>
  constexpr auto integer<size_>::to_int64() const noexcept
      -> int64_t {
    return static_cast<int64_t>(to_uint64());
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::to_uint64() const noexcept
      -> uint64_t {

    auto n = uint64_t {};
    auto k = uint64_t { 1 };

    for (ptrdiff_t index = 0; index < size_ && index < sizeof n;
         index++) {
      n += m_bytes[index] * k;
      k *= 0x100;
    }

    return n;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::to_double() const noexcept
      -> double {
    if (is_negative())
      return -negate().to_double();

    long double f = {};
    long double k = 1.;

    for (ptrdiff_t index = 0; index < size_; index++) {
      f += m_bytes[index] * k;
      k *= 0x100;
    }

    return static_cast<double>(f);
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::from_int64(int64_t i) noexcept
      -> integer {
    auto x = from_uint64(static_cast<uint64_t>(i));
    if (i < 0)
      for (ptrdiff_t k = sizeof i; k < size_; k++)
        x.m_bytes[k] = 0xff;
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::from_uint64(uint64_t i) noexcept
      -> integer {
    auto x     = integer {};
    auto index = ptrdiff_t {};

    while (i > 0 && index < size_) {
      x.m_bytes[index++] = i % 0x100;
      i /= 0x100;
    }

    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::from_double(double f) noexcept
      -> integer {
    auto x     = integer {};
    auto index = ptrdiff_t {};

    while (f > .5 && index < size_) {
      x.m_bytes[index++] = static_cast<int>(
          round(f - floor(f / 0x100) * 0x100));
      f = floor(f / 0x100);
    }

    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::bit_not() const noexcept -> integer {
    auto x = integer {};
    for (ptrdiff_t i = 0; i < size_; i++) x.m_bytes[i] = ~m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::bit_and(
      integer const &other) const noexcept -> integer {
    auto x = integer {};
    for (ptrdiff_t i = 0; i < size_; i++)
      x.m_bytes[i] = m_bytes[i] & other.m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::bit_or(
      integer const &other) const noexcept -> integer {
    auto x = integer {};
    for (ptrdiff_t i = 0; i < size_; i++)
      x.m_bytes[i] = m_bytes[i] | other.m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::bit_xor(
      integer const &other) const noexcept -> integer {
    auto x = integer {};
    for (ptrdiff_t i = 0; i < size_; i++)
      x.m_bytes[i] = m_bytes[i] ^ other.m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::is_negative() const noexcept
      -> bool {
    return (m_bytes.back() & 0x80) == 0x80;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::increment() const noexcept
      -> integer {
    auto x = integer {};
    auto i = ptrdiff_t {};

    for (; i < size_; i++) {
      if (m_bytes[i] == 0xff) {
        x.m_bytes[i] = 0;
      } else {
        x.m_bytes[i] = m_bytes[i] + 1;
        i++;
        break;
      }
    }

    for (; i < size_; i++) x.m_bytes[i] = m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::decrement() const noexcept
      -> integer {
    auto x = integer {};
    auto i = ptrdiff_t {};

    for (; i < size_; i++) {
      if (m_bytes[i] == 0) {
        x.m_bytes[i] = 0xff;
      } else {
        x.m_bytes[i] = m_bytes[i] - 1;
        i++;
        break;
      }
    }

    for (; i < size_; i++) x.m_bytes[i] = m_bytes[i];
    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::negate() const noexcept -> integer {
    return decrement().bit_not();
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::add(
      integer const &other) const noexcept -> integer {
    auto x = integer {};
    auto s = unsigned {};

    for (ptrdiff_t i = 0; i < size_; i++) {
      s            = m_bytes[i] + other.m_bytes[i] + s;
      x.m_bytes[i] = s % 0x100;
      s /= 0x100;
    }

    return x;
  }

  template <ptrdiff_t size_>
  constexpr auto integer<size_>::subtract(
      integer const &other) const noexcept -> integer {
    return add(other.negate());
  }
}

#endif
