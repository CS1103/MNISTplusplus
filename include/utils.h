#pragma once
#include "matrix.h"
#include <vector>
std::pair<int, int> argmax(Matrix<double> mat);

std::filesystem::path find_project_root();
std::filesystem::path get_absolute_path(const char* relative_path);