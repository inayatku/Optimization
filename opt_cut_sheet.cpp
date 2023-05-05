#include <iostream>
#include <vector>
#include <algorithm>

int cutSheet(const std::vector<std::vector<int>>& prices, int width, int height) {
    std::vector<std::vector<int>> revenue(height + 1, std::vector<int>(width + 1, 0));

    for (int i = 1; i <= height; ++i) {
        for (int j = 1; j <= width; ++j) {
            int maxRevenue = prices[i][j];
            for (int k = 1; k <= i / 2; ++k) {
                maxRevenue = std::max(maxRevenue, revenue[k][j] + revenue[i - k][j]);
            }
            for (int k = 1; k <= j / 2; ++k) {
                maxRevenue = std::max(maxRevenue, revenue[i][k] + revenue[i][j - k]);
            }
            revenue[i][j] = maxRevenue;
        }
    }

    return revenue[height][width];
}

int main() {
    std::vector<std::vector<int>> prices = {
        {0, 0, 0, 0, 0},
        {0, 2, 3, 6, 9},
        {0, 3, 5, 10, 12},
        {0, 4, 7, 12, 16}
    };
    int width = 4;
    int height = 3;

    int maxRevenue = cutSheet(prices, width, height);

    std::cout << "Maximum revenue for a sheet of width " << width << " and height " << height << ": " << maxRevenue << std::endl;

    return 0;
}
