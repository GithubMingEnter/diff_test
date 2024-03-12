#include<iostream>
#include<vector>
#include <casadi/casadi.hpp>
#include<chrono>
#include<Eigen/Dense>

void vec_sx(){
    // Create a std::vector<Eigen::Vector2d>
    std::vector<Eigen::Vector2d> vector_of_vectors;
    vector_of_vectors.push_back(Eigen::Vector2d(1.0, 2.0));
    vector_of_vectors.push_back(Eigen::Vector2d(3.0, 4.0));
    vector_of_vectors.push_back(Eigen::Vector2d(5.0, 6.0));

    // Transform std::vector<Eigen::Vector2d> to casadi::SX
    
    casadi::SX matrix=casadi::SX(vector_of_vectors.size(),vector_of_vectors[0].size());
    
    int i=0;
    for (const auto& vec : vector_of_vectors) {
        casadi::SX row = casadi::SX::vertcat({vec[0], vec[1]});//col
        std::cout << row << std::endl;
        matrix(i++,casadi::Slice())=row; // slice by row
        casadi::SX col =casadi::SX::horzcat({vec[0],vec[1]});//row
                std::cout << col << std::endl;

        // matrix(i++)=row;
    }

    // Print the resulting casadi::SX matrix
    std::cout << "Resulting casadi::SX matrix:" << std::endl;
    std::cout << matrix << std::endl;
    std::cout << "slice matrix:" << std::endl;
    std::cout << matrix(casadi::Slice(1,3,1)) << std::endl; //1-3 row 0 col
    std::cout << matrix(0,casadi::Slice(0,2,1)) << std::endl;
}


int main()
{
    vec_sx();
    return 0;

}








