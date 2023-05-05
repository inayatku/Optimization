#include <iostream>
#include <vector>
#include <algorithm>
struct Item {
    int value;
    int weight;
};
int knapsack(const std::vector<Item>& items, int max_weight) {
    int num_items = items.size();
    std::vector<std::vector<int>> dp(num_items + 1, std::vector<int>(max_weight + 1, 0));
    for (int i = 1; i <= num_items; ++i) {
        for (int w = 1; w <= max_weight; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    return dp[num_items][max_weight];
}
int main() {
    std::vector<Item> items = {
        {60, 10},
        {100, 20},
        {120, 30},
    };
    int max_weight = 50;
    int max_value = knapsack(items, max_weight);
    std::cout << "Maximum value of items that can be packed in the knapsack: " << max_value << std::endl;
    return 0;
}
