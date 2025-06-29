#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <stdexcept>


#include "meshGeneration.h"
#include "makeMatrixEquation.h"
#include "solver.h"

// プラットフォーム別
#ifdef _WIN32
#define API_EXPORT __declspec(dllexport)
#else
#define API_EXPORT
#endif

// extern "C"でC++の関数であることを明示する。
extern "C" API_EXPORT void run_1d_heat_conduction(
    double total_length, 
    int num_cells, 
    double heat_conductance, 
    double heat_source,
    double boundary_T_left, 
    double boundary_T_right,
    double tolerance, 
    int max_iteration,
    bool makeMidResidual, // 残差計算の出力有無
    const char* output_csv_filename // 結果を出力するCSVファイル名
);