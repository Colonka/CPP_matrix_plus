#include "s21_matrix_oop.h"

// CONSTRUCTORS AND DESTRUCTOR

S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) { copy_matrix(other); }

S21Matrix::S21Matrix(S21Matrix&& other) noexcept {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

// ACCESSORS AND MUTATORS

int S21Matrix::GetRows() const noexcept { return rows_; }

int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int new_rows) { ResizeMatrix(new_rows, cols_); }

void S21Matrix::SetCols(int new_cols) { ResizeMatrix(rows_, new_cols); }

void S21Matrix::ResizeMatrix(int new_rows, int new_cols) {
  if (new_rows < 0 || new_cols < 0) {
    throw std::invalid_argument(
        "Incorrect index in ResizeMatrix(), index must be greater or equal "
        "than 0");
  } else {
    S21Matrix tmp(new_rows, new_cols);
    new_rows = new_rows < rows_ ? new_rows : rows_;
    new_cols = new_cols < cols_ ? new_cols : cols_;
    for (int i = 0; i < new_rows; i++) {
      std::memcpy(tmp.matrix_[i], matrix_[i], new_cols * sizeof(double));
    }
    *this = std::move(tmp);
  }
}

// OPERATORS

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::length_error(
        "Rows and cols amount of each matrix must be equal");
  }
  S21Matrix tmp(*this);
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::length_error(
        "Rows and cols amount of each matrix must be equal");
  }
  S21Matrix tmp(*this);
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (rows_ != other.cols_ && cols_ != other.rows_) {
    throw std::length_error(
        "Rows amount matrix A must be equal Cols amount matrix B");
  }
  S21Matrix tmp(*this);
  tmp.MulMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(const double number) noexcept {
  S21Matrix tmp(*this);
  tmp.MulNumber(number);
  return tmp;
}

S21Matrix operator*(const double number, const S21Matrix& other) noexcept {
  S21Matrix tmp(other);
  tmp.MulNumber(number);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  bool res = 0;
  if (EqMatrix(other)) res = 1;
  return res;
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) noexcept {
  std::swap(matrix_, other.matrix_);
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  return *this;
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix copy(other);
  *this = std::move(copy);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double other) {
  MulNumber(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
    throw std::invalid_argument("Incorrect indexes!");
  return matrix_[i][j];
}

double S21Matrix::operator()(int i, int j) const {
  if (rows_ <= i || cols_ <= j || i < 0 || j < 0)
    throw std::invalid_argument("Incorrect indexes!");
  return matrix_[i][j];
}

// OPERATIONS

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool res = 1;
  if (rows_ == other.rows_ && cols_ == other.cols_ && matrix_ != nullptr &&
      other.matrix_ != nullptr) {
    for (int i = 0; i < rows_ && res; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (res) {
          if (std::abs(other.matrix_[i][j] - matrix_[i][j]) > 1e-7) res = 0;
        } else {
          break;
        }
      }
    }
  } else {
    res = 0;
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    S21Matrix tmp(*this);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        tmp(i, j) += other(i, j);
      }
    }
    *this = std::move(tmp);
  } else {
    throw std::length_error(
        "Rows and cols amount of each matrix must be equal");
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        (*this)(i, j) -= other(i, j);
      }
    }
  } else {
    throw std::length_error(
        "Rows and cols amount of each matrix must be equal");
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.GetRows()) {
    throw std::length_error(
        "Cols amount matrix A must be equal Rows amount matrix B");
  }
  S21Matrix tmp(rows_, other.GetCols());
  for (int i = 0; i < tmp.GetRows(); ++i) {
    for (int j = 0; j < tmp.GetCols(); ++j) {
      for (int k = 0; k < cols_; ++k) {
        tmp(i, j) += ((*this)(i, k) * other(k, j));
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix ::Transpose() {
  S21Matrix result{cols_, rows_};
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(j, i) = (*this)(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::length_error("Incorrect matrix size for CalcComplements");
  }
  S21Matrix result(*this);
  S21Matrix tmp_minor_support(rows_ - 1, cols_ - 1);
  for (int i = 0; i < result.GetRows(); ++i) {
    for (int j = 0; j < result.GetCols(); ++j) {
      tmp_minor_support = minor_matrix(i, j, *this);
      result(i, j) = tmp_minor_support.Determinant();
      if ((i + j) % 2 != 0) {
        result(i, j) = -result(i, j);
      }
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double res = 1;
  if (rows_ != 2) {
    if (rows_ != 1) {
      if (rows_ != 0) {
        if (rows_ == cols_) {
          S21Matrix sup(*this);
          for (int step = 0; step < rows_ - 1; ++step) {
            res *= sup(step, step);
            if (sup(step, step) != 0) {
              for (int j = cols_ - 1; j >= step; --j) {
                sup(step, j) = sup(step, j) / sup(step, step);
              }
            }
            for (int i = step; i < rows_ - 1; ++i) {
              if (std::abs(sup(i + 1, step)) > 1e-7) {
                for (int j = cols_ - 1; j >= step; --j) {
                  sup(i + 1, j) =
                      sup(i + 1, j) - (sup(step, j) * sup(i + 1, step));
                }
              }
            }
          }
          res *= sup(rows_ - 1, cols_ - 1);
        } else {
          throw std::length_error("Incorrect matrix size for Determinant");
        }
      } else {
        res = 0;
      }
    } else
      res = (*this)(0, 0);
  } else {
    res = ((*this)(0, 0) * (*this)(1, 1)) - ((*this)(0, 1) * (*this)(1, 0));
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (std::abs(det) <= 1e-7) {
    throw std::length_error(
        "Impossible to inverse matrix which determinant equal zero");
  }
  S21Matrix tmp(*this);
  S21Matrix tmp_tmp(*this);
  tmp_tmp = tmp.CalcComplements();
  tmp = tmp_tmp.Transpose();
  tmp.MulNumber(-1);
  return tmp;
}

// SUPPORT FUNCTIONS

void S21Matrix::CreateMatrix() {
  if (rows_ < 0 || cols_ < 0)
    throw std::length_error("Matrix rows or cols must be greater than zero");
  matrix_ = new double* [rows_] {};
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::copy_matrix(const S21Matrix& other) {
  rows_ = other.GetRows();
  cols_ = other.GetCols();
  CreateMatrix();
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      std::memcpy(matrix_[i], other.matrix_[i], cols_ * sizeof(double));
    }
  }
}

S21Matrix S21Matrix::minor_matrix(int i, int j, const S21Matrix& other) {
  S21Matrix tmp(other.GetRows() - 1, other.GetCols() - 1);
  int flag_i = 0;
  int flag_j = 0;
  int flag_i_was = 0;
  for (int k = 0; k < other.GetRows(); ++k) {
    flag_i = 0;
    if (k == i) {
      flag_i = 1;
      flag_i_was = 1;
    }
    if (!flag_i) {
      flag_j = 0;
      for (int l = 0; l < other.GetCols(); ++l) {
        if (l == j) {
          flag_j = 1;
        } else {
          tmp(k - flag_i_was, l - flag_j) = other(k, l);
        }
      }
    }
  }
  return tmp;
}
