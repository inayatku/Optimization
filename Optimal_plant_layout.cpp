#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

struct Machine {
    int id;
    int x;
    int y;
};

int calculate_distance(const Machine& a, const Machine& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int calculate_total_distance(const std::vector<Machine>& layout) {
    int total_distance = 0;
    for (size_t i = 0; i < layout.size(); ++i) {
        for (size_t j = i + 1; j < layout.size(); ++j) {
            total_distance += calculate_distance(layout[i], layout[j]);
        }
    }
    return total_distance;
}

std::vector<Machine> generate_random_layout(int num_machines, int grid_size) {
    std::vector<Machine> layout(num_machines);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, grid_size - 1);

    for (int i = 0; i < num_machines; ++i) {
        layout[i] = {i, dis(gen), dis(gen)};
    }

    return layout;
}

std::vector<Machine> mutate_layout(const std::vector<Machine>& layout, int grid_size) {
    std::vector<Machine> mutated_layout(layout);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, grid_size - 1);
    std::uniform_int_distribution<> machine_dis(0, layout.size() - 1);

    int index = machine_dis(gen);
    mutated_layout[index].x = dis(gen);
    mutated_layout[index].y = dis(gen);

    return mutated_layout;
}

int main() {
    int grid_size = 10;
    int num_machines = 5;
    int num_iterations = 10000;

    std::vector<Machine> best_layout = generate_random_layout(num_machines, grid_size);
    int best_distance = calculate_total_distance(best_layout);

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine dre(seed);
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < num_iterations; ++i) {
        std::vector<Machine> mutated_layout = mutate_layout(best_layout, grid_size);
        int mutated_distance = calculate_total_distance(mutated_layout);

        if (mutated_distance < best_distance || distribution(dre) < 0.05) {
            best_layout = mutated_layout;
            best_distance = mutated_distance;
        }
    }

    std::cout << "Optimal layout with total distance: " << best_distance << std::endl;
    for (const auto& machine : best_layout) {
        std::cout << "Machine " << machine.id << " at (" << machine.x << ", " << machine.y << ")" << std::endl;
    }

    return 0;
}
