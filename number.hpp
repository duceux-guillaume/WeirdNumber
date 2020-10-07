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
  Integer& operator*=(Integer const& other);
};

Integer operator+(Integer left, Integer const& right);
Integer operator*(Integer left, Integer const& right);

std::ostream& operator<<(std::ostream& out, Integer number);

std::istream& operator>>(std::istream& theStream, Integer& theNumber);

class Decimal {
private:
  Integer _numerator;
  Integer _denominator;

public:
  Decimal() : _numerator(0), _denominator(1) {}

  Decimal& operator+=(Decimal const& other);
};

class Complex {
  friend std::istream& operator>>(std::istream& out, Complex& number);

private:
  Integer _real;
  Integer _img;

public:
  Complex() : Complex(0, 0) {}
  Complex(Integer const& r) : Complex(r, 0) {}
  Complex(Integer const& r, Integer const& i) : _real(r), _img(i) {}

  Integer const& real() const { return _real; }
  Integer const& img() const { return _img; }

  Complex& operator+=(Complex const& other);
};

Complex operator+(Complex left, Complex const& right);

std::ostream& operator<<(std::ostream& out, Complex const& number);

std::istream& operator>>(std::istream& out, Complex& number);

std::string polar(Complex const& n);

#endif // !NUMBER_HPP
