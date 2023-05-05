#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Resource {
    string name;
    double cost;
    double value;
};

vector<Resource> knapsack(vector<Resource> resources, double budget) {
    int n = resources.size();
    vector<vector<double>> V(n+1, vector<double>(budget+1));
    for (int w = 0; w <= budget; w++) {
        V[0][w] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= budget; w++) {
            if (resources[i-1].cost <= w) {
                V[i][w] = max(V[i-1][w], V[i-1][w-resources[i-1].cost] + resources[i-1].value);
            } else {
                V[i][w] = V[i-1][w];
            }
        }
    }

    // Backtracking to find selected resources
    vector<Resource> selectedResources;
    double remainingBudget = budget;
    for (int i = n; i >= 1; i--) {
        if (V[i][remainingBudget] > V[i-1][remainingBudget]) {
            selectedResources.push_back(resources[i-1]);
            remainingBudget -= resources[i-1].cost;
        }
    }
    reverse(selectedResources.begin(), selectedResources.end());
    return selectedResources;
}

int main() {
    vector<Resource> resources = {
        {"Resource 1", 500.0, 1000.0},
        {"Resource 2", 800.0, 1200.0},
        {"Resource 3", 1000.0, 2000.0},
        {"Resource 4", 1500.0, 2500.0},
        {"Resource 5", 2000.0, 3000.0}
    };
    double budget = 3500.0;

    vector<Resource> selectedResources = knapsack(resources, budget);
    cout << "Selected resources for allocation:" << endl;
    for (auto r : selectedResources) {
        cout << r.name << endl;
    }
    return 0;
}
