#include <iostream>
#include <string>
#include "../include/utils.hpp"
#include <Eigen/Sparse>

using Image = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

int main() {
    std::string originalPath = "../data/Einstein.jpg";

    /*
     * TASK 1
     *
     * Load the image as an Eigen matrix A with size m×n. Each entry in the matrix corresponds
     * to a pixel on the screen and takes a value somewhere between 0 (black) and 255 (white).
     * Compute the matrix product ATA and report the euclidean norm of ATA.
     * */

    Image A;
    Utils::loadImage("../data/Einstein.jpg", A);

    Image ATA = A.transpose()*A;
    double ATAnorm = ATA.norm();
    std::cout << "[INFO] norm(ATA) = " << ATAnorm << std::endl;

    return 0;
}
