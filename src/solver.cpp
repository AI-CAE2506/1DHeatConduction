#include "solver.h"

std::vector<double> solveByJacobi(
    const std::vector<std::vector<double>>& A, //係数行列式
    const std::vector<double>& b, //右辺ベクトル
    double torelance, // 許容誤差
    int max_iteration // 最大反復回数
) {
    int mesh_size = A.size();
    std::vector<double> T_current(mesh_size, 0.0); // 解の初期化

    std::vector<double> T_prev; // 前回の計算値を格納する
    T_prev = T_current;


    for (int i = 0; i < mesh_size; i++)
    {
        if (A[i][i] == 0.0)
        {
            std::cout << "対角要素に0要素が含まれています。別の方法を検討してください" << std::endl;
            return T_current;
        }
    }
    


    for (int i_conv = 0; i_conv < max_iteration; i_conv++)
    {
        // 三角行列のため、iのみの繰り返しとする。
        for (int i = 0; i < mesh_size; i++) {
            double sum = 0.0;
            
            // 境界部分は場合分け。
            if (i == 0)
            {
                sum = A[i][i+1] * T_prev[i+1];
            }
            else if (i == mesh_size-1)
            {
                sum = A[i][i-1] * T_prev[i-1];
            }
            else
            {
                sum = A[i][i-1] * T_prev[i-1] + A[i][i+1] * T_prev[i+1];
            }
            
            T_current[i] = (b[i] - sum) / A[i][i];
        }

        double norm = calculateNorm(T_current, T_prev);

        // 収束判定 
        // 修正：T_prev = T_currentを外に出す
        if (norm < torelance) break;
        //     break;
        // }
        // else{
        //     T_prev = T_current;
        // }
        T_prev = T_current;
        
        // 最大繰り返し回数のエラー処理
        // 判定式を修正
        // if (i_conv == max_iteration)
        if (i_conv == max_iteration-1 && norm >= torelance)
        {
            std::cout << "最大繰り返し数を超えました。解は参考値です。" << std::endl;
        }
        
    }

    return T_current;

}

double calculateNorm(const std::vector<double>& T_current, const std::vector<double>& T_prev){
    int mesh_size = T_current.size();
    std::vector<double> difference(mesh_size, 0.0);

    for (int i = 0; i < mesh_size; i++)
    {
        difference[i] = std::abs(T_current[i] - T_prev[i]);
    }

    double norm = *std::max_element(difference.begin(), difference.end());

    return norm;


}
