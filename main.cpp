#include <iostream>

#include "matrix.hpp"

int main(int argc, char* argv[]) {
  uint_fast32_t order = 3;
  uint_fast32_t method = 0;

  std::vector<float> m{};
  if (argc >= 2) {
    // 0 is the ./Matrinator.exe command
    // 1 should be the order of the matrix
    // 2 (if there) should be which method to use:
    //    - 0: Gauss-Jordan w/ Partial Pivoting
    //    - 1: Adjugate method (Row-echelon determinant)
    // If 3 or more parameter exist, we ask for a matrix input

    order = atoi(argv[1]);
    if (argc >= 3) {
      method = atoi(argv[2]);
      if (argc >= 4) {
        m.reserve(order * order);
        std::cout << "Insert your matrix, one number at a time, going up left then up right, "
                     "then down left, down right, separating the numbers with spaces" << std::endl;
        for (uint_fast32_t i = 0; i < order * order; i++) {
          float x = 0;
          std::cin >> x;
          m.push_back(x);
        }
      }
    }
  }

  Matrix<float> a(order);
  if (!m.empty()) a.setMatrix(m);
  std::cout << "---" << std::endl;
  a.print();
  std::cout << "---" << std::endl;
  std::cout << a.determinant() << std::endl;
  std::cout << "---" << std::endl;
  switch (method) {
    case 0:
      a.gaussInverse().print();
      break;
    case 1:
      a.inverse().print();
      break;
    case 2:
      a.gaussInverse();
      break;
    case 3:
      a.inverse();
      break;
    default:
      throw std::exception();
  } std::cout << "---" << std::endl;
  return 0;
}
