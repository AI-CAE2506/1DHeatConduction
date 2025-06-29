#include "main.h"

int main(){

    // インプットファイルから入力データを読み込む
    SimulationParameters input_params = readParametersFromJson("input.json");

    // C++から実行するときはこちらを実行。
    run_1d_heat_conduction(
        input_params.total_length, 
        input_params.num_cells, 
        input_params.heat_conductance, 
        input_params.heat_source,
        input_params.boundary_T_left, 
        input_params.boundary_T_right,
        input_params.tolerance, 
        input_params.max_iteration,
        input_params.makeMidResidual,
        input_params.output_csv_filename.c_str() // 結果を出力するCSVファイル名
    );

    // 以下のコア部分は"api.cpp"に移動

    // try {


    //     double mesh_size = input_params.total_length / input_params.num_cells;    

    //     // メッシュ分割とセル中心位置の取得
    //     std::vector<double> position_node_center = meshGeneration(mesh_size, input_params.num_cells);

    //     // int row_size = num_cells;
    //     // int column_size = num_cells;
        
    //     // 行列、ベクトルの作成・初期化
    //     std::vector<std::vector<double>> matrix_coeff(
    //         input_params.num_cells, 
    //         std::vector<double>(input_params.num_cells, 0.0)
    //     );
    //     std::vector<double> vectot_T(input_params.num_cells, 0.0);
    //     std::vector<double> vectot_b(input_params.num_cells, 0.0);    
        
    //     // boundary_T_left = 100.0;  // [K]
    //     // boundary_T_right = 20.0;  // [K]

    //     // 境界条件は方程式の差分化の段階でbベクトルに組み込まれる。
    //     // 具体的にはb0とb_{num_cells}に現れる。

    //     double k_deltax = input_params.heat_conductance / mesh_size;
    //     double heatSourceCell = input_params.heat_source * mesh_size;

    //     makeCoeffMatrix(k_deltax, matrix_coeff);
    //     makeVector_b(
    //         input_params.boundary_T_left, 
    //         input_params.boundary_T_right, 
    //         k_deltax, 
    //         heatSourceCell, 
    //         vectot_b
    //     );

    //     printCoefffMatrix(matrix_coeff);
    //     printVector(vectot_b, "右辺ベクトル");

    //     // double torelance = 1.e-6;
    //     // int max_iteration = 100;

    //     std::vector<double> vectot_T_result = solveByJacobi(
    //         matrix_coeff, 
    //         vectot_b, 
    //         input_params.tolerance, 
    //         input_params.max_iteration
    //     );
    //     printVector(vectot_T_result, "解ベクトル");

    // } catch (const std::exception& e) {
    //     std::cerr << "エラーが発生しました: " << e.what() << std::endl;
    //     return 1;
    // }

    return 0;

}


