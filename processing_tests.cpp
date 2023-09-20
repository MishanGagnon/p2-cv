#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cassert>
#include <cstring>
#include "Image.hpp"
#include "processing.hpp"
#include "Matrix_test_helpers.hpp"
#include "Image_test_helpers.hpp"

using namespace std;

void test_all(string prefix, int sizes[], int num_sizes);
void test_rotate(const Image *img, string prefix);
void test_energy(const Matrix *energy_mat, string prefix);
void test_cost(const Matrix *cost_mat, string prefix);
void test_find_seam(const int seam[], int n, string prefix);
void test_remove_seam(const Image* img, const int seam[],
                             string prefix);
void test_seam_carve(const Image *img, string prefix,
                            int new_width, int new_height);

static void load_matrix(Matrix* mat, string filename);
static void write_matrix(const Matrix* mat, string filename);
static void load_image(Image* img, string filename);
static void write_image(const Image* img, string filename);
static void load_seam(int seam[], string filename);
static void write_seam(const int seam[], int len, string filename);

const string OUT_PPM_EXT = ".out.ppm";
const string OUT_TXT_EXT = ".out.txt";

int main(int argc, char *argv[]){
  if (argc > 2 ||
      (argc == 2&&
       strcmp(argv[1], "dog") &&
       strcmp(argv[1], "crabster") &&
       strcmp(argv[1], "horses"))) {
    cout << "Usage: " << argv[0] << " [dog|crabster|horses]" << endl;
    return 1;
  }

  string which_test = argc == 2 ? argv[1] : "all";

  if (which_test == "all" || which_test == "dog") {
    int dog_sizes[] = {4, 5};
    test_all("dog", dog_sizes, 1);
  }
  if (which_test == "all" || which_test == "crabster") {
    int crabster_sizes[] = {50, 45, 70, 35};
    test_all("crabster", crabster_sizes, 2);
  }
  if (which_test == "all" || which_test == "horses") {
    int horses_sizes[] = {300, 382, 400, 250};
    test_all("horses", horses_sizes, 2);
  }
}

void test_all(string prefix, int sizes[], int num_sizes){
  Image* img = new Image;
  load_image(img, prefix + ".ppm");

  // Test rotate
  test_rotate(img, prefix);

  // Test energy
  Matrix* energy = new Matrix;
  compute_energy_matrix(img, energy);
  test_energy(energy, prefix);

  // Test cost
  Matrix*  cost = new Matrix;
  compute_vertical_cost_matrix(energy, cost);
  test_cost(cost, prefix);

  // Test find seam
  int seam[MAX_MATRIX_HEIGHT];
  find_minimal_vertical_seam(cost, seam);
  test_find_seam(seam, Matrix_height(cost), prefix);

  // Test remove seam
  test_remove_seam(img, seam, prefix);

  // Test full seam carving algorithm on various sizes
  for(int i = 0; i < num_sizes; ++i){
    test_seam_carve(img, prefix, sizes[2*i], sizes[2*i + 1]);
  }

  cout << prefix << " tests PASS" << endl << endl;

  delete cost;
  delete energy;
  delete img;
}


void test_energy(const Matrix *energy_mat, string prefix){
  cout << "Testing " << prefix << " energy..." << flush;

  write_matrix(energy_mat, prefix + "_energy" + OUT_TXT_EXT);

  Matrix* energy_mat_correct = new Matrix;
  load_matrix(energy_mat_correct, prefix + "_energy_correct.txt");

  assert(Matrix_equal(energy_mat, energy_mat_correct));
  cout << "PASS" << endl;
  delete energy_mat_correct;
}


