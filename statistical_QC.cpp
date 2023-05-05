#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <algorithm>


double calculate_average(const std::vector<double>& sample) {
    return std::accumulate(sample.begin(), sample.end(), 0.0) / sample.size();
}

double calculate_range(const std::vector<double>& sample) {
    auto min_element = std::min_element(sample.begin(), sample.end());
    auto max_element = std::max_element(sample.begin(), sample.end());
    return *max_element - *min_element;
}

int main() {
    std::vector<std::vector<double>> samples = {
        {5.2, 5.4, 5.0, 5.1},
        {5.3, 5.6, 5.2, 5.5},
        {5.7, 5.1, 5.0, 5.3},
        {5.5, 5.3, 5.6, 5.2}
    };

    int num_samples = samples.size();
    double total_average = 0;
    double total_range = 0;

    for (const auto& sample : samples) {
        total_average += calculate_average(sample);
        total_range += calculate_range(sample);
    }

    double average_of_averages = total_average / num_samples;
    double average_range = total_range / num_samples;

    const double A2 = 0.729;  // A2 constant for sample size 4
    double upper_control_limit = average_of_averages + A2 * average_range;
    double lower_control_limit = average_of_averages - A2 * average_range;

    std::cout << "X-bar control chart:" << std::endl;
    std::cout << "Average of averages: " << average_of_averages << std::endl;
    std::cout << "Average range: " << average_range << std::endl;
    std::cout << "Upper control limit: " << upper_control_limit << std::endl;
    std::cout << "Lower control limit: " << lower_control_limit << std::endl;

    bool process_in_control = true;

    for (size_t i = 0; i < num_samples; ++i) {
        double sample_average = calculate_average(samples[i]);

        if (sample_average > upper_control_limit || sample_average < lower_control_limit) {
            process_in_control = false;
            std::cout << "Sample " << i + 1 << " is out of control." << std::endl;
        }
    }

    if (process_in_control) {
        std::cout << "All samples are in control." << std::endl;
    }

    return 0;
}
