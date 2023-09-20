#include <iostream>
#include <string>
#include <fstream>
#include "processing.hpp"
#include "Image.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4 || argc > 5) {
        std::cerr << "Please provide at least all arguments." << std::endl;
        return 1;
    }

    std::string fileInputName = argv[1];
    std::string fileOutputName = argv[2];
    int newWidth = std::stoi(argv[3]);
    //int newHeight = std::stoi(argv[4]);
    
    std::ifstream fin;
    fin.open(fileInputName.c_str());
    if (!fin.is_open()) {
        std::cerr << "Error: cannot open file " << fileInputName << std::endl;
        return 1;
    }
    Image* img = new Image;
    Image_init(img, 0, 0);
    Image_init(img, fin);
    fin.close();
    if(argc == 5){
        int newHeight = std::stoi(argv[4]);
        seam_carve(img, newWidth, newHeight);
    }else{
        seam_carve(img, newWidth, img->height);
    }
    std::ofstream fout;
    fout.open(fileOutputName.c_str());
    if (!fout.is_open()) {
        std::cerr << "Error: cannot open file " << fileOutputName << std::endl;
        return 1;
    }
    Image_print(img, fout);
    fout.close();
    delete img;

    return 0;
}
