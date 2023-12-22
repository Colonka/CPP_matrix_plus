#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

TEST(test_matrix, default_constructor) {
  S21Matrix one;

  EXPECT_EQ(one.GetRows(), 0);
  EXPECT_EQ(one.GetCols(), 0);
}

TEST(test_matrix, rows_cols_constructor) {
  S21Matrix one(3, 3);

  EXPECT_EQ(one.GetRows(), 3);
  EXPECT_EQ(one.GetCols(), 3);
}

TEST(test_matrix, copy_constructor) {
  S21Matrix one(10, 10);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  S21Matrix two(one);

  EXPECT_EQ(one.GetRows(), two.GetRows());
  EXPECT_EQ(one.GetCols(), two.GetCols());
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      EXPECT_EQ(one(i, j), two(i, j));
    }
  }
}

TEST(test_matrix, move_constructor) {
  S21Matrix one(2, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  S21Matrix one_sup(one);
  S21Matrix two(std::move(one));

  EXPECT_EQ(2, two.GetRows());
  EXPECT_EQ(3, two.GetCols());
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one_sup(i, j), two(i, j));
    }
  }
}

TEST(test_matrix, cols_rows_setter_less) {
  S21Matrix one(3, 4);
  one.SetRows(2);
  EXPECT_EQ(2, one.GetRows());
  EXPECT_EQ(4, one.GetCols());
  one.SetCols(3);
  EXPECT_EQ(2, one.GetRows());
  EXPECT_EQ(3, one.GetCols());
}

TEST(test_matrix, cols_rows_setter_more) {
  S21Matrix one(3, 4);
  one.SetCols(100);
  one.SetRows(100);
  EXPECT_EQ(100, one.GetCols());
  EXPECT_EQ(100, one.GetRows());
}

// OPERATORS

TEST(test_matrix, index_operator_true) {
  S21Matrix one(3, 3);
  double res = 1;
  one(2, 2) = 15.7;
  res = one(2, 2);
  EXPECT_EQ(15.7, one(2, 2));
  EXPECT_EQ(15.7, res);
}

TEST(test_matrix, index_operator_false) {
  S21Matrix one(1, 1);
  EXPECT_THROW(one(2, 2), std::invalid_argument);
}

TEST(test_matrix, equal_copy_true) {
  S21Matrix one(3, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  S21Matrix two(3, 3);
  two = one;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one(i, j), two(i, j));
    }
  }
}

TEST(test_matrix, equal_move_true) {
  S21Matrix one(3, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  S21Matrix one_clone(3, 3);
  one_clone(0, 0) = 1;
  one_clone(0, 1) = 2;
  one_clone(0, 2) = 3;
  one_clone(1, 0) = 4;
  one_clone(1, 1) = 5;
  one_clone(1, 2) = 6;
  one_clone(2, 0) = 7;
  one_clone(2, 1) = 8;
  one_clone(2, 2) = 9;

  S21Matrix two(3, 3);

  two = std::move(one);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one_clone(i, j), two(i, j));
    }
  }
}

// OPERATIONS

TEST(test_matrix, equal_matrix_true) {
  S21Matrix one(3, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  S21Matrix two(3, 3);
  two(0, 0) = 1;
  two(0, 1) = 2;
  two(0, 2) = 3;
  two(1, 0) = 4;
  two(1, 1) = 5;
  two(1, 2) = 6;
  two(2, 0) = 7;
  two(2, 1) = 8;
  two(2, 2) = 9;

  EXPECT_EQ(one.EqMatrix(two), 1);
  EXPECT_EQ(one == two, 1);
}

TEST(test_matrix, equal_matrix_false) {
  S21Matrix one(3, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  S21Matrix two(3, 3);
  two(0, 0) = 1;
  two(0, 1) = 2;
  two(0, 2) = 34;
  two(1, 0) = 4;
  two(1, 1) = 5;
  two(1, 2) = 6;
  two(2, 0) = 7;
  two(2, 1) = 8;
  two(2, 2) = 9;

  EXPECT_EQ(one.EqMatrix(two), 0);
  EXPECT_EQ(one == two, 0);
}

TEST(test_matrix, sum_matrix_true) {
  S21Matrix one(3, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;
  one(2, 0) = 7;
  one(2, 1) = 8;
  one(2, 2) = 9;

  S21Matrix two(3, 3);
  two(0, 0) = 1;
  two(0, 1) = 2;
  two(0, 2) = 3;
  two(1, 0) = 4;
  two(1, 1) = 5;
  two(1, 2) = 6;
  two(2, 0) = 7;
  two(2, 1) = 8;
  two(2, 2) = 9;

  S21Matrix operator_sum(3, 3);

  operator_sum = one + two;

  one.SumMatrix(two);

  S21Matrix res(3, 3);
  res(0, 0) = 2;
  res(0, 1) = 4;
  res(0, 2) = 6;
  res(1, 0) = 8;
  res(1, 1) = 10;
  res(1, 2) = 12;
  res(2, 0) = 14;
  res(2, 1) = 16;
  res(2, 2) = 18;

  S21Matrix one_sup(3, 3);

  one_sup(0, 0) = 1;
  one_sup(0, 1) = 2;
  one_sup(0, 2) = 3;
  one_sup(1, 0) = 4;
  one_sup(1, 1) = 5;
  one_sup(1, 2) = 6;
  one_sup(2, 0) = 7;
  one_sup(2, 1) = 8;
  one_sup(2, 2) = 9;

  one_sup += two;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one(i, j), res(i, j));
      EXPECT_EQ(operator_sum(i, j), res(i, j));
      EXPECT_EQ(one_sup(i, j), res(i, j));
    }
  }
}

TEST(test_matrix, sum_matrix_false) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  S21Matrix operator_sum(3, 3);
  EXPECT_THROW(one.SumMatrix(two), std::length_error);
  EXPECT_THROW(operator_sum = one + two, std::length_error);
}

TEST(test_matrix, sub_matrix_true) {
  S21Matrix one(3, 3);
  one(0, 0) = 9;
  one(0, 1) = 8;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 5;
  one(1, 2) = 4;
  one(2, 0) = 3;
  one(2, 1) = 2;
  one(2, 2) = 1;

  S21Matrix two(3, 3);
  two(0, 0) = 1;
  two(0, 1) = 2;
  two(0, 2) = 3;
  two(1, 0) = 4;
  two(1, 1) = 5;
  two(1, 2) = 6;
  two(2, 0) = 7;
  two(2, 1) = 8;
  two(2, 2) = 9;

  S21Matrix operator_sub(3, 3);

  operator_sub = one - two;

  one.SubMatrix(two);

  S21Matrix res(3, 3);
  res(0, 0) = 8;
  res(0, 1) = 6;
  res(0, 2) = 4;
  res(1, 0) = 2;
  res(1, 1) = 0;
  res(1, 2) = -2;
  res(2, 0) = -4;
  res(2, 1) = -6;
  res(2, 2) = -8;

  S21Matrix one_sup(3, 3);
  one_sup(0, 0) = 9;
  one_sup(0, 1) = 8;
  one_sup(0, 2) = 7;
  one_sup(1, 0) = 6;
  one_sup(1, 1) = 5;
  one_sup(1, 2) = 4;
  one_sup(2, 0) = 3;
  one_sup(2, 1) = 2;
  one_sup(2, 2) = 1;
  one_sup -= two;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one(i, j), res(i, j));
      EXPECT_EQ(operator_sub(i, j), res(i, j));
      EXPECT_EQ(one_sup(i, j), res(i, j));
    }
  }
}

TEST(test_matrix, sub_matrix_false) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 4);
  S21Matrix operator_sub(3, 3);
  EXPECT_THROW(one.SumMatrix(two), std::length_error);
  EXPECT_THROW(operator_sub = one - two;, std::length_error);
}

TEST(test_matrix, mul_number) {
  S21Matrix one(3, 3);
  one(0, 0) = 9;
  one(0, 1) = 8;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 5;
  one(1, 2) = 4;
  one(2, 0) = 3;
  one(2, 1) = 2;
  one(2, 2) = 1;

  S21Matrix tmp(3, 3);
  S21Matrix tmp2(3, 3);
  tmp = one * 2;
  tmp2 = 2 * one;

  one.MulNumber(2);

  S21Matrix res(3, 3);
  res(0, 0) = 18;
  res(0, 1) = 16;
  res(0, 2) = 14;
  res(1, 0) = 12;
  res(1, 1) = 10;
  res(1, 2) = 8;
  res(2, 0) = 6;
  res(2, 1) = 4;
  res(2, 2) = 2;

  S21Matrix one_sup(3, 3);
  one_sup(0, 0) = 9;
  one_sup(0, 1) = 8;
  one_sup(0, 2) = 7;
  one_sup(1, 0) = 6;
  one_sup(1, 1) = 5;
  one_sup(1, 2) = 4;
  one_sup(2, 0) = 3;
  one_sup(2, 1) = 2;
  one_sup(2, 2) = 1;
  one_sup *= 2;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(one(i, j), res(i, j));
      EXPECT_EQ(tmp(i, j), res(i, j));
      EXPECT_EQ(tmp2(i, j), res(i, j));
      EXPECT_EQ(one_sup(i, j), res(i, j));
    }
  }
}

TEST(test_matrix, mul_matrix_true) {
  S21Matrix one(2, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  S21Matrix two(3, 2);
  two(0, 0) = 6;
  two(0, 1) = 5;
  two(1, 0) = 4;
  two(1, 1) = 3;
  two(2, 0) = 2;
  two(2, 1) = 1;

  one.MulMatrix(two);

  S21Matrix res(2, 2);
  res(0, 0) = 20;
  res(0, 1) = 14;
  res(1, 0) = 56;
  res(1, 1) = 41;

  S21Matrix one_sup(2, 3);
  one_sup(0, 0) = 1;
  one_sup(0, 1) = 2;
  one_sup(0, 2) = 3;
  one_sup(1, 0) = 4;
  one_sup(1, 1) = 5;
  one_sup(1, 2) = 6;

  one_sup *= two;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(one(i, j), res(i, j));
      EXPECT_EQ(one_sup(i, j), res(i, j));
    }
  }
}

TEST(test_matrix, mul_matrix_operator_true) {
  S21Matrix one(2, 3);
  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 4;
  one(1, 1) = 5;
  one(1, 2) = 6;

  S21Matrix two(3, 2);
  two(0, 0) = 6;
  two(0, 1) = 5;
  two(1, 0) = 4;
  two(1, 1) = 3;
  two(2, 0) = 2;
  two(2, 1) = 1;

  one *= two;

  S21Matrix res(2, 2);
  res(0, 0) = 20;
  res(0, 1) = 14;
  res(1, 0) = 56;
  res(1, 1) = 41;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      EXPECT_EQ(one(i, j), res(i, j));
    }
  }
}

TEST(test_matrix, mul_matrix_false) {
  S21Matrix one(3, 2);
  S21Matrix two(2, 4);
  EXPECT_THROW(one.SumMatrix(two), std::length_error);
}

TEST(test_matrix, transpose) {
  S21Matrix one(3, 3);
  one(0, 0) = 9;
  one(0, 1) = 8;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 5;
  one(1, 2) = 4;
  one(2, 0) = 3;
  one(2, 1) = 2;
  one(2, 2) = 1;

  S21Matrix tmp(3, 3);
  tmp = one.Transpose();

  S21Matrix res(3, 3);
  res(0, 0) = 9;
  res(0, 1) = 6;
  res(0, 2) = 3;
  res(1, 0) = 8;
  res(1, 1) = 5;
  res(1, 2) = 2;
  res(2, 0) = 7;
  res(2, 1) = 4;
  res(2, 2) = 1;

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(tmp(i, j), res(i, j));
    }
  }
}

TEST(MatrixTest, complement_matrix_true_1) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 1;
  one(0, 1) = 2;
  one(0, 2) = 3;
  one(1, 0) = 0;
  one(1, 1) = 4;
  one(1, 2) = 2;
  one(2, 0) = 5;
  one(2, 1) = 2;
  one(2, 2) = 1;

  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;
  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;
  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;

  two = one.CalcComplements();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(two(i, j), result(i, j));
    }
  }
}

TEST(MatrixTest, complement_matrix_true_2) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 2;
  one(0, 1) = 5;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 3;
  one(1, 2) = 4;
  one(2, 0) = 5;
  one(2, 1) = -2;
  one(2, 2) = -3;

  result(0, 0) = -1;
  result(0, 1) = 38;
  result(0, 2) = -27;
  result(1, 0) = 1;
  result(1, 1) = -41;
  result(1, 2) = 29;
  result(2, 0) = -1;
  result(2, 1) = 34;
  result(2, 2) = -24;

  two = one.CalcComplements();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(two(i, j), result(i, j));
    }
  }
}

TEST(MatrixTest, determinant_0_true) {
  S21Matrix one{};

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(0, det);
}

TEST(MatrixTest, determinant_1_true) {
  S21Matrix one(1, 1);
  one(0, 0) = 8;

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(8, det);
}

TEST(MatrixTest, determinant_2_true) {
  S21Matrix one(2, 2);
  one(0, 0) = 0;
  one(0, 1) = 2;
  one(1, 0) = 5;
  one(1, 1) = 1;

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(-10, det);
}

TEST(MatrixTest, determinant_4_true) {
  S21Matrix one(4, 4);
  one(0, 0) = 8;
  one(0, 1) = 9;
  one(0, 2) = 2;
  one(0, 3) = 4;
  one(1, 0) = 0;
  one(1, 1) = 9;
  one(1, 2) = 8;
  one(1, 3) = 7;
  one(2, 0) = 5;
  one(2, 1) = 9;
  one(2, 2) = 6;
  one(2, 3) = 5;
  one(3, 0) = 4;
  one(3, 1) = 6;
  one(3, 2) = 7;
  one(3, 3) = 8;

  double det = one.Determinant();
  EXPECT_DOUBLE_EQ(651, det);
}

TEST(test_matrix, determinant_false) {
  S21Matrix one(3, 2);
  EXPECT_THROW(one.Determinant(), std::length_error);
}

TEST(MatrixTest, inverse_matrix_true) {
  S21Matrix one(3, 3);
  S21Matrix two(3, 3);
  S21Matrix result(3, 3);

  one(0, 0) = 2;
  one(0, 1) = 5;
  one(0, 2) = 7;
  one(1, 0) = 6;
  one(1, 1) = 3;
  one(1, 2) = 4;
  one(2, 0) = 5;
  one(2, 1) = -2;
  one(2, 2) = -3;

  result(0, 0) = 1;
  result(0, 1) = -1;
  result(0, 2) = 1;
  result(1, 0) = -38;
  result(1, 1) = 41;
  result(1, 2) = -34;
  result(2, 0) = 27;
  result(2, 1) = -29;
  result(2, 2) = 24;

  two = one.InverseMatrix();
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      EXPECT_EQ(two(i, j), result(i, j));
    }
  }
}

TEST(test_matrix, inverse_matrix_false) {
  S21Matrix one(3, 3);

  one(0, 0) = 2;
  one(0, 1) = 5;
  one(0, 2) = 7;
  one(1, 0) = 3;
  one(1, 1) = 6;
  one(1, 2) = 4;
  one(2, 0) = 2;
  one(2, 1) = 5;
  one(2, 2) = 7;

  EXPECT_THROW(one.InverseMatrix(), std::length_error);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
