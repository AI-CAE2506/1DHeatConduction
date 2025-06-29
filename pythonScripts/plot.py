import pandas as pd
import matplotlib.pyplot as plt

if __name__ == "__main__":
# グラフ作成
    # CSVファイルからデータの取得
    # NumericalData = pd.read_csv(InputData.get("output_csv_filename"))
    NumericalData = pd.read_csv("Numerical_Solution.csv")    
    AnalyticalData = pd.read_csv("analytical_solution.csv")

    # print(NumericalData)
    # print(AnalyticalData)

    # 数値解を点でプロット。データはヘッダー名で指定する。この時、空白も反映されるので注意。
    plt.scatter(
        NumericalData['Cell_Center'], 
        NumericalData['Numerical_Solution'], 
        label="Numerical solution"
        ) 
    # 解析解をラインプロット
    plt.plot(
        AnalyticalData['Cell_Center'], 
        AnalyticalData['Analytical_solution'], 
        label="Analytical solution"
        )
    plt.xlabel("Position [m]") # x軸のラベル
    plt.ylabel("Temperature [K]") # y軸のラベル
    plt.legend() # 凡例の表示

    plt.savefig("1D_Heat_Conduction.png") # 画像として保存。

    # plt.show()