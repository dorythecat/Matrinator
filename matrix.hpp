#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstdint>
#include <vector>

template<typename T>
class Matrix {
public:
  uint_fast32_t size;

  explicit Matrix(uint_fast32_t size, bool zero = false) : size(size) {
    m.reserve(size * size);
    if (zero) {
      std::fill(m.begin(), m.end(), 0);
      return;
    }
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < size; y++) {
        m.push_back(x == y ? 1 : 0);
      }
    }
  }
  ~Matrix() = default;

  // Helper function to print the matrix to the console
  void print() {
    T out = 0;
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < size; y++) {
        out = m[y + x * size];
        std::cout << (std::abs(out) == 0 ? 0 : out) << ' '; // Clean our output so we don't get -0
      } std::cout << std::endl;
    }
  }

  // Helper functions to set values on the matrix (DO NOT USE INTERNALLY)
  void setMatrix(std::vector<T> matrix) { m = matrix; }
  void setElement(uint_fast32_t x, uint_fast32_t y, T value) { m[x + y * size] = value; }

  // Comparison operators
  bool operator==(const Matrix<T> a) {
    if (size != a.size || m != a.m) return false;
    return true;
  }
  bool operator!=(const Matrix<T> a) {
    if (size != a.size || m != a.m) return true;
    return false;
  }

  // Real operators
  Matrix<T> operator*(const T a) {
    if (a == 1) return *this;

    std::vector<T> matrix(m.size());
    for (uint_fast32_t i = 0; i < m.size(); i++) matrix.push_back(m[i] * a);

    Matrix<T> mat(size);
    mat.m = matrix;
    return mat;
  }
  Matrix<T> operator/(const T a) {
    if (a == 1) return *this;

    std::vector<T> matrix(m.size());
    for (uint_fast32_t i = 0; i < m.size(); i++) matrix.push_back(m[i] / a);

    Matrix<T> mat(size);
    mat.m = matrix;
    return mat;
  }
  Matrix<T> operator*=(const T a) {
    if (a == 1) return *this;
    for (uint_fast32_t i = 0; i < m.size(); i++) m[i] *= a;
    return *this;
  }
  Matrix<T> operator/=(const T a) {
    if (a == 1) return *this;
    for (uint_fast32_t i = 0; i < m.size(); i++) m[i] /= a;
    return *this;
  }

  // Matrix operators
  Matrix<T> operator+(const Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t i = 0; i < m.size(); i++) result.m.push_back(m[i] + a.m[i]);
    return result;
  }
  Matrix<T> operator-(const Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t i = 0; i < m.size(); i++) result.m.push_back(m[i] - a.m[i]);
    return result;
  }
  Matrix<T> operator*(const Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < size; y++) {
        T sum = 0;
        for (uint_fast32_t i = 0; i < size; i++) sum += m[y + i * size] * a.m[i + x * size];
        result.m.push_back(sum);
      }
    } return result;
  }
  Matrix<T> operator+=(Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t i = 0; i < m.size(); i++) result.m.push_back(m[i] + a.m[i]);
    *this = result;
    return result;
  }
  Matrix<T> operator-=(Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t i = 0; i < m.size(); i++) result.m.push_back(m[i] - a.m[i]);

    *this = result;
    return result;
  }
  Matrix<T> operator*=(Matrix<T> a) {
    if (a.size != size) throw std::exception();

    Matrix<T> result(size, true);
    result.m.clear();
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < size; y++) {
        T sum = 0;
          for (uint_fast32_t i = 0; i < size; i++) sum += m[y + i * size] * a.m[i + x * size];
        result.m.push_back(sum);
      }
    }

    *this = result;
    return result;
  }

  // Single-matrix operators (TRANSPOSE ALTERS THE MATRIX IT IS USED UPON)
  Matrix<T> transpose() {
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < x; y++) {
        if (x == y) continue;
        T temp = m[y + x * size];
        m[y + x * size] = m[x + y * size];
        m[x + y * size] = temp;
      }
    } return *this;
  }
  Matrix<T> minor(uint_fast32_t x, uint_fast32_t y) {
    Matrix<T> mat(size - 1, true);
    mat.m.clear();
    for (uint_fast32_t y1 = 0; y1 < size; y1++) {
      if (y1 == y) continue;
      uint_fast32_t y2 = y1 * size;
      for (uint_fast32_t x1 = 0; x1 < size; x1++) {
        if (x1 == x) continue;
        mat.m.push_back(m[x1 + y2]);
      }
    } return mat;
  }

  // Linear transformations (THEY ALTER THE MATRIX)
  Matrix<T> switchRows(uint_fast32_t r1, uint_fast32_t r2) {
    r1 *= size;
    r2 *= size;
    for (uint_fast32_t i = 0; i < size; i++) {
      T temp = m[i + r1];
      m[i + r1] = m[i + r2];
      m[i + r2] = temp;
    } return *this;
  }
  Matrix<T> multiplyRow(uint_fast32_t row, T mul) {
    row *= size;
    for (uint_fast32_t i = 0; i < size; i++) m[i + row] *= mul;
    return *this;
  }
  Matrix<T> linearAddRows(uint_fast32_t r1, uint_fast32_t r2, T mul = 1) {
    r1 *= size;
    r2 *= size;
    for (uint_fast32_t i = 0; i < size; i++) m[i + r1] += m[i + r2] * mul;
    return *this;
  }
  Matrix<T> rowEchelon() {
    for (uint_fast32_t j = 0; j < size - 1; j++) {
      T jj = m[j + j * size];
      if (jj == 0) {
        for (uint_fast32_t i = j + 1; i < size; i++) {
          if (m[j + i * size] == 0) continue;
          switchRows(j, i);
          break;
        } if (jj == 0) return Matrix<T>(size, true);
      } jj = 1 / jj;
      for (uint_fast32_t i = j + 1; i < size; i++) {
        if (m[j + i * size] == 0) continue;
        linearAddRows(i, j, - m[j + i * size] * jj);
      }
    } return *this;
  }
  Matrix<T> diagonal() {
    rowEchelon(); // Convert to row echelon, to start (this also checks if it's inversible)
    for (uint_fast32_t j = size - 1; j > 0; j--) {
      T jj = m[j + j * size];
      for (uint_fast32_t i = j; i > 0; i--) {
        if (m[j + (i - 1) * size] == 0) continue;
        linearAddRows(i - 1, j, - m[j + (i - 1) * size] / jj);
      }
    } return *this;
  }

  // Alters this matrix to be row echelon or diagonal, and returns a matrix,
  // to which the same transformations have been applied
  Matrix<T> rowEchelonIdentity(Matrix<T>* identity) {
    for (uint_fast32_t j = 0; j < size - 1; j++) {
      T jj = m[j + j * size];
      if (jj == 0) {
        for (uint_fast32_t i = j + 1; i < size; i++) {
          if (m[j + i * size] == 0) continue;
          switchRows(j, i);
          identity->switchRows(j, i);
          break;
        } if (jj == 0) return Matrix<T>(size, true);
      } jj = 1 / jj;
      for (uint_fast32_t i = j + 1; i < size; i++) {
        if (m[j + i * size] == 0) continue;
        T mul = -m[j + i * size] * jj;
        linearAddRows(i, j, mul);
        identity->linearAddRows(i, j, mul);
      }
    } return *this;
  }
  Matrix<T> diagonalIdentity(Matrix<T>* identity) {
    rowEchelonIdentity(identity); // Convert to row echelon, to start (this also checks if it's inversible)
    for (uint_fast32_t j = size - 1; j > 0; j--) {
      T jj = 1 / m[j + j * size];
      for (uint_fast32_t i = j; i > 0; i--) {
        if (m[j + (i - 1) * size] == 0) continue;
        T mul = -m[j + (i - 1) * size] * jj;
        linearAddRows(i - 1, j, mul);
        identity->linearAddRows(i - 1, j, mul);
      }
    } return *this;
  }

  // Determinant
  T determinant() {
    Matrix<T> aux = *this;
    aux.rowEchelon(); // We don't want to modify this matrix

    T mul = 1;
    for (uint_fast32_t i = 0; i < size; i++) mul *= aux.m[i + i * size];
    return mul;
  }

  // Adjugate and inverse
  Matrix<T> adjugate() {
    Matrix<T> adj(size, true);
    adj.m.clear();
    for (uint_fast32_t x = 0; x < size; x++) {
      for (uint_fast32_t y = 0; y < size; y++) {
        adj.m.push_back(minor(x, y).determinant() * ((x + y) % 2 == 0 ? 1 : -1));
      }
    } return adj;
  }
  Matrix<T> inverse() {
    return adjugate() / determinant();
  }

  Matrix<T> gaussInverse() {
    Matrix<T> inverse(size);
    diagonalIdentity(&inverse);
    for (uint_fast32_t i = 0; i < size; i++) inverse.multiplyRow(i, 1 / m[i + i * size]);
    return inverse;
  }

private:
  std::vector<T> m;
};

#endif
