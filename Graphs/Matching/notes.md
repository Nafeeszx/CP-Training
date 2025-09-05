# Graph Theory: Matching

This section covers algorithms related to finding matchings in graphs, primarily in bipartite graphs.

## Core Concepts

* **Matching:** A subset of edges where no two edges share a common vertex.
* **Maximum Matching:** A matching with the maximum possible number of edges.
* **Perfect Matching:** A matching that covers all vertices of the graph.
* **Bipartite Graph (Bigraph):** A graph whose vertices can be divided into two disjoint sets, 'U' and 'V', such that every edge connects a vertex in U to one in V.

---

## Algorithms

### 1. Maximum Bipartite Matching using Augmenting Paths (Ford-Fulkerson variant)

This is a common approach using DFS or BFS to find augmenting paths in the residual graph.

**Key Idea:** An augmenting path is a path in the graph that alternates between edges not in the matching and edges in the matching. Finding and "flipping" such a path increases the matching size by one.

**Complexity:** $O(E \cdot V)$

**Sample Implementation (`gameLogic` part):**
```cpp
// adj: adjacency list
// match: stores the matching pair for a vertex in V
// visited: keeps track of visited vertices in a single DFS run

bool can_match(int u, vector<vector<int>>& adj, vector<int>& match, vector<bool>& visited) {
    for (int v : adj[u]) {
        if (!visited[v]) {
            visited[v] = true;
            // If v is not matched or its partner can find an alternative match
            if (match[v] < 0 || can_match(match[v], adj, match, visited)) {
                match[v] = u;
                return true;
            }
        }
    }
    return false;
}
```

### 2. Hopcroft-Karp Algorithm

A more advanced algorithm that finds multiple augmenting paths at once using BFS to layer the graph and then DFS to find paths in that layered structure.

**Complexity:** $O(E \sqrt{V})$

---

## Problem Links & Notes

* [LightOJ 1151 - A New Traffic System](http://lightoj.com/volume_showproblem.php?problem=1151): Classic max-flow formulation, which is equivalent to bipartite matching.
* **Key trick:** Vertex splitting is a common technique to model problems as bipartite matching. For example, on a grid, you can model rows and columns as the two sets of the bipartite graph.