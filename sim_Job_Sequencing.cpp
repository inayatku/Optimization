#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

struct Job {
    int id;
    int processingTime;
    int waitingTime;
    int turnaroundTime;

    Job(int id, int processingTime)
        : id(id), processingTime(processingTime), waitingTime(0), turnaroundTime(0) {}
};

bool compareProcessingTime(const Job& a, const Job& b) {
    return a.processingTime < b.processingTime;
}

void processJobs(std::vector<Job>& jobs) {
    int currentTime = 0;

    for (Job& job : jobs) {
        job.waitingTime = currentTime;
        currentTime += job.processingTime;
        job.turnaroundTime = currentTime;
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

    // Sort jobs based on processing time using the SJF rule
    std::sort(jobs.begin(), jobs.end(), compareProcessingTime);

    // Process the jobs
    processJobs(jobs);

    // Calculate the average waiting time and average turnaround time
    double avgWaitingTime = std::accumulate(jobs.begin(), jobs.end(), 0.0,
        [](double sum, const Job& job) { return sum + job.waitingTime; }) / n;
    double avgTurnaroundTime = std::accumulate(jobs.begin(), jobs.end(), 0.0,
        [](double sum, const Job& job) { return sum + job.turnaroundTime; }) / n;

    // Display the results
    std::cout << "Job\tProcessing Time\tWaiting Time\tTurnaround Time" << std::endl;
    for (const Job& job : jobs) {
        std::cout << job.id << "\t" << job.processingTime << "\t\t" << job.waitingTime
                  << "\t\t" << job.turnaroundTime << std::endl;
    }
    std::cout << "Average waiting time: " << avgWaitingTime << std::endl;
    std::cout << "Average turnaround time: " << avgTurnaroundTime << std::endl;

    return 0;
}
