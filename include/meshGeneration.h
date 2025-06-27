#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

std::vector<double> meshGeneration(double mesh_size, int num_cells);
void info_node(std::vector<double> position_node_center);
