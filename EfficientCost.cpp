#include <vector>
#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

int calculateCost(vector<int>& arr, int threshold) {
    int n = arr.size();
    vector<int> dp(n + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int currentMax = 0;
        for (int j = 1; j <= threshold && i - j >= 0; ++j) {
            currentMax = max(currentMax, arr[i - j]);
            dp[i] = min(dp[i], dp[i - j] + currentMax);
        }
    }

    return dp[n];
}

void testCalculateCost() {
    // Test Case 1
    vector<int> arr1 = {1, 3, 4, 5, 2, 6};
    int threshold1 = 3;
    cout << "Test Case 1: " << calculateCost(arr1, threshold1) << " (Expected: 10)" << endl;

    // Test Case 2
    vector<int> arr2 = {1, 2};
    int threshold2 = 1;
    cout << "Test Case 2: " << calculateCost(arr2, threshold2) << " (Expected: 3)" << endl;

    // Test Case 3
    vector<int> arr3 = {4, 3, 2, 5, 1};
    int threshold3 = 2;
    cout << "Test Case 3: " << calculateCost(arr3, threshold3) << " (Expected: 10)" << endl;

    // Test Case 4
    vector<int> arr4 = {1, 1, 1, 1, 1};
    int threshold4 = 3;
    cout << "Test Case 4: " << calculateCost(arr4, threshold4) << " (Expected: 2)" << endl;

    // Test Case 5
    vector<int> arr5 = {10, 20, 30, 40, 50};
    int threshold5 = 1;
    cout << "Test Case 5: " << calculateCost(arr5, threshold5) << " (Expected: 150)" << endl;
}

int main() {
    testCalculateCost();
    return 0;
}