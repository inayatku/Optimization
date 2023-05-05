#include <iostream>
#include <vector>

double seriesReliability(const std::vector<double>& componentReliabilities) {
    double reliability = 1.0;
    for (double componentReliability : componentReliabilities) {
        reliability *= componentReliability;
    }
    return reliability;
}

double parallelReliability(const std::vector<double>& componentReliabilities) {
    double unreliability = 1.0;
    for (double componentReliability : componentReliabilities) {
        unreliability *= (1.0 - componentReliability);
    }
    return 1.0 - unreliability;
}

int main() {
    // Stage 1: Components connected in series
    std::vector<double> stage1 = {0.98, 0.95};
    double stage1Reliability = seriesReliability(stage1);

    // Stage 2: Components connected in parallel
    std::vector<double> stage2 = {0.90, 0.92};
    double stage2Reliability = parallelReliability(stage2);

    // Stage 3: Components connected in series
    std::vector<double> stage3 = {0.99, 0.96};
    double stage3Reliability = seriesReliability(stage3);

    // Compute the overall system reliability
    double systemReliability = stage1Reliability * stage2Reliability * stage3Reliability;

    std::cout << "System reliability: " << systemReliability << std::endl;

    return 0;
}
