#include "input.h"

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
    params.makeMidResidual = data.at("makeMidResidual").get<bool>();
    params.output_csv_filename = data.at("output_csv_filename").get<std::string>();

    return params;
}