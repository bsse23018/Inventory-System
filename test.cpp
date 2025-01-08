#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "classes.h"
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

TEST_CASE("Test Inventory Implementation with shelves and items") {
    Inventory inventory;

    vector<int> value = {10, 40, 30, 50};
    vector<int> weight = {5, 4, 6, 3};
    int shelfCount = 3;
    vector<int> shelfCapacity = {10, 15, 5};
for (int i = 0; i < shelfCount; i++) {
  Shelf *shelf=new Shelf(i,shelfCapacity[i]);
  inventory.shelves.push_back(shelf);
}

    implementation(inventory, shelfCount, weight, value);
    REQUIRE(inventory.shelves.size() == shelfCount);
    REQUIRE(inventory.getTotalCapacity() == 30);
    REQUIRE(inventory.getItemCount() == value.size());
    cout<<inventory<<endl;
}
// Function to generate a large number of inputs for testing
void generateTestData(int productCount, int shelfCount, vector<int>& values, vector<int>& weights, vector<int>& shelfCapacities) {
    for (int i = 0; i < productCount; ++i) {
        values.push_back(rand() % 100 + 1);      // Random value between 1 and 100
        weights.push_back(rand() % 50 + 1);     // Random weight between 1 and 50
    }
    for (int i = 0; i < shelfCount; ++i) {
        shelfCapacities.push_back(rand() % 500 + 100);  // Random capacity between 100 and 600
    }
}


TEST_CASE("Performance Test for implementation()") {
    // Define test parameters
    const int productCount = 1000;   // Number of products
    const int shelfCount = 100;      // Number of shelves

    vector<int> values, weights, shelfCapacities;
    Inventory inventory;

    // Generate test data
    generateTestData(productCount, shelfCount, values, weights, shelfCapacities);
    for (int i = 0; i < shelfCount; i++) {
        Shelf *shelf=new Shelf(i,shelfCapacities[i]);
        inventory.shelves.push_back(shelf);
    }

    SECTION("Execution time measurement") {
        // Measure time complexity using clock
        clock_t startTime = clock();

        // Call the implementation function
        implementation(inventory, shelfCount, weights, values);

        clock_t endTime = clock();

        // Calculate elapsed time
        double elapsedTime = double(endTime - startTime) / CLOCKS_PER_SEC;
        INFO("Execution Time: " << elapsedTime << " seconds");
        REQUIRE(elapsedTime < 5.0);  // Expect the execution time to be less than 5 seconds
    }

    SECTION("Memory usage estimation") {
        // Measure space complexity (approximation)
        size_t memoryUsage = 0;
        memoryUsage += sizeof(inventory);
        memoryUsage += values.capacity() * sizeof(int);
        memoryUsage += weights.capacity() * sizeof(int);
        memoryUsage += shelfCapacities.capacity() * sizeof(int);
        for (const auto& shelf : inventory.shelves) {
            memoryUsage += sizeof(Shelf);
            memoryUsage += shelf->ProductList.capacity() * sizeof(Product*);
        }

        INFO("Estimated Memory Usage: " << memoryUsage / (1024.0 * 1024.0) << " MB");
        REQUIRE(memoryUsage / (1024.0 * 1024.0) < 100);  // Expect memory usage to be under 100 MB
    }
}
