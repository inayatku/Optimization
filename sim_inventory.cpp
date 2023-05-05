#include <iostream>
#include <cmath>

// Function to calculate the EOQ based on demand, ordering cost, and holding cost per unit
double calculateEOQ(double annualDemand, double orderingCost, double holdingCostPerUnit) {
    return std::sqrt((2 * annualDemand * orderingCost) / holdingCostPerUnit);
}

// Function to calculate the total annual cost based on demand, EOQ, ordering cost, and holding cost per unit
double calculateTotalCost(double annualDemand, double EOQ, double orderingCost, double holdingCostPerUnit) {
    double orderingCostTotal = (annualDemand / EOQ) * orderingCost;
    double holdingCostTotal = (EOQ / 2) * holdingCostPerUnit;
    return orderingCostTotal + holdingCostTotal;
}

int main() {
    double annualDemand = 12000;      // Annual demand for the product
    double orderingCost = 50;          // Cost per order
    double holdingCostPerUnit = 2.5;   // Holding cost per unit per year

    // Calculate the EOQ
    double EOQ = calculateEOQ(annualDemand, orderingCost, holdingCostPerUnit);
    std::cout << "Economic Order Quantity (EOQ): " << EOQ << " units" << std::endl;

    // Calculate the total annual cost
    double totalCost = calculateTotalCost(annualDemand, EOQ, orderingCost, holdingCostPerUnit);
    std::cout << "Total annual cost: $" << totalCost << std::endl;

    return 0;
}
