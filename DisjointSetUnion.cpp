#include <iostream>
#include <vector>

using namespace std;

class DSU {
private:
    vector<int> parent, rank, size;

public:
    // Constructor to initialize DSU for 'n' elements
    // Supports 1-based indexing by allocating n+1 space
    DSU(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; // Initially, every node is its own parent
        }
    }

    // Find operation with Path Compression
    // Time Complexity: O(4 * alpha) ~ O(1)
    int findParent(int node) {
        if (node == parent[node]) {
            return node;
        }
        // Path compression: link the current node directly to the ultimate parent
        return parent[node] = findParent(parent[node]);
    }

    // Union operation by Rank
    void unionByRank(int u, int v) {
        int root_u = findParent(u);
        int root_v = findParent(v);

        // If they have the same root, they are already in the same set
        if (root_u == root_v) return;

        // Attach the smaller rank tree under the larger rank tree
        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            // If ranks are equal, attach one to the other and increase the rank
            parent[root_u] = root_v;
            rank[root_v]++;
        }
    }

    // Union operation by Size (often preferred over Rank as it gives component size)
    void unionBySize(int u, int v) {
        int root_u = findParent(u);
        int root_v = findParent(v);

        if (root_u == root_v) return;

        // Attach the smaller size tree under the larger size tree
        if (size[root_u] > size[root_v]) {
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        } else {
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        }
    }

    // Utility to check if two nodes belong to the same component
    bool isConnected(int u, int v) {
        return findParent(u) == findParent(v);
    }
};

int main() {
    // Example Usage
    DSU ds(7);
    
    ds.unionByRank(1, 4);
    ds.unionByRank(2, 5);
    ds.unionByRank(3, 2);
    
    if (ds.isConnected(3, 5)) {
        cout << "3 and 5 are connected." << endl;
    } else {
        cout << "3 and 5 are NOT connected." << endl;
    }

    ds.unionByRank(1, 7);
    ds.unionByRank(0, 5);
    ds.unionByRank(5, 6);
    ds.unionByRank(4, 6);
    
    if (ds.isConnected(3, 7)) {
        cout << "3 and 7 are connected." << endl;
    } else {
        cout << "3 and 7 are NOT connected." << endl;
    }

    return 0;
}
