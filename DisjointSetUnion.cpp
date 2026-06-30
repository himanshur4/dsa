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
