
# TapNap

A C++ project focused on graph algorithms, data structures, and algorithmic problem-solving.

This repository contains a collection of graph-related algorithms and practical implementations covering topics such as:

- Shortest Path Algorithms
- Minimum Spanning Tree (MST)
- Lowest Common Ancestor (LCA)
- Binary Lifting
- Graph Traversal and Connectivity
- Competitive Programming Problems

The project is organized into separate problem solutions and reusable helper implementations, allowing each program to be studied, compiled, and executed independently.

## Project Structure

```text
TapNap/
├── Problems/
│   ├── Core.cpp
│   ├── PriceComparing.cpp
│   ├── ShortestPathPetrol.cpp
│   ├── ShortestPathPtrlLight.cpp
│   └── ShortestTimeRedLight.cpp
├── help/
│   ├── Bicycles.cpp
│   ├── BinaryLifting.cpp
│   ├── LCA.cpp
│   ├── MinMaxLca.cpp
│   └── MstForEdges.cpp
├── .gitignore
└── README.md
```

## Main Topics Covered

- **Graph Algorithms:** Implementations of fundamental graph algorithms and techniques.
- **Shortest Path:** Solutions to shortest path problems with different constraints.
- **Minimum Spanning Tree:** Algorithms for finding minimum spanning trees.
- **Lowest Common Ancestor (LCA):** Efficient techniques for finding common ancestors in trees.
- **Binary Lifting:** An optimization technique for efficient tree queries.
- **Data Structures:** Practical applications of data structures in graph-related problems.
- **Competitive Programming:** Algorithmic solutions to various programming challenges.

## Requirements

- C++ compiler (`g++` recommended)
- C++17 or later
- Linux, macOS, or Windows with a configured C++ development environment

## Compilation and Execution

Since this repository contains multiple standalone C++ programs, each source file can be compiled and executed independently.

### Example 1: Compile a Problem File

Compile and run `Core.cpp`:

```bash
g++ -std=c++17 Problems/Core.cpp -o core
./core
```

### Example 2: Compile a Shortest Path Problem

Compile and run `ShortestPathPetrol.cpp`:

```bash
g++ -std=c++17 Problems/ShortestPathPetrol.cpp -o petrol
./petrol
```

### Example 3: Compile a Helper Implementation

Compile and run `LCA.cpp`:

```bash
g++ -std=c++17 help/LCA.cpp -o lca
./lca
```

## Notes

This project is intended for:

- Studying fundamental concepts of graph theory.
- Implementing and understanding graph algorithms in C++.
- Exploring practical data structure and algorithm applications.
- Improving problem-solving and algorithmic thinking.
- Preparing for competitive programming and academic coursework.

## Purpose

The main purpose of this repository is to provide a collection of graph algorithm implementations and problem-solving exercises, particularly in the context of data structures and algorithms coursework and competitive programming practice.

## Author

Developed as a collection of C++ graph algorithm implementations and data structure problem-solving exercises.
