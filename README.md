# Tarjan's Algorithm for Strongly Connected Components

A minimal, clean, and efficient C++ implementation of **Tarjan’s algorithm** to find all **Strongly Connected Components (SCCs)** in a directed graph.

## Problem Statement

In a directed graph, a **Strongly Connected Component (SCC)** is a maximal subset of nodes where every node is reachable from every other node in the subset. The goal is to decompose the graph into all such components.

## Algorithm Overview

Tarjan’s algorithm performs a **single depth-first search (DFS)** while maintaining:
- A **discovery time** for each node (when it is first visited)
- A **low-link value** (the earliest discovery time reachable from the node)
- An **explicit stack** of nodes currently in the active DFS path

During **backtracking**, if a node’s `low-link` equals its `discovery time`, it is the **root of an SCC**. All nodes from the top of the stack down to this root are popped and form one SCC.

## Key Properties

- **Time Complexity**: O(V + E) — each node and edge is processed exactly once  
- **Space Complexity**: O(V) — for the stack, discovery map, low-link map, and on-stack set  
- **Graph Traversal**: Single DFS pass  
- **Graph Reversal**: Not required (unlike Kosaraju’s algorithm)

## Why Tarjan Over Alternatives?

- **Brute force** (DFS from every node): O(V·(V + E)) — unscalable beyond tiny graphs  
- **Kosaraju’s algorithm**: Requires building a reversed graph and two full passes — extra memory and slower in practice  
- **Gabow’s algorithm**: Similar complexity but more complex logic with no real-world advantage  
- **Tarjan’s**: Optimal, cache-friendly, widely used in production systems

## Real-World Applications

- **Compiler Design**: Detect circular imports, eliminate dead code, analyze call graphs  
- **Network Systems**: Identify routing loops, detect cyclic dependencies in microservices  
- **Static Analysis Tools**: Find data-flow cycles, taint propagation loops, resolve build dependencies

## Implementation Highlights

- Uses an **explicit stack** to track active DFS path (separate from recursion stack)  
- Tracks `onStack` status for O(1) back-edge validation  
- Correctly handles **disconnected components**, **isolated nodes**, and **complex SCC topologies**

## Test Cases

1. **Single cycle**  
   Input: `{0: {1}, 1: {2}, 2: {0}}`  
   Output: `[[2, 1, 0]]`

2. **Two cycles connected by a bridge**  
   Input: `{0: {1}, 1: {2}, 2: {0, 3}, 3: {4}, 4: {5}, 5: {3}}`  
   Output: `[[2, 1, 0], [5, 4, 3]]`

3. **Two cycles plus an isolated node**  
   Input: `{0: {1}, 1: {2}, 2: {0}, 3: {4}, 4: {5}, 5: {3}, 6: {}}`  
   Output: `[[2, 1, 0], [5, 4, 3], [6]]`

## Build and Run

Compile with any C++17-compatible compiler:

```bash
g++ -std=c++17 tarjan.cpp -o tarjan
./tarjan
