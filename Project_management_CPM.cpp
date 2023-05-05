#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Task {
    int id;
    int duration;
    std::vector<int> predecessors;
};

void find_critical_path(const std::vector<Task>& tasks, int task_id, const std::vector<int>& earliest_start, std::vector<int>& critical_path) {
    critical_path.push_back(task_id);
    int earliest_completion = earliest_start[task_id] + tasks[task_id].duration;

    for (size_t i = 0; i < tasks.size(); i++) {
        if (std::find(tasks[i].predecessors.begin(), tasks[i].predecessors.end(), task_id) != tasks[i].predecessors.end()) {
            if (earliest_start[i] == earliest_completion) {
                find_critical_path(tasks, tasks[i].id, earliest_start, critical_path);
                break;
            }
        }
    }
}

int main() {
    std::vector<Task> tasks = {
        {0, 5, {}},
        {1, 6, {0}},
        {2, 8, {0}},
        {3, 6, {1}},
        {4, 1, {2}},
        {5, 3, {3, 4}}
    };

    int n = tasks.size();
    std::vector<int> earliest_start(n, 0);

    for (const Task& task : tasks) {
        for (int predecessor : task.predecessors) {
            earliest_start[task.id] = std::max(earliest_start[task.id], earliest_start[predecessor] + tasks[predecessor].duration);
        }
    }

    int max_duration = 0;
    int end_task_id = -1;

    for (int i = 0; i < n; i++) {
        if (tasks[i].duration + earliest_start[i] > max_duration) {
            max_duration = tasks[i].duration + earliest_start[i];
            end_task_id = i;
        }
    }

    std::vector<int> critical_path;
    find_critical_path(tasks, 0, earliest_start, critical_path);

    std::cout << "Project duration: " << max_duration << std::endl;
    std::cout << "Critical path: ";

    for (int task_id : critical_path) {
        std::cout << "Task " << task_id << " -> ";
    }

    std::cout << "End" << std::endl;

    return 0;
}
