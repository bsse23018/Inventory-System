//
// Created by dell on 1/7/2025.
//
#include <algorithm>
#include <vector>
#include "classes.h"

int Inventory::getTotalCapacity() {
    int totalCapacity = 0;
    for (auto i:shelves) {
        totalCapacity+=i->capacity;
    }
    return totalCapacity;
}

int Inventory::getItemCount() {
    int itemCount = 0;
    for (auto i:shelves) {
        itemCount += i->ProductList.size();
    }
    return itemCount;
}
int kSack(int W, vector<int> &wt, vector<int> &val, vector<int> &PW, vector<int> &PV) {
    int n = wt.size();
    vector<vector<int> > memo(n + 1, vector<int>(W + 1, 0));

    // Memo table ko iteratively build karna
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i - 1] <= w) {
                // Agar current item ka weight w se chhota ya barabar hai, to usko consider karein
                memo[i][w] = max(val[i - 1] + memo[i - 1][w - wt[i - 1]], memo[i - 1][w]);
            } else {
                // Agar item ka weight zyada hai, to pichle item ka result use karein
                memo[i][w] = memo[i - 1][w];
            }
        }
    }

    // Backtracking karke selected items find karna
    vector<int> selectedIndices;
    int currentW = W;
    for (int i = n; i > 0 && currentW > 0; i--) {
        if (memo[i][currentW] != memo[i - 1][currentW]) {
            // Agar current item select hua hai to uska index save karein
            selectedIndices.push_back(i - 1);
            currentW -= wt[i - 1]; // Weight update karein
        }
    }

    // Selected items ko list se remove karna
    for (int idx: selectedIndices) {
        PW.push_back(wt[idx]); // Selected weight ko PW mein add karein
        PV.push_back(val[idx]); // Selected value ko PV mein add karein
        wt.erase(wt.begin() + idx); // Original list se weight remove karein
        val.erase(val.begin() + idx); // Original list se value remove karein
    }

    // Maximum profit return karein
    return memo[n][W];
}

void implementation(Inventory &inventory,int shelfCount,vector<int> weight,vector<int>value){
    // here shelfs are sorted based on their capacity in ascending order
    std::stable_sort(inventory.shelves.begin(), inventory.shelves.end(), [](const Shelf* a, const Shelf* b) {
             return a->capacity < b->capacity;  // Sorting by weight in ascending order
         });

    for (int i = shelfCount - 1; i >= 0; --i) {
        vector<int> PlacedWeights, PlacedVal;
        // on each iteration largest capacity shelf is passed in knapsack in means in descending order
        //also those weights(products) which are placed are removed from main weight vector and shifted in to
        //the vector of products on each shelf as object
        int maxProfit = kSack(inventory.shelves[i]->capacity, weight, value, PlacedWeights, PlacedVal);
        int sum=0;
        for (int j = 0; j < PlacedVal.size(); ++j) {
            //static int so one time initialized so that we will have unique id every time after increment
            static int Productid = 1;
            auto product = new Product(Productid, PlacedVal[j], PlacedWeights[j]);
            Productid += 1;
            //now those weights which are selected and removed from main weight vector are placed on shelf in the form of product object
            inventory.shelves[i]->ProductList.push_back(product);
            sum+=PlacedWeights[j];
        }
        // calculation of remaining capacity
        inventory.shelves[i]->remainingCapacity=inventory.shelves[i]->capacity - sum;

    }

}
void Input(Inventory& inventory) {
    inventory.shelves.clear();
    vector<int> value ;
    vector<int> weight ;
    int ProductN=0;
    cout<<"Please input the number of products: ";
    cin>>ProductN;
    for (int i = 0; i < ProductN; i++) {
      int tempw,tempv;
      cout<<"Enter Product weight and value for index "<<i+1<<": ";
      cin>>tempw>>tempv;

      if(tempw<=0 || tempv<=0) {
        cout<<"invalid input\n";
        i--;
      }else {
          weight.push_back(tempw);
          value.push_back(tempv);
      }
    }
    int shelfCount;
    cout << "Enter number of shelves: ";
    cin >> shelfCount;
    vector<int> shelfCapacity;
    for (int i = 0; i < shelfCount; ++i) {
        cout << "Enter capacity for shelf " << i + 1 << ": ";
        int temp;
        cin >> temp;
        if(temp<=0) {
          cout<<"invalid input\n";
        }
        Shelf *shelf = new Shelf(i, temp);
        inventory.shelves.push_back(shelf);
    }
    implementation(inventory, shelfCount, weight, value);
}

void Menu() {
    Inventory inventory;
    Input(inventory); // Assuming this function populates the inventory

    while (true) {
        cout << "\n================== Inventory Management Menu ==================\n";
        cout << "1. Display total number of shelves\n";
        cout << "2. Display total capacity of all shelves\n";
        cout << "3. Display total number of items\n";
        cout << "4. Display inventory details\n";
        cout << "5. Input data again\n";
        cout << "6. Exit\n";
        cout << "==============================================================\n";
        cout << "Enter your choice: ";

        char choice;
        cin >> choice;

        switch (choice) {
            case '1': {
                cout << "Total number of shelves: " << inventory.shelves.size() << endl;
                break;
            }
            case '2': {
                cout << "Total capacity of all shelves: " << inventory.getTotalCapacity() << endl;
                break;
            }
            case '3': {
                cout << "Total number of items: " << inventory.getItemCount() << endl;
                break;
            }
            case '4': {
                cout << "Displaying inventory details:\n";
                cout<<inventory;
                break;
            }
            case '5': {
                Input(inventory);
            }case '6':{
                cout << "Exiting the menu. Goodbye!\n";
                return;
            }
            default: {
                cout << "Invalid choice! Please select a valid option.\n";
                break;
            }
        }
    }
}

ostream & operator<<(ostream &os, const Inventory &inventory) {
        os << "================ Inventory Details ================\n";
        os << "Total Shelves: " << inventory.shelves.size() << "\n\n";

        for (const auto& shelf : inventory.shelves) {
            os << "Shelf ID: " << shelf->id << "\n";
            os << "Capacity: " << shelf->capacity << "\n";
            os << "Remaining Capacity: " << shelf->remainingCapacity << "\n";
            os << "Products:\n";

            if (shelf->ProductList.empty()) {
                os << "  [No Products]\n";
            } else {
                for (const auto& product : shelf->ProductList) {
                    os << "  - Product ID: " << product->id
                       << ", Value: " << product->value
                       << ", Weight: " << product->weight << "\n";
                }
            }
            os << "-------------------------------------------------\n";
        }

        os << "=================================================\n";
        return os;
    }

