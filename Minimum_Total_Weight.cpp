#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int findMinWeight(vector<int>& weights, int d) {
    // 使用最大堆（优先队列）来存储巧克力的重量
    priority_queue<int> maxHeap(weights.begin(), weights.end());

    for (int i = 0; i < d; ++i) {
        if (maxHeap.empty()) break; // 如果没有巧克力了，直接退出

        int maxWeight = maxHeap.top(); // 取出当前最重的巧克力
        maxHeap.pop();

        int eaten = maxWeight / 2; // 吃掉一半
        int remaining = maxWeight - eaten; // 剩下的部分

        if (remaining > 0) {
            maxHeap.push(remaining); // 将剩下的部分放回堆中
        }
    }

    // 计算剩余巧克力的总重量
    int totalWeight = 0;
    while (!maxHeap.empty()) {
        totalWeight += maxHeap.top();
        maxHeap.pop();
    }

    return totalWeight;
}

int main() {
    vector<int> weights = {2};
    int d = 1;
    cout << "Minimum total weight after " << d << " days: " << findMinWeight(weights, d) << endl;
    return 0;
}