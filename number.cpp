#include "number.hpp"
#include <algorithm>
#include <sstream>

Integer::Integer(Digit const& d) : _positive(true), _digits(1, d) {}

Integer::Integer() : Integer(Digit(0)) {}

Integer::Integer(int integer) : _positive(true), _digits() {
  if (integer == 0) {
    _digits.push_back(0);
    return;
  }
  if (integer < 0) {
    _positive = false;
    integer = -integer;
  }
  while (integer > 0) {
    Digit remainder = integer % Base;
    integer /= Base;
    _digits.push_back(remainder);
  }
}

Integer::~Integer() {}

Integer::operator std::string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

bool Integer::operator==(Integer const& other) const {
  if (_positive != other._positive) {
    return false;
  }
  if (_digits.size() != other._digits.size()) {
    return false;
  }
  std::size_t length = _digits.size();
  for (std::size_t i = 0; i < length; ++i) {
    if (_digits[i] != other._digits[i]) {
      return false;
    }
  }
  return true;
}

bool Integer::operator>(Integer const& o) const {
  if (_positive != o._positive) {
    return _positive;
  }
  if (_digits.size() != o._digits.size()) {
    return !((_digits.size() > o._digits.size()) ^ _positive);
  }
  bool digit_bigger = false;
  auto it = _digits.crbegin();
  auto eit = _digits.crend();
  auto oit = o._digits.crbegin();
  auto eoit = o._digits.crend();
  for (; (it != eit) && (oit != eoit); ++it, ++oit) {
    if (*it > *oit) {
      digit_bigger = true;
      break;
    } else if (*it < *oit) {
      break;
    }
  }
  return !(digit_bigger ^ _positive);
}

Integer Integer::operator-() const {
  Integer result = *this;
  result._positive = !result._positive;
  return result;
}

Integer& Integer::operator+=(Integer const& other) {
  std::size_t min_length = std::min(_digits.size(), other._digits.size());
  bool overflow = false;
  for (std::size_t i = 0; i < min_length; ++i) {
    auto tmp = _digits[i] + other._digits[i] + Integer::Digit(overflow);
    overflow = (tmp < _digits[i]) ? true : false;
    _digits[i] = tmp;
  }
  std::size_t max_length = std::max(_digits.size(), other._digits.size());
  for (std::size_t i = min_length; i < max_length; ++i) {
    Integer::Digit left(0);
    if (i < _digits.size()) {
      left = _digits[i];
    }
    Integer::Digit right(0);
    if (i < other._digits.size()) {
      right = other._digits[i];
    }
    auto tmp = left + right + Integer::Digit(overflow);
    if (i >= _digits.size()) {
      _digits.push_back(tmp);
    }
  }
  if (overflow) {
    _digits.push_back(Digit(1));
  }
  return *this;
}

Integer operator+(Integer left, Integer const& right) {
  left += right;
  return left;
}

std::ostream& operator<<(std::ostream& out, Integer number) {
  Integer::Digits string_digits;
  if (number._positive == false) {
    out << "-";
  }
  for (auto it = number._digits.crbegin(); it != number._digits.crend(); ++it) {
    out << static_cast<int>(*it) << ".";
  }
  return out;
}
