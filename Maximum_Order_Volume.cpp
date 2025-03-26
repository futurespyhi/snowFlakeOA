#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

// Function declaration (copy from the previous implementation)
int phoneCalls(vector<int>& start, vector<int>& duration, vector<int>& volume);

void testPhoneCalls() {
    // Test Case 1: The example from the problem statement
    {
        vector<int> start = {10, 5, 15, 18, 30};
        vector<int> duration = {30, 12, 20, 35, 35};
        vector<int> volume = {50, 51, 20, 25, 10};
        int expected = 76; // Maximum total volume is 51 + 25 = 76
        int result = phoneCalls(start, duration, volume);
        assert(result == expected);
        cout << "Test Case 1 Passed!" << endl;
    }

    // Test Case 2: No overlapping calls
    {
        vector<int> start = {1, 10, 20, 30};
        vector<int> duration = {2, 3, 4, 5};
        vector<int> volume = {10, 20, 30, 40};
        int expected = 100; // Sum of all volumes
        int result = phoneCalls(start, duration, volume);
        assert(result == expected);
        cout << "Test Case 2 Passed!" << endl;
    }

    // Test Case 3: All calls overlap
    {
        vector<int> start = {1, 2, 3, 4};
        vector<int> duration = {10, 10, 10, 10};
        vector<int> volume = {50, 60, 70, 80};
        int expected = 80; // Maximum volume without complete overlap
        int result = phoneCalls(start, duration, volume);
        assert(result == expected);
        cout << "Test Case 3 Passed!" << endl;
    }

    // Test Case 4: Single call
    {
        vector<int> start = {5};
        vector<int> duration = {10};
        vector<int> volume = {100};
        int expected = 100;
        int result = phoneCalls(start, duration, volume);
        assert(result == expected);
        cout << "Test Case 4 Passed!" << endl;
    }

    // Test Case 5: Empty input
    {
        vector<int> start = {};
        vector<int> duration = {};
        vector<int> volume = {};
        int expected = 0;
        int result = phoneCalls(start, duration, volume);
        assert(result == expected);
        cout << "Test Case 5 Passed!" << endl;
    }

    cout << "All Test Cases Passed Successfully!" << endl;
}

int main() {
    testPhoneCalls();
    return 0;
}

int phoneCalls(vector<int>& start, vector<int>& duration, vector<int>& volume) {
    int numCalls = start.size();
    vector<tuple<int, int, int>> calls(numCalls);

    // 将每个电话的开始时间、结束时间和订单量存入元组
    for (int i = 0; i < numCalls; ++i) {
        calls[i] = {start[i] + duration[i], start[i], volume[i]};
    }

    // 按结束时间升序排序
    sort(calls.begin(), calls.end());

    // 动态规划数组
    vector<int> dp(numCalls + 1, 0);

    for (int i = 0; i < numCalls; ++i) {
        auto [endTime, startTime, vol] = calls[i];

        // 使用二分查找找到在startTime之前结束的最后一个电话
        int latestNonConflictCallIndex = upper_bound(calls.begin(), calls.begin() + i, startTime, [&](int time, const auto& call) -> bool {
            return time < get<0>(call);
        }) - calls.begin();

        // 更新dp数组，选择当前电话或不选择当前电话
        dp[i + 1] = max(dp[i], dp[latestNonConflictCallIndex] + vol);
    }

    return dp[numCalls];
}
