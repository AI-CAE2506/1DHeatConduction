#include "input.h"

// // 設定を保持する構造体などを作成すると、コードが整理されます
// struct SimulationParameters {
//     double total_length;
//     int num_cells;
//     double heat_conductance;
//     double heat_source;
//     double boundary_t_left;
//     double boundary_t_right;
//     double solver_tolerance;
//     int solver_max_iterations;
// };

// JSONファイルからパラメータを読み込む関数
SimulationParameters readParametersFromJson(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Error: Could not open JSON file: " + filename);
    }

    json data;
    ifs >> data; // ファイルの内容をJSONオブジェクトにパース

    SimulationParameters params;
    // JSONオブジェクトから値を取得
    // .at() を使うとキーが存在しない場合に例外が発生するので、安全です
    params.total_length = data.at("total_length").get<double>();
    params.num_cells = data.at("num_cells").get<int>();
    params.heat_conductance = data.at("heat_conductance").get<double>();
    params.heat_source = data.at("heat_source").get<double>();
    params.boundary_T_left = data.at("boundary_T_left").get<double>();
    params.boundary_T_right = data.at("boundary_T_right").get<double>();
    params.tolerance = data.at("tolerance").get<double>();
    params.max_iteration = data.at("max_iteration").get<int>();

    return params;
}