#ifndef NUMBER_HPP
#define NUMBER_HPP

#include <cstdint>
#include <iostream>
#include <vector>

class Integer {
  friend std::ostream& operator<<(std::ostream& out, Integer number);

public:
  using Digit = uint8_t;
  static const uint64_t Base = sizeof(Digit) * 256;
  using Digits = std::vector<Digit>;

private:
  bool _positive;
  Digits _digits;

public:
  // CONSTRUCTORS
  Integer();
  Integer(Digit const& d);
  Integer(int integer);
  ~Integer();

  // CAST
  operator std::string() const;

  // COMPARISONS
  bool operator==(Integer const& other) const;
  bool operator>(Integer const& o) const;
  bool operator!=(Integer const& other) const { return !(*this == other); }
  bool operator>=(Integer const& o) const { return *this > o || *this == o; }
  bool operator<=(Integer const& o) const { return !(*this > o); }
  bool operator<(Integer const& o) const { return !(*this >= o); }

  // OPERATORS
  Integer operator-() const;
  Integer& operator+=(Integer const& other);
};

Integer operator+(Integer left, Integer const& right);

std::ostream& operator<<(std::ostream& out, Integer number);

#endif // !NUMBER_HPP
