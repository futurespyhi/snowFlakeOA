#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

// 将整数转换为长度为 n 的二进制字符串
string toBinaryString(int x, int n) {
    string binary;
    for (int i = n - 1; i >= 0; --i) {
        binary.push_back((x & (1 << i)) ? '1' : '0');
    }
    return binary;
}

// 生成所有 super bit strings 并返回唯一数量
int superBitStrings(int n, vector<int>& bitStrings) {
    unordered_set<string> superSet; // 存储所有唯一的 super bit strings

    for (int x : bitStrings) {
        string bitString = toBinaryString(x, n); // 转换为二进制字符串
        vector<int> zeroIndices; // 存储所有 0 的位置
        for (int i = 0; i < n; ++i) {
            if (bitString[i] == '0') {
                zeroIndices.push_back(i);
            }
        }

        // 遍历所有可能的子集（SOS DP）
        int m = zeroIndices.size();
        for (int mask = 0; mask < (1 << m); ++mask) {
            string superString = bitString; // 复制原始字符串
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    superString[zeroIndices[i]] = '1'; // 翻转 0 到 1
                }
            }
            superSet.insert(superString); // 添加到集合中
        }
    }

    return superSet.size(); // 返回唯一 super bit strings 的数量
}

// 测试用例
int main() {
    // 测试用例 1
    int n1 = 2;
    vector<int> bitStrings1 = {1};
    cout << "Test Case 1: " << superBitStrings(n1, bitStrings1) << endl; // 预期输出: 2

    // 测试用例 2
    int n2 = 3;
    vector<int> bitStrings2 = {2, 6};
    cout << "Test Case 2: " << superBitStrings(n2, bitStrings2) << endl; // 预期输出: 4

    // 测试用例 3
    int n3 = 5;
    vector<int> bitStrings3 = {10, 26};
    cout << "Test Case 3: " << superBitStrings(n3, bitStrings3) << endl; // 预期输出: 8

    return 0;
}