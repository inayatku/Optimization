#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

struct Task {
    int id;
    int optimistic_time;
    int most_likely_time;
    int pessimistic_time;
    std::vector<int> predecessors;
    double expected_time;
    double variance;
};

int main() {
    std::vector<Task> tasks = {
        {0, 1, 4, 7, {}},
        {1, 2, 5, 8, {0}},
        {2, 2, 5, 14, {0}},
        {3, 1, 5, 9, {1}},
        {4, 3, 6, 9, {1, 2}},
        {5, 2, 3, 10, {3, 4}}
    };

    int n = tasks.size();
    std::vector<double> earliest_start(n, 0);

    for (Task& task : tasks) {
        task.expected_time = (task.optimistic_time + 4 * task.most_likely_time + task.pessimistic_time) / 6.0;
        task.variance = pow((task.pessimistic_time - task.optimistic_time) / 6.0, 2);

        for (int predecessor : task.predecessors) {
            earliest_start[task.id] = std::max(earliest_start[task.id], earliest_start[predecessor] + tasks[predecessor].expected_time);
        }
    }

    int end_task_id = -1;
    double max_duration = 0;

    for (int i = 0; i < n; i++) {
        if (tasks[i].expected_time + earliest_start[i] > max_duration) {
            max_duration = tasks[i].expected_time + earliest_start[i];
            end_task_id = i;
        }
    }

    std::vector<int> critical_path = {end_task_id};

    for (int i = end_task_id; i >= 0;) {
        int next_task_id = -1;

        for (int predecessor : tasks[i].predecessors) {
            if (earliest_start[i] - tasks[predecessor].expected_time == earliest_start[predecessor]) {
                next_task_id = predecessor;
                break;
            }
        }

        if (next_task_id == -1) {
            break;
        }

        critical_path.push_back(next_task_id);
        i = next_task_id;
    }

    std::reverse(critical_path.begin(), critical_path.end());

    std::cout << "Project duration (expected time): " << max_duration << std::endl;
    std::cout << "Critical path: ";

    for (int task_id : critical_path) {
        std::cout << "Task " << task_id << " -> ";
    }

    std::cout << "End" << std::endl;

    return 0;
}
