#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic)
{
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, 42);

    for (int r = 0; r < height; ++r)
    {
        for (int c = 0; c < width; ++c)
        {
            cout << *Matrix_at(mat, r, c) << " ";
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
        cout << endl;
    }

    delete mat; // delete the Matrix
}
TEST(test_matrix_init)
{
    Matrix *mat = new Matrix;

    const int width = 3;
    const int height = 5;
    Matrix_init(mat, width, height);

    ASSERT_EQUAL(Matrix_width(mat), width);
    ASSERT_EQUAL(Matrix_height(mat), height);
    delete mat;
}

TEST(test_matrix_print)
{
    Matrix *mat = new Matrix;
    const int width = 2;
    const int height = 2;
    const int value = 5;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, value);

    std::stringstream ss;
    Matrix_print(mat, ss);

    std::string expected_output = "2 2\n5 5 \n5 5 \n";
    ASSERT_EQUAL(ss.str(), expected_output);
    delete mat;
}

TEST(test_matrix_fill)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 7);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            ASSERT_EQUAL(*Matrix_at(mat, i, j), 7);
        }
    }
    delete mat;
}

// TEST FOR Matrix_max
TEST(test_matrix_max)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 3, 3);
    int values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            *Matrix_at(mat, i, j) = values[i * 3 + j];
        }
    }
    ASSERT_EQUAL(Matrix_max(mat), 9);
    delete mat;
}

// TEST FOR Matrix_column_of_min_value_in_row
TEST(test_matrix_column_of_min_value_in_row)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 4);
    int values[16] = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      8, 7, 6, 5,
                      4, 3, 2, 1};
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            *Matrix_at(mat, i, j) = values[i * 4 + j];
        }
    }
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 2, 1, 3), 2);
    delete mat;
}

TEST(test_matrix_height)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 6);
    ASSERT_EQUAL(Matrix_height(mat), 6);
    delete mat;
}

// TEST FOR Matrix_width
TEST(test_matrix_width)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 6);
    ASSERT_EQUAL(Matrix_width(mat), 4);
    delete mat;
}

// TEST FOR Matrix_row
TEST(test_matrix_row)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 6);
    int *ptr = Matrix_at(mat, 2, 3);
    ASSERT_EQUAL(Matrix_row(mat, ptr), 2);
    delete mat;
}

// TEST FOR Matrix_column
TEST(test_matrix_column)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 6);
    int *ptr = Matrix_at(mat, 2, 3);
    ASSERT_EQUAL(Matrix_column(mat, ptr), 3);
    delete mat;
}

// TEST FOR Matrix_fill_border
TEST(test_matrix_fill_border)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 4, 4);
    Matrix_fill(mat, 0);
    Matrix_fill_border(mat, 5);

    // Check all border elements
    for (int i = 0; i < 4; ++i)
    {
        ASSERT_EQUAL(*Matrix_at(mat, i, 0), 5);
        ASSERT_EQUAL(*Matrix_at(mat, i, 3), 5);
    }
    for (int j = 0; j < 4; ++j)
    {
        ASSERT_EQUAL(*Matrix_at(mat, 0, j), 5);
        ASSERT_EQUAL(*Matrix_at(mat, 3, j), 5);
    }
    delete mat;
}

// TEST FOR Matrix_min_value_in_row
TEST(test_matrix_min_value_in_row)
{
    Matrix *mat = new Matrix;
    Matrix_init(mat, 2, 2);

    int values[4] = {4, 7,
                     6, 2};

    *Matrix_at(mat, 0, 0) = values[0];
    *Matrix_at(mat, 0, 1) = values[1];
    *Matrix_at(mat, 1, 0) = values[2];
    *Matrix_at(mat, 1, 1) = values[3];

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 2), 4);

    delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
