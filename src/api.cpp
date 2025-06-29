#include "api.h"

extern "C" API_EXPORT void run_1d_heat_conduction(
    double total_length, 
    int num_cells, 
    double heat_conductance, 
    double heat_source,
    double boundary_T_left, 
    double boundary_T_right,
    double tolerance, 
    int max_iteration,
    bool makeMidResidual,
    const char* output_csv_filename // 結果を出力するCSVファイル名
){
    try {
        double mesh_size = total_length / num_cells;    

        // メッシュ分割とセル中心位置の取得
        std::vector<double> position_node_center = meshGeneration(mesh_size, num_cells);

        // int row_size = num_cells;
        // int column_size = num_cells;
        
        // 行列、ベクトルの作成・初期化
        std::vector<std::vector<double>> matrix_coeff(
            num_cells, 
            std::vector<double>(num_cells, 0.0)
        );
        std::vector<double> vectot_T(num_cells, 0.0);
        std::vector<double> vectot_b(num_cells, 0.0);    
        
        // 共通の定数を定義しておく
        double k_deltax = heat_conductance / mesh_size;
        double heatSourceCell = heat_source * mesh_size;

        makeCoeffMatrix(k_deltax, matrix_coeff);
        makeVector_b(
            boundary_T_left, 
            boundary_T_right, 
            k_deltax, 
            heatSourceCell, 
            vectot_b
        );

        printCoefffMatrix(matrix_coeff);
        printVector(vectot_b, "右辺ベクトル");

        // double torelance = 1.e-6;
        // int max_iteration = 100;

        std::vector<double> vectot_T_result = solveByJacobi(
            matrix_coeff, 
            vectot_b, 
            tolerance, 
            max_iteration,
            makeMidResidual
        );
        printVector(vectot_T_result, "解ベクトル");

        std::ofstream resultfile;
        resultfile.open(output_csv_filename);
        if (!resultfile.is_open()){
            std::cerr << "ファイルが開けません: " << output_csv_filename << std::endl;
            return;
        }
        resultfile << std::fixed;
        resultfile << std::setprecision(4);
        resultfile << "Cell_Center" << "," << "Numerical_Solution" << std::endl;        
        for (int i = 0; i < num_cells; i++){
            resultfile << position_node_center[i] << ", " << vectot_T_result[i] << std::endl;
        }
        if (resultfile.is_open()){ resultfile.close(); }


    } catch (const std::exception& e) {
        std::cerr << "エラーが発生しました: " << e.what() << std::endl;
    }

}


