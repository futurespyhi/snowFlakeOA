#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int getMinSwaps(vector<int>& arr) {
    int n = arr.size();
    int m = 0; // 非零整数的数量
    unordered_map<int, int> valueToIndex; // 记录每个非零整数的位置

    // 找出非零整数的数量 m，并记录每个非零整数的位置
    for (int i = 0; i < n; i++) {
        if (arr[i] != 0) {
            m++;
            valueToIndex[arr[i]] = i;
        }
    }

    int swaps = 0; // 记录交换次数

    for (int i = 0; i < m; i++) {
        // 如果当前位置已经是正确的非零整数，跳过
        if (arr[i] == i + 1) {
            continue;
        }

        // 找到应该放在位置 i 的非零整数
        int correctValue = i + 1;

        // 找到这个非零整数的位置
        int correctIndex = valueToIndex[correctValue];

        // 如果当前位置是 0，直接交换
        if (arr[i] == 0) {
            swap(arr[i], arr[correctIndex]);
            swaps++;
        } else {
            // 如果当前位置不是 0，需要先找到一个 0 来辅助交换
            // 找到数组中第一个 0 的位置
            int zeroIndex = -1;
            for (int j = i; j < n; j++) {
                if (arr[j] == 0) {
                    zeroIndex = j;
                    break;
                }
            }

            // 交换 0 和当前位置的非零整数
            swap(arr[i], arr[zeroIndex]);
            swaps++;

            // 再次交换，将正确的非零整数放到位置 i
            swap(arr[i], arr[correctIndex]);
            swaps++;
        }

        // 更新 valueToIndex 中的位置信息
        valueToIndex[arr[i]] = i;
        valueToIndex[arr[correctIndex]] = correctIndex;
    }

    return swaps;
}

int main() {
    // 示例 1
    vector<int> arr1 = {2, 3, 1, 0};
    cout << "Min swaps for [2, 3, 1, 0]: " << getMinSwaps(arr1) << endl; // 输出: 4

    // 示例 2
    vector<int> arr2 = {1, 3, 0, 2, 0};
    cout << "Min swaps for [1, 3, 0, 2, 0]: " << getMinSwaps(arr2) << endl; // 输出: 2

    // 示例 3
    vector<int> arr3 = {0, 2, 3, 1, 0};
    cout << "Min swaps for [0, 2, 3, 1, 0]: " << getMinSwaps(arr3) << endl; // 输出: 1

    
    return 0;
}