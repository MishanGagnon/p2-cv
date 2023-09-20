#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image;

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  ostringstream s;
  Image_print(img, s);

  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; 
}
TEST(test_Image_init) {
    Image* img = new Image;
    Image_init(img, 2, 2);
    Image_fill(img, {0, 0, 0});

    ASSERT_EQUAL(Image_get_pixel(img, 0, 1).r, 0);
    ASSERT_EQUAL(Image_get_pixel(img, 1, 1).g, 0);
    ASSERT_EQUAL(Image_get_pixel(img, 0, 1).b, 0);
    ASSERT_EQUAL(img->width, 2);
    ASSERT_EQUAL(img->height, 2);
    delete img;
}

TEST(test_Image_init_from_stream) {
    std::stringstream ss;
    ss << "P3\n2 2\n255\n255 0 0 0 255 0 0 0 255 255 255 255\n";

    Image* img = new Image;
    Image_init(img, ss);

    ASSERT_EQUAL(Image_get_pixel(img,1,1).r, 255);
    ASSERT_EQUAL(Image_get_pixel(img,1,1).g, 0);
    ASSERT_EQUAL(Image_get_pixel(img,1,1).b, 0);
    ASSERT_EQUAL(img->width, 2);
    ASSERT_EQUAL(img->height, 2);
    delete img;
}

TEST(test_Image_width) {
    Image* img = new Image;
    Image_init(img, 3, 4);
    ASSERT_EQUAL(Image_width(img), 3);
    delete img;
}

TEST(test_Image_height) {
    Image* img = new Image;
    Image_init(img, 3, 4);
    ASSERT_EQUAL(Image_height(img), 4);
    delete img;
}

TEST(test_Image_get_pixel) {
    Image* img = new Image;
    Image_init(img, 2, 2);
    Pixel p = {255, 128, 64};
    Image_set_pixel(img, 1, 1, p);
    
    Pixel fetchedPixel = Image_get_pixel(img, 1, 1);
    ASSERT_EQUAL(fetchedPixel.r, 255);
    ASSERT_EQUAL(fetchedPixel.g, 128);
    ASSERT_EQUAL(fetchedPixel.b, 64);
    delete img;
}

TEST(test_Image_set_pixel) {
    Image* img = new Image;
    Image_init(img, 2, 2);
    Pixel p = {255, 128, 64};
    Image_set_pixel(img, 1, 1, p);
    
    ASSERT_EQUAL(Image_get_pixel(img,1,1).r, 255);
    ASSERT_EQUAL(Image_get_pixel(img,1,1).g, 128);
    ASSERT_EQUAL(Image_get_pixel(img,1,1).b, 64);
    delete img;
}

TEST(test_Image_fill) {
    Image* img = new Image;
    Image_init(img, 2, 2);
    
    Pixel fill_color = {123, 45, 67};
    Image_fill(img, fill_color);

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            Pixel current_pixel = Image_get_pixel(img, i, j);
            ASSERT_EQUAL(current_pixel.r, fill_color.r);
            ASSERT_EQUAL(current_pixel.g, fill_color.g);
            ASSERT_EQUAL(current_pixel.b, fill_color.b);
        }
    }

    delete img;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
