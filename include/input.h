#pragma once

#include <iostream>
#include <fstream> // ファイル操作に必要
#include <string> // 文字列操作に必要
#include <nlohmann/json.hpp> // nlohmann/json ライブラリのヘッダ

// nlohmann::json を使うためのusing宣言（または都度 nlohmann::json::parse などと記述）
using json = nlohmann::json;

// 設定を保持する構造体などを作成すると、コードが整理されます
struct SimulationParameters {
    double total_length;
    int num_cells;
    double heat_conductance;
    double heat_source;
    double boundary_T_left;
    double boundary_T_right;
    double tolerance;
    int max_iteration;
    bool makeMidResidual;
    std::string output_csv_filename;
};

SimulationParameters readParametersFromJson(const std::string& filename);