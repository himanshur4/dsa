class DSU {
private:
    vector<int> parent, rank, size;
public:
    DSU(int n) {
        rank.resize(n + 1, 0);
        size.resize(n + 1, 1);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i; 
        }
    }
    int findParent(int node) {
        if (node == parent[node]) {
            return node;
        }
        return parent[node] = findParent(parent[node]);
    }
    void unionByRank(int u, int v) {
        int root_u = findParent(u);
        int root_v = findParent(v);
        if (root_u == root_v) return;

        if (rank[root_u] > rank[root_v]) {
            parent[root_v] = root_u;
        } else if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else {
            parent[root_u] = root_v;
            rank[root_v]++;
        }
    }
    void unionBySize(int u, int v) {
        int root_u = findParent(u);
        int root_v = findParent(v);
        if (root_u == root_v) return;
        if (size[root_u] > size[root_v]) {
            parent[root_v] = root_u;
            size[root_u] += size[root_v];
        } else {
            parent[root_u] = root_v;
            size[root_v] += size[root_u];
        }
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
