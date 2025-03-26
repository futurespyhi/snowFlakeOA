#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace std;

const long INF = LONG_MAX / 10;

long dfs(int i, const vector<int>& cost, int timeSoFar, const vector<int>& time, vector<unordered_map<int, long>>& memo) {
    int n = cost.size();
    if (i == n) return timeSoFar >= 0 ? 0 : INF;
    if (timeSoFar >= n - i) return 0;
    if (memo[i].count(timeSoFar)) return memo[i][timeSoFar];
    long resPaid = cost[i] + dfs(i + 1, cost, timeSoFar + time[i], time, memo); // paid server
    long resFree = dfs(i + 1, cost, timeSoFar - 1, time, memo); // free server
    memo[i][timeSoFar] = min(resPaid, resFree);
    return memo[i][timeSoFar];
}

long getMinCost(const vector<int>& cost, const vector<int>& time) {
    assert(cost.size() > 0);
    assert(cost.size() == time.size());
    vector<unordered_map<int, long>> memo(cost.size());
    return dfs(0, cost, 0, time, memo);
}

int main() {
    // 使用临时对象调用 getMinCost
    vector<int> cost1 = {1, 1, 3, 4};
    vector<int> time1 = {3, 1, 2, 3};
    cout << "Expected: 1, actual: " << getMinCost(cost1, time1) << endl;

    vector<int> cost2 = {1, 2, 3, 2};
    vector<int> time2 = {1, 2, 3, 2};
    cout << "Expected: 3, actual: " << getMinCost(cost2, time2) << endl;

    vector<int> cost3 = {2, 3, 4, 2};
    vector<int> time3 = {1, 1, 1, 1};
    cout << "Expected: 4, actual: " << getMinCost(cost3, time3) << endl;

    vector<int> cost4 = {2, 3, 4, 5};
    vector<int> time4 = {1, 1, 5, 3};
    cout << "Expected: 4, actual: " << getMinCost(cost4, time4) << endl;

    vector<int> cost5 = {5, 6, 7, 8, 8, 10};
    vector<int> time5 = {1, 1, 1, 1, 1, 10};
    cout << "Expected: 10, actual: " << getMinCost(cost5, time5) << endl;

    vector<int> cost6 = {10, 10, 10, 10, 10, 20, 20, 20};
    vector<int> time6 = {3, 3, 3, 3, 3, 6, 6, 6};
    cout << "Expected: 20, actual: " << getMinCost(cost6, time6) << endl;

    vector<int> cost7 = {5, 6, 7, 8, 1000000};
    vector<int> time7 = {1, 1, 1, 1, 1000};
    cout << "Expected: 18, actual: " << getMinCost(cost7, time7) << endl;

    // 1000 size example
    vector<int> costList = {6, 3, 9, 5, 1000000, 2, 3, 4, 4, 5};
    vector<int> timeList = {3, 1, 2, 3, 1000, 1, 1, 1, 1, 7};
    vector<int> largeCostList;
    vector<int> largeTimeList;
    for (int i = 0; i < 100; i++) {
        largeCostList.insert(largeCostList.end(), costList.begin(), costList.end());
        largeTimeList.insert(largeTimeList.end(), timeList.begin(), timeList.end());
    }
    cout << "Expected: 700, actual: " << getMinCost(largeCostList, largeTimeList) << endl;

    // 1000 size example 2
    vector<int> cost8(1000, 1000000);
    vector<int> time8(1000, 1000);
    cout << "Expected: 1000000, actual: " << getMinCost(cost8, time8) << endl;

    return 0;
}