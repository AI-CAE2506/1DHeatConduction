#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>


int makeCoeffMatrix(double k_deltax, std::vector<std::vector<double>> &matrix_coeff);

int makeVector_b(
    double boundary_T_left, 
    double boundary_T_right, 
    double k_deltax, 
    double heatSourceCell, 
    std::vector<double> &vectot_b);

void printCoefffMatrix(std::vector<std::vector<double>> &matrix_coeff);

void printVector(std::vector<double> &vectot_b, std::string vectorDescription);