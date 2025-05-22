#include <iostream>

class Complex {
private:
  double real;
  double imaginary;

public:
  Complex(double real, double imaginary) : real(real), imaginary(imaginary) {}

  // 重载加法运算符
  Complex operator+(const Complex &other) const {
    return Complex(real + other.real, imaginary + other.imaginary);
  }

  // 重载减法运算符
  Complex operator-(const Complex &other) const {
    return Complex(real - other.real, imaginary - other.imaginary);
  }

  // 重载乘法运算符
  Complex operator*(const Complex &other) const {
    return Complex((real * other.real) - (imaginary * other.imaginary),
                   (real * other.imaginary) + (imaginary * other.real));
  }

  // 重载除法运算符
  Complex operator/(const Complex &other) const {
    double denominator =
        (other.real * other.real) + (other.imaginary * other.imaginary);
    double newReal =
        ((real * other.real) + (imaginary * other.imaginary)) / denominator;
    double newImaginary =
        ((imaginary * other.real) - (real * other.imaginary)) / denominator;
    return Complex(newReal, newImaginary);
  }

  // 重载赋值运算符
  Complex &operator=(const Complex &other) {
    real = other.real;
    imaginary = other.imaginary;
    return *this;
  }

  // 重载等于运算符
  bool operator==(const Complex &other) const {
    return (real == other.real) && (imaginary == other.imaginary);
  }

  // 重载不等于运算符
  bool operator!=(const Complex &other) const { return !(*this == other); }

  // 重载输出流运算符
  friend std::ostream &operator<<(std::ostream &out, const Complex &complex) {
    out << complex.real << " + " << complex.imaginary << "i";
    return out;
  }
};

int main() {
  Complex c1(1.0, 2.0);
  Complex c2(3.0, 4.0);

  Complex sum = c1 + c2;
  Complex difference = c1 - c2;
  Complex product = c1 * c2;
  Complex quotient = c1 / c2;

  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Difference: " << difference << std::endl;
  std::cout << "Product: " << product << std::endl;
  std::cout << "Quotient: " << quotient << std::endl;

  return 0;
}
