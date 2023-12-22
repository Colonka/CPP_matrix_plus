#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <cstring>
#include <exception>
#include <iostream>

class S21Matrix {
 public:
  // CONSTRUCTORS AND DESTRACTOR
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // ACCESSORS AND MUTATORS
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows);
  void SetCols(int new_cols);
  void ResizeMatrix(int new_rows, int new_cols);

  // OPERATIONS
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // OPERATORS
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double number) noexcept;
  friend S21Matrix operator*(const double number,
                             const S21Matrix& other) noexcept;
  bool operator==(const S21Matrix& other);
  S21Matrix operator=(S21Matrix&& other) noexcept;
  S21Matrix operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(const double other);
  double& operator()(int i, int j);
  double operator()(int i, int j) const;

 private:
  // ARGS
  int rows_, cols_;
  double** matrix_;

  // SUPPORT FUNCTIONS
  void CreateMatrix();
  void copy_matrix(const S21Matrix& other);
  S21Matrix minor_matrix(int i, int j, const S21Matrix& other);
};

#endif  // SRC_S21_MATRIX_OOP_H_