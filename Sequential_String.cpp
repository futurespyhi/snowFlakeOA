#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 检查 sCount 是否包含 targetCount 中的所有字符
bool hasAllDigits(const vector<int>& sCount, const vector<int>& targetCount) {
    for (int i = 0; i < 10; i++) {
        if (sCount[i] < targetCount[i]) {
            return false;
        }
    }
    return true;
}

// 在 digitCountUpToIndex 中查找满足条件的最小子串长度
int findMinimumLength(const vector<vector<int>>& digitCountUpToIndex, const string& target) {
    vector<int> targetCount(10, 0);
    for (char c : target) {
        targetCount[c - '0']++;
    }

    int left = 0, right = digitCountUpToIndex.size() - 1, minLength = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (hasAllDigits(digitCountUpToIndex[mid], targetCount)) {
            minLength = mid + 1; // 找到一个有效长度，尝试找到更小的
            right = mid - 1;
        } else {
            left = mid + 1; // 字符不足，继续向右查找
        }
    }
    return minLength;
}

// 主函数，计算每个字符串所需的最少字符数
vector<int> countMinimumCharacters(const string& s, const vector<string>& arr) {
    vector<int> result(arr.size(), -1);
    vector<vector<int>> digitCountUpToIndex(s.length(), vector<int>(10, 0));

    // 预处理 s，统计每个位置之前的字符频率
    for (int i = 0; i < s.length(); i++) {
        if (i > 0) {
            digitCountUpToIndex[i] = digitCountUpToIndex[i - 1];
        }
        digitCountUpToIndex[i][s[i] - '0']++;
    }

    // 对每个字符串，查找满足条件的最小子串长度
    for (int i = 0; i < arr.size(); i++) {
        result[i] = findMinimumLength(digitCountUpToIndex, arr[i]);
    }

    return result;
}

int main(int argc, char* argv[]) {
    // 检查命令行参数数量是否正确
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <special_string> <target1> <target2> ... <targetN>" << endl;
        return 1;
    }

    // 第一个参数是特殊字符串 s
    string s = argv[1];

    // 剩余参数是目标字符串数组 arr
    vector<string> arr;
    for (int i = 2; i < argc; i++) {
        arr.push_back(argv[i]);
    }

    // 调用函数计算结果
    vector<int> result = countMinimumCharacters(s, arr);

    // 输出结果
    cout << "Result: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}