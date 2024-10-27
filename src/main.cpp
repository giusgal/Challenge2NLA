#include <iostream>
#include <Eigen/Sparse>

#include "../include/utils.hpp"

using Image = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;

int main() {
    /*
    TASK 1
    Load the image as an Eigen matrix A with size m×n. Each entry in the matrix corresponds
    to a pixel on the screen and takes a value somewhere between 0 (black) and 255 (white).
    Compute the matrix product A^TA and report the euclidean norm of A^TA.
    */

    Image A;
    Utils::loadImage("../data/Einstein.jpg", A);

    Image ATA{A.transpose()*A};
    double ATAnorm = ATA.norm();
    std::cout << "[INFO] norm(ATA) = " << ATAnorm << std::endl;

    /*
    TASK2
    Solve the eigenvalue problem A^TAx = λx using the proper solver provided by the Eigen
    library. Report the two largest computed singular values of A.
    */



    return 0;
}
