# 🍔 Food Delivery Routing Optimization

This C++ project simulates and optimizes delivery routing for food orders across a grid-based city map. It models restaurants, customers, and delivery paths, and uses a brute-force approach to determine the most efficient route to fulfill multiple orders.

## Features

- Simulates a city grid where each node represents a delivery location
- Models multiple restaurants, each with multiple orders
- Calculates minimum distance to deliver all orders from a restaurant
- Uses next-permutation to explore all order delivery combinations
- Displays grid and order information per test case
- Reads test data from an external file


## How It Works

- **Grid Construction**: Each cell in the grid is a `Node` connected via `up/down/left/right` pointers.
- **Restaurant System**: Restaurants and their orders are placed at specific grid locations.
- **Order Routing**: For each restaurant, all permutations of order delivery routes are evaluated to find the shortest path.
- **Distance Calculation**: Manhattan distance is used between grid cells.

## File Structure

- `Food Delivery Routing Optimization.cpp` – Main source file
- `projecttestdata.txt` – Input data file (user-defined format)
  - Test case count
  - Grid size, number of riders, number of restaurants
  - Restaurant details and order data
