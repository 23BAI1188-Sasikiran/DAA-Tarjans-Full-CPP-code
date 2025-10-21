#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Tarjan {
private:
    unordered_map<int, vector<int>> graph;
    int time;
    stack<int> stk;
    unordered_set<int> onStack;
    unordered_map<int, int> discovery;
    unordered_map<int, int> lowLink;
    vector<vector<int>> sccs;

    void dfs(int node) {
        discovery[node] = time;
        lowLink[node] = time;
        time++;
        stk.push(node);
        onStack.insert(node);

        for (int neighbor : graph[node]) {
            if (discovery.find(neighbor) == discovery.end()) {
                dfs(neighbor);
                lowLink[node] = min(lowLink[node], lowLink[neighbor]);
            } else if (onStack.count(neighbor)) {
                lowLink[node] = min(lowLink[node], discovery[neighbor]);
            }
        }

        if (lowLink[node] == discovery[node]) {
            vector<int> scc;
            int w;
            do {
                w = stk.top();
                stk.pop();
                onStack.erase(w);
                scc.push_back(w);
            } while (w != node);
            sccs.push_back(scc);
        }
    }

public:
    Tarjan(const unordered_map<int, vector<int>>& g) : graph(g), time(0) {}

    vector<vector<int>> run() {
        sccs.clear();
        discovery.clear();
        lowLink.clear();
        onStack.clear();
        while (!stk.empty()) stk.pop();

        for (const auto& kv : graph) {
            int node = kv.first;
            if (discovery.find(node) == discovery.end()) {
                dfs(node);
            }
        }
        return sccs;
    }
};

void printGraphAsCode(const unordered_map<int, vector<int>>& g) {
    cout << "{";
    bool firstNode = true;
    // Print in sorted key order for consistency
    for (int k = 0; k <= 10; ++k) { // safe upper bound for test cases
        if (g.count(k)) {
            if (!firstNode) cout << ", ";
            cout << k << ": {";
            const auto& nbrs = g.at(k);
            for (size_t i = 0; i < nbrs.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << nbrs[i];
            }
            cout << "}";
            firstNode = false;
        }
    }
    cout << "}";
}

void printSCCs(const vector<vector<int>>& sccs) {
    cout << "[";
    for (size_t i = 0; i < sccs.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << "[";
        for (size_t j = 0; j < sccs[i].size(); ++j) {
            if (j > 0) cout << ", ";
            cout << sccs[i][j];
        }
        cout << "]";
    }
    cout << "]";
}

int main() {
    // Test Case 1
    auto g1 = unordered_map<int, vector<int>>{{0, {1}}, {1, {2}}, {2, {0}}};
    cout << "Input:  ";
    printGraphAsCode(g1);
    cout << "\nOutput: ";
    printSCCs(Tarjan(g1).run());
    cout << "\n\n";

    // Test Case 2
    auto g2 = unordered_map<int, vector<int>>{
        {0, {1}}, {1, {2}}, {2, {0, 3}}, {3, {4}}, {4, {5}}, {5, {3}}
    };
    cout << "Input:  ";
    printGraphAsCode(g2);
    cout << "\nOutput: ";
    printSCCs(Tarjan(g2).run());
    cout << "\n\n";

    // Test Case 3
    auto g3 = unordered_map<int, vector<int>>{
        {0, {1}}, {1, {2}}, {2, {0}},
        {3, {4}}, {4, {5}}, {5, {3}},
        {6, {}}
    };
    cout << "Input:  ";
    printGraphAsCode(g3);
    cout << "\nOutput: ";
    printSCCs(Tarjan(g3).run());
    cout << "\n";

    return 0;
}