#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <fstream>
#include <sstream>

std::vector<double> solveByJacobi(
    const std::vector<std::vector<double>>& A, //係数行列式
    const std::vector<double>& b, //右辺ベクトル
    double tolerance, // 許容誤差
    int max_iteration, // 最大反復回数
    bool makeMidResidual // 途中経過出力の実行有無
);

double calculateNorm(const std::vector<double>& T_current, const std::vector<double>& T_prev);
