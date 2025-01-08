//
// Created by dell on 1/7/2025.
//

#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <vector>
using namespace std;

class Product {
public:
    int id, value, weight;

    Product() {
        id = 0;
        value = 0;
        weight = 0;
    };

    Product(int id, int value, int weight): id(id), value(value), weight(weight) {
    }
};

class Shelf {
public:
    int id, capacity, remainingCapacity;
    vector<Product *> ProductList;

    Shelf(int id, int capacity): id(id), capacity(capacity) {
        remainingCapacity = capacity;
    }

    bool operator<(const Shelf &other) const {
        return capacity < other.capacity;
    }

    bool operator>(const Shelf &other) const {
        return capacity > other.capacity;
    }

    void display() {
        cout << "Shelf id:" << id << endl;;
        cout << "Shelf capacity:" << capacity << endl;
        cout << "Shelf remaining Capacity:" << remainingCapacity << endl;
    }

    ~Shelf() {
        for (auto *product: ProductList) {
            delete product;
        }
    }
};

class Inventory {
public:
    vector<Shelf *> shelves;

    int getTotalCapacity();

    int getItemCount();

    friend ostream &operator<<(ostream &os, const Inventory &inventory);

    ~Inventory() {
        for (auto i: shelves) {
            delete i;
        }
    }
};

int kSack(int W, vector<int> &wt, vector<int> &val, vector<int> &PW, vector<int> &PV);

void Input();

void implementation(Inventory &inventory, int shelfCount, vector<int> weight, vector<int> value);

void Menu();
#endif //CLASSES_H
