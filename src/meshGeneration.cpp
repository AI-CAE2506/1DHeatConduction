#include "meshGeneration.h"

std::vector<double> meshGeneration(double mesh_size, int num_cells){
    // 1次元の長さと分割数から等分割メッシュを生成する関数
    // @param mesh_size: セルの幅
    // @param num_cells: 分割数
    // @return position_node_center: ノード中心の座標


    std::vector<double> position_node_center;

    // ノード中心の座標を計算して、position_node_centerに追加する。
    for( int i = 0; i < num_cells; i++) {
        if( i == 0){
            position_node_center.push_back(mesh_size/2);
        }
        // else if(i==num_cells){
        //     position_node_center.push_back(position_node_center[i-1]+mesh_size/2);
        // }
        else{
            position_node_center.push_back(position_node_center[i-1]+mesh_size);
        }
    }

    info_node(position_node_center);

    return position_node_center;
}


void info_node(std::vector<double> position_node_center){
    int num_nodes = position_node_center.size();

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << "ノード数: " << num_nodes << std::endl;
    for(int i = 0; i < num_nodes; i++){
        if (i == 0){
            std::cout << "ノード番号, " << "ノード中心位置" << std::endl;
        }
        std::cout << i << " , " <<  position_node_center[i] << std::endl;
    }
}

