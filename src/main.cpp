#include "main.h"

int main(){
    double total_length = 1.0;  //  [m]
    const int num_cells = 10;
    double heatConductance = 1.0; // [W/(mK)]
    double heatSource = 0.0;  // [W/m3]

    double mesh_size = total_length / num_cells;    

    // メッシュ分割とセル中心位置の取得
    std::vector<double> position_node_center = meshGeneration(mesh_size, num_cells);

    // int row_size = num_cells;
    // int column_size = num_cells;
    
    // 行列、ベクトルの作成・初期化
    std::vector<std::vector<double>> matrix_coeff(num_cells, std::vector<double>(num_cells, 0.0));
    std::vector<double> vectot_T(num_cells, 0.0);
    std::vector<double> vectot_b(num_cells, 0.0);    
    
    double boundary_T_left = 100.0;  // [K]
    double boundary_T_right = 20.0;  // [K]

    // 境界条件は方程式の差分化の段階でbベクトルに組み込まれる。
    // 具体的にはb0とb_{num_cells}に現れる。

    double k_deltax = heatConductance / mesh_size;
    double heatSourceCell = heatSource * mesh_size;

    makeCoeffMatrix(k_deltax, matrix_coeff);
    makeVector_b(boundary_T_left, boundary_T_right, k_deltax, heatSourceCell, vectot_b);

    printCoefffMatrix(matrix_coeff);
    printVector_b(vectot_b);

    return 0;

}


