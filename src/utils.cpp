#include "utils.h"
#include <filesystem>
using namespace std;

std::pair<int, int> argmax(Matrix<double> mat) {
    pair<int, int> result;
    double max = mat[0][0];
    for (int i = 0; i < mat.get_rows(); i++)
        for (int j = 0; j < mat.get_cols(); j++)
            if (mat[i][j] > max) {
                max = mat[i][j];
                result.first = i;
                result.second = j;
            }
    return result;
}


std::filesystem::path find_project_root() {
    auto current_path = std::filesystem::current_path();
    auto project_directory = std::filesystem::path("MNISTplusplus");
    while (current_path != current_path.root_path()) {
        if (std::filesystem::exists(current_path / "MNISTplusplus")) {
            return std::filesystem::path(current_path / project_directory);
        }
        current_path = current_path.parent_path();
    }
    throw std::runtime_error("Project root not found.");
}

std::filesystem::path get_absolute_path(const char* relative_path) {
    std::filesystem::path base_path = find_project_root();
    std::filesystem::path absolute_path = base_path /  std::filesystem::path(std::string(relative_path));
    return absolute_path;
}