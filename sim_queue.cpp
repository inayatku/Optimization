#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>

// Customer class represents a customer with arrival time and service time
class Customer {
public:
    int arrivalTime;
    int serviceTime;

    Customer(int arrivalTime, int serviceTime)
        : arrivalTime(arrivalTime), serviceTime(serviceTime) {}
};

// Teller class represents a bank teller
class Teller {
public:
    int finishTime;

    Teller() : finishTime(0) {}

    // Check if the teller is available to serve a customer
    bool isAvailable(int currentTime) const {
        return currentTime >= finishTime;
    }

    // Serve a customer and update the teller's finish time
    void serveCustomer(const Customer& customer, int currentTime) {
        finishTime = currentTime + customer.serviceTime;
    }
};

// BankSimulation class manages the simulation process
class BankSimulation {
private:
    std::queue<Customer> customerQueue; // Queue of customers waiting for service
    std::vector<Teller> tellers;        // Vector of tellers
    int totalCustomers;                 // Total number of customers
    int maxServiceTime;                 // Maximum service time for a customer

public:
    BankSimulation(int numTellers, int totalCustomers, int maxServiceTime)
        : tellers(numTellers), totalCustomers(totalCustomers), maxServiceTime(maxServiceTime) {}

    // Generate customers with random arrival and service times
    void generateCustomers() {
        for (int i = 0; i < totalCustomers; ++i) {
            int arrivalTime = rand() % totalCustomers;
            int serviceTime = rand() % maxServiceTime + 1;
            customerQueue.push(Customer(arrivalTime, serviceTime));
        }
    }

    // Run the simulation of the bank operation
    void runSimulation() {
        int currentTime = 0;
        int totalWaitingTime = 0;

        // Continue until there are no more customers in the queue
        while (!customerQueue.empty()) {
            Customer& customer = customerQueue.front();

            // If the customer has arrived, find an available teller
            if (customer.arrivalTime <= currentTime) {
                int minWaitTeller = 0;
                // Find the teller with the earliest finish time
                for (int i = 1; i < tellers.size(); ++i) {
                    if (tellers[i].finishTime < tellers[minWaitTeller].finishTime) {
                        minWaitTeller = i;
                    }
                }

                // If the selected teller is available, serve the customer
                if (tellers[minWaitTeller].isAvailable(currentTime)) {
                    tellers[minWaitTeller].serveCustomer(customer, currentTime);
                    totalWaitingTime += currentTime - customer.arrivalTime;
                    customerQueue.pop();
                }
            }

            currentTime++;
        }

        // Calculate and display the average waiting time for customers
        double avgWaitingTime = static_cast<double>(totalWaitingTime) / totalCustomers;
        std::cout << "Average waiting time: " << avgWaitingTime << " time units." << std::endl;
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    int numTellers = 3;
    int totalCustomers = 50;
    int maxServiceTime = 10;

    // Initialize the bank simulation with specified parameters
    BankSimulation simulation(numTellers, totalCustomers, maxServiceTime);

    // Generate customers and run the simulation
    simulation.generateCustomers();
    simulation.runSimulation();

    return 0;
}
