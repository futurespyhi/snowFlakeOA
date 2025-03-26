#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
public:
    int numWays(vector<string>& words, string target) {
        const int mod = 1e9 + 7;
        const int m = target.size(), n = words[0].size();
        
        // 统计每个位置每个字符的频率
        int freq[26][1000] = {0};
        for (int i = 0; i < n; i++) {
            for (const auto& w : words) {
                freq[w[i] - 'a'][i]++;
            }
        }
        
        // 1D DP数组，dp[j]表示构造target的前j个字符的方式数
        int dp[1001] = {0};
        dp[0] = 1; // 基本情况
        
        for (int i = 0; i < n; i++) {
            // 从后向前遍历target，避免覆盖
            for (int j = m; j >= 1; j--) {
                long long fc = freq[target[j - 1] - 'a'][i]; // 避免溢出
                dp[j] = (dp[j] + dp[j - 1] * fc) % mod;
            }
        }
        return dp[m];
    }
};

int main() {
    Solution solution;

    // 输入 words 的大小
    int n;
    cout << "Enter the number of words: ";
    cin >> n;

    // 输入 words
    vector<string> words(n);
    cout << "Enter the words (one per line):" << endl;
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    // 输入 target
    string target;
    cout << "Enter the target string: ";
    cin >> target;

    // 调用函数并输出结果
    int result = solution.numWays(words, target);
    cout << "Number of ways to form the target string: " << result << endl;

    return 0;
}