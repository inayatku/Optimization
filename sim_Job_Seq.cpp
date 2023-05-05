#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

struct Job {
    int id;
    int processingTime;

    Job(int id, int processingTime) : id(id), processingTime(processingTime) {}
};

struct Machine {
    int id;
    int currentLoad;

    Machine(int id) : id(id), currentLoad(0) {}
};

bool compareProcessingTime(const Job& a, const Job& b) {
    return a.processingTime < b.processingTime;
}

bool compareMachineLoad(const Machine& a, const Machine& b) {
    return a.currentLoad < b.currentLoad;
}

void processJobs(std::vector<Job>& jobs, std::vector<Machine>& machines) {
    for (Job& job : jobs) {
        // Find the machine with the lowest current load
        auto minLoadMachine = std::min_element(machines.begin(), machines.end(), compareMachineLoad);

        // Assign the job to the machine and update the machine's current load
        minLoadMachine->currentLoad += job.processingTime;
    }
}

int main() {
    int n = 6; // Number of jobs
    int m = 3; // Number of machines

    std::vector<Job> jobs = {
        Job(1, 15),
        Job(2, 5),
        Job(3, 25),
        Job(4, 12),
        Job(5, 30),
        Job(6, 10),
    };

    std::vector<Machine> machines;
    for (int i = 0; i < m; ++i) {
        machines.emplace_back(i + 1);
    }

    // Sort jobs based on processing time using the SJF rule
    std::sort(jobs.begin(), jobs.end(), compareProcessingTime);

    // Process the jobs
    processJobs(jobs, machines);

    // Display the results
    std::cout << "Machine\tLoad" << std::endl;
    for (const Machine& machine : machines) {
        std::cout << machine.id << "\t" << machine.currentLoad << std::endl;
    }

    return 0;
}
