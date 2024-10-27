#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/SparseExtra>

#include "../include/utils.hpp"

using Image = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using spImage = Eigen::SparseMatrix<double, Eigen::RowMajor>;

// Just a semantic thing
using Vector = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using spVector = Eigen::SparseMatrix<double, Eigen::RowMajor>;

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
    
    // A^TA is symmetric => SelfAdjointEigenSolver
    Eigen::SelfAdjointEigenSolver<Image> eigensolver(ATA);
    if(eigensolver.info() != Eigen::Success) {
        std::cerr << "[ERROR] Couldn't compute eigenvalues of ATA" << std::endl;
        exit(1);
    }
    Vector ATAeigenvalues = eigensolver.eigenvalues();
    // std::cout << ATAeigenvalues << std::endl;
    
    // The singular values of A are the (ordered) square roots of the eigenvalues of A^TA,
    //  therefore
    double ATAmaxeigen1 = ATAeigenvalues(ATA.rows()-1);
    double ATAmaxeigen2 = ATAeigenvalues(ATA.rows()-2);
    std::cout << "[INFO] maxeigen1(A^TA) = " << ATAmaxeigen1 
        << std::endl;
    std::cout << "[INFO] maxeigen2(A^TA) = " << ATAmaxeigen2 
        << std::endl;
    double AsingularValue1 = std::sqrt(ATAmaxeigen1);
    double AsingularValue2 = std::sqrt(ATAmaxeigen2);
    std::cout << "[INFO] σ1(A) = " << AsingularValue1 << std::endl;
    std::cout << "[INFO] σ2(A) = " << AsingularValue2 << std::endl;


    // TODO: Check tolerances
    /*
    TASK3 (LIS) [execute solveLis.sh after this file]
    Export matrix ATA in the matrix market format and move it to the lis-2.1.6/test
    folder. Using the proper iterative solver available in the LIS library compute the largest
    eigenvalue of ATA up to a tolerance of 10^−8. Report the computed eigenvalue. Is the result
    in agreement with the one obtained in the previous point?

    Result:
     max_eig(A^TA) = 1.608332e+04 (it's the same)
     relative residual = 1.866013e-09
     iterations = 8
    */
    
    // Export the matrix
    if(!Eigen::saveMarket(ATA, "../data/ATA.mtx")) {
        std::cerr << "[ERROR] Couldn't save matrix ATA in the matrix market format" << std::endl;
        exit(1);
    }


    // TODO: See this better (check tolerances)
    /*
    TASK4 (LIS) [execute solveLis.sh after this file]
    Find a shift μ ∈ R yielding an acceleration of the previous eigensolver. Report μ and the
    number of iterations required to achieve a tolerance of 10^−8.
    
    Result:
     μ = 1000
     iterations = 7
    */


    /*
    TASK5
    Using the SVD module of the Eigen library, perform a singular value decomposition of the
    matrix A. Report the Euclidean norm of the diagonal matrix Σ of the singular values.
    */


    return 0;
}
