/*
* C++ solution for Marbles on tree problem (Uva 10672)
* And also add a function to print the path of moves
* This solution uses Depth First Search (DFS) to traverse the tree and calculate the moves needed to balance the marbles.
* Author: Aaron Lin
* Date: 2025/2/22
*/
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

struct Node {
    int marbles; //彈珠數
    vector<int> children; //子節點數量
};

// 增加參數 paths 來記錄移動的過程
int dfs(int node, vector<Node>& tree, int& moves, vector<string>& paths) {
    int surplus = tree[node].marbles - 1; // 多的或缺的彈珠數量

    for (int child : tree[node].children) {
        int child_surplus = dfs(child, tree, moves, paths);
        surplus += child_surplus;

        if (child_surplus > 0) {
            // 子節點有多的，要移到 parent（也就是自己）
            paths.push_back("Move " + to_string(child_surplus) + " marbles from node " + to_string(child) + " to node " + to_string(node));
        } else if (child_surplus < 0) {
            // 子節點缺的，要從 parent 移給它
            paths.push_back("Move " + to_string(-child_surplus) + " marbles from node " + to_string(node) + " to node " + to_string(child));
        }
    }

    moves += abs(surplus);
    return surplus;
}

int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<Node> tree(n + 1);
        vector<bool> hasParent(n + 1, false); // 用來找 root

        for (int i = 0; i < n; ++i) {
            int v, marbles, d;
            cin >> v >> marbles >> d;
            tree[v].marbles = marbles;

            for (int j = 0; j < d; ++j) {
                int child;
                cin >> child;
                tree[v].children.push_back(child);
                hasParent[child] = true;
            }
        }

        int root = 1;
        for (int i = 1; i <= n; ++i) {
            if (!hasParent[i]) {
                root = i;
                break;
            }
        }

        int moves = 0;
        vector<string> paths;

        dfs(root, tree, moves, paths);

        cout << "Total moves: " << moves << endl;
        for (const string& step : paths) {
            cout << step << endl;
        }
    }

    return 0;
}
