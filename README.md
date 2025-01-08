# Inventory-System

---

## Problem: Dynamic Warehouse Management

You are managing a warehouse with **N shelves** and **M products**. Each product has a specific weight and value. The warehouse has limited capacity, and you need to determine the optimal way to distribute the products across the shelves to maximize total value while respecting capacity constraints.

---

## Constraints

1. **N Shelves**: Each shelf has a maximum weight capacity.
2. **M Products**: 
   - Each product has a **weight** and a **value**.
   - Each product can only be placed on **one shelf**, and splitting a product across multiple shelves is not allowed.

---

## Input Format

- **N**: Number of shelves (1 ≤ N ≤ 100).  
- **M**: Number of products (1 ≤ M ≤ 10,000).  
- The next **N** lines contain the **capacity** of each shelf.  
- The following **M** lines contain the **weight** and **value** of each product.

---

## Output Format

Output the **maximum total value** that can be stored in the warehouse.

---

## Example

### Input
2 5   // here 2 is number of shelfs and 5 is number of products
50 60 //these are weights of shelf 1 and 2
10 60 // product weight    product value
20 100 
30 120 
40 140 
50 200

### Output

### Explanation

- Place products with weights **10** and **30** on Shelf 1 (total weight = 40, total value = 180).  
- Place the product with weight **50** on Shelf 2 (total value = 200).  

**Total value = 380.**

---

## Requirements

1. **Optimization Techniques**:
   - Use **Knapsack Problem algorithms**, adapting them for multiple knapsacks (shelves).

2. **Dynamic Programming**:
   - Design a DP table where state variables represent the remaining capacity of each shelf and the subset of products.

3. **Efficiency**:
   - Optimize the solution for the given constraints by leveraging:
     - **Greedy methods**.
     - **Branch and Bound**.
     - Advanced **DP techniques**.

---

## Features

- Supports **multiple knapsack optimization** for dynamic warehouse management.
- Handles up to **100 shelves** and **10,000 products** efficiently.
- Implements advanced algorithms to maximize value while respecting constraints.

---


