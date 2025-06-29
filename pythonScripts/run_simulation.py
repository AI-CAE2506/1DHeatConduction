import ctypes
import os
import json
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


# 共有ライブラリのパスを指定 (ビルド環境による)
# macOS/Linux: libheat_conduction_solver.so または libheat_conduction_solver.dylib
# Windows: heat_conduction_solver.dll
lib_path = "../libheat_conduction_solver.dylib" # macOSの場合の例
solver_lib = ctypes.CDLL(lib_path)

# C++関数の引数と戻り値の型を定義 (ctypes.c_double, ctypes.c_int, ctypes.c_char_p など)
solver_lib.run_1d_heat_conduction.argtypes = [
    ctypes.c_double, 
    ctypes.c_int, 
    ctypes.c_double, 
    ctypes.c_double,
    ctypes.c_double, 
    ctypes.c_double,
    ctypes.c_double,
    ctypes.c_int,
    ctypes.c_bool,
    ctypes.c_char_p # 文字列をC++に渡す
]
solver_lib.run_1d_heat_conduction.restype = None # 戻り値がない場合


def getInputData():
    # 入力ファイルのパス
    InputfilePath = './input.json'

    # 入力ファイルを読み込む
    try:
        with open(InputfilePath, 'r', encoding='utf-8') as f:
            InputData = json.load(f)
    except FileNotFoundError:
        print(f"エラー: 設定ファイル '{InputfilePath}' が見つかりません。")
        exit()
    except json.JSONDecodeError:
        print(f"エラー: 設定ファイル '{InputfilePath}' のJSON形式が不正です。")
        exit()
    except Exception as e:
        print(f"エラー: 設定ファイルの読み込み中に予期せぬ問題が発生しました: {e}")
        exit()

    return InputData
    
def makeCellInfo(InputData):
    # セル中心位置を生成する。

    mesh_size = InputData.get("total_length") / InputData.get("num_cells")
    positionCellCenter = np.zeros(InputData.get("num_cells"))

    for i in range(InputData.get("num_cells")):
        if i == 0:
            positionCellCenter[i] = mesh_size / 2.0
        else:
            positionCellCenter[i] = positionCellCenter[i-1] + mesh_size
    
    return positionCellCenter

def analyticalSolution(InputData):
    # 発熱のない場合の1次元定常熱伝導方程式の解析解を生成する。

    positionCellCenter = makeCellInfo(InputData) # セル中心位置を取得

    T_result = np.zeros(InputData.get("num_cells"))
    
    for i in range(InputData.get("num_cells")):
        T_result[i] =(InputData.get("boundary_T_right") - InputData.get("boundary_T_left"))/InputData.get("total_length")
        T_result[i] = T_result[i] * positionCellCenter[i] + InputData.get("boundary_T_left")

    # 結果をCSVファイルに保存する。
    outdata = np.stack((positionCellCenter , T_result), axis=1)
    df = pd.DataFrame(outdata, columns=["Cell_Center", "Analytical_solution"])
    df.to_csv("analytical_solution.csv", index=False, float_format='%.5f')

    return T_result

# 呼び出される関数
if __name__ == "__main__":
    InputData = getInputData()

    # ライブラリを呼び出し、数値解を計算。
    solver_lib.run_1d_heat_conduction(
        InputData.get("total_length"),
        InputData.get("num_cells"),
        InputData.get("heat_conductance"),
        InputData.get("heat_source"),
        InputData.get("boundary_T_left"),
        InputData.get("boundary_T_right"),
        InputData.get("tolerance"),
        InputData.get("max_iteration"),
        InputData.get("makeMidResidual"),
        ctypes.c_char_p(InputData.get("output_csv_filename").encode('utf-8')) # C++へ渡せるようにエンコードを調整する。
    )

    # 解析解を生成する
    positionCellCenter = makeCellInfo(InputData)
    T_result = analyticalSolution(InputData)



    # outdata = np.stack((positionCellCenter , T_result), axis=0)
    # print(f'{"セル中心位置":>8} ,{"解析解":>8}' )
    # for i in range(InputData.get("num_cells")):
    #     print(f'{positionCellCenter[i]:12.3f}, {T_result[i]:12.4f}')
    # print(outdata)
    

