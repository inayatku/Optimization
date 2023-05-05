#include <iostream>
#include <vector>
#include <algorithm>

struct Job {
    int id;
    int time_m1;
    int time_m2;
};

std::vector<Job> johnsons_algorithm(const std::vector<Job>& jobs) {
    std::vector<Job> sorted_jobs = jobs;
    std::sort(sorted_jobs.begin(), sorted_jobs.end(),
              [](const Job& a, const Job& b) { return std::min(a.time_m1, a.time_m2) < std::min(b.time_m1, b.time_m2); });

    size_t front = 0;
    size_t back = sorted_jobs.size() - 1;

    std::vector<Job> sequence(sorted_jobs.size());
    for (const auto& job : sorted_jobs) {
        if (job.time_m1 < job.time_m2) {
            sequence[front++] = job;
        } else {
            sequence[back--] = job;
        }
    }

    return sequence;
}

int main() {
    std::vector<Job> jobs = {
        {0, 6, 2},
        {1, 8, 7},
        {2, 1, 5},
        {3, 4, 6},
        {4, 3, 9},
    };

    std::vector<Job> sequence = johnsons_algorithm(jobs);

    std::cout << "Optimal job sequence: ";
    for (const auto& job : sequence) {
        std::cout << job.id << " ";
    }
    std::cout << std::endl;

    return 0;
}
