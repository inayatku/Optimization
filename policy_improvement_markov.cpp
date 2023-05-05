#include <iostream>
#include <vector>

using namespace std;

// Define a function to perform policy improvement
vector<int> policy_improvement(const vector<vector<double>>& transition_probs, const vector<vector<double>>& rewards, const vector<int>& policy) {
    int n = transition_probs.size();
    vector<int> new_policy(n);
    bool policy_stable = true;
    for (int state = 0; state < n; state++) {
        int action = policy[state];
        double max_value = -1e9;
        for (int new_action = 0; new_action < n; new_action++) {
            double value = 0;
            for (int next_state = 0; next_state < n; next_state++) {
                value += transition_probs[state][action] * (rewards[state][action] + transition_probs[state][action] * rewards[next_state][new_action]);
            }
            if (value > max_value) {
                max_value = value;
                new_policy[state] = new_action;
            }
        }
        if (new_policy[state] != action) {
            policy_stable = false;
        }
    }
    if (policy_stable) {
        return new_policy;
    } else {
        return policy_improvement(transition_probs, rewards, new_policy);
    }
}

int main() {
    // Define a sample Markov decision process
    vector<vector<double>> transition_probs = {
        {0.7, 0.3, 0.0},
        {0.0, 0.6, 0.4},
        {0.0, 0.0, 1.0}
    };
    vector<vector<double>> rewards = {
        {10, 0, 0},
        {0, 50, 0},
        {0, 0, -10}
    };
    vector<int> policy = {0, 0, 0};

    // Perform policy improvement
    vector<int> new_policy = policy_improvement(transition_probs, rewards, policy);

    // Print the new policy
    for (int action : new_policy) {
        cout << action << " ";
    }
    cout << endl;

    return 0;
}
