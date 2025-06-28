#include "makeMatrixEquation.h"

int makeCoeffMatrix(double k_deltax, std::vector<std::vector<double>> &matrix_coeff){
    int row_size = matrix_coeff.size();
    // int column_size = matrix_coeff[0].size();

    // 三角行列の性質を活かして、繰り返しを行方向だけにする。
    for(int i = 0; i < row_size; i++){
        // 左側境界
        if (i == 0){
            matrix_coeff[i][0] = 2*k_deltax + k_deltax;
            matrix_coeff[i][1] = -k_deltax;            
        }
        // 右側境界
        else if (i == row_size-1){
            matrix_coeff[i][i] = 2*k_deltax + k_deltax;
            matrix_coeff[i][i-1] = -k_deltax;                     
        }
        else{
            matrix_coeff[i][i] = 2*k_deltax;
            matrix_coeff[i][i-1] = -k_deltax;
            matrix_coeff[i][i+1] = -k_deltax;
        }           

    }
    return 0;
}


int makeVector_b(
    double boundary_T_left, 
    double boundary_T_right, 
    double k_deltax, 
    double heatSourceCell, 
    std::vector<double> &vectot_b){
    
    int row_size = vectot_b.size();

    for (size_t i = 0; i < row_size; i++)
    {
        // 左側境界
        if (i == 0)
        {
            vectot_b[i] = 2.0*k_deltax * boundary_T_left + heatSourceCell;
        }
        // 右側境界
        else if (i == row_size-1)
        {
            vectot_b[i] = 2.0 * k_deltax * boundary_T_right + heatSourceCell;
        }
        else{
            vectot_b[i] = heatSourceCell;
        }
    }
    return 0;    
    
}


void printCoefffMatrix(std::vector<std::vector<double>> &matrix_coeff){
    int row_size = matrix_coeff.size();
    int column_size = matrix_coeff[0].size();

    const int field_width = 5;  // 表示文字数

    std::cout << std::fixed;
    std::cout << std::setprecision(1);

    std::cout << "係数行列" << std::endl;

    for (size_t i = 0; i < row_size; i++)
    {
        for (size_t j = 0; j < column_size; j++)
        {
            std::cout << std::setw(field_width) << std::right << matrix_coeff[i][j] << ", "; //表示文字数指定と右寄せを指定
        }
        std::cout << std::endl;
    }
}

void printVector(std::vector<double> &vectot_b, std::string vectorDescription){
    int row_size = vectot_b.size();

    std::cout << std::fixed;
    std::cout << std::setprecision(3);

    std::cout << vectorDescription << std::endl;
    
    for (size_t i = 0; i < row_size; i++)
    {
        std::cout << vectot_b[i] << ", " << std::endl;
    }
    // std::cout << std::endl;
}

