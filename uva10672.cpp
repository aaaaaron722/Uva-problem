/*
* C++ solution for Marbles on tree problem (Uva 10672)
*
* Author: Aaron Lin
* Date: 2025/2/22
*/
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Node{
    int marbles; //彈珠數
    vector<int> children; //子節點數量
};

int dfs(int node, vector<Node>& tree, int& moves){
    int surplus = tree[node].marbles - 1; //自身的彈珠數量減一決定是否多彈珠或少彈珠

    for(int child : tree[node].children){
        surplus += dfs(child, tree, moves); //遞迴
    }

    moves += abs(surplus);

    return surplus;
}

int main(){
    int n;
    while(cin >> n && n != 0){
        vector<Node> tree(n + 1);
        for (int i = 0; i < n; ++i){ //構建tree
            int v, marbles, d;
            cin >> v >> marbles >> d;
            tree[v].marbles = marbles;

            for(int j = 0; j < d; ++j){
                int child;
                cin >> child;
                tree[v].children.push_back(child); //children的資料型態是vector所以用push_back
            }
        }

        int moves = 0;

        dfs(1, tree, moves); //從root開始遍歷, 若沒有從root出發就會錯

        cout << "moves: " << moves << endl;
    }

    return 0;
}
