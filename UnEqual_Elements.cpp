#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

int findMaxLength(vector<int>& skills, int k) {
    int n = skills.size();
    if (n == 0) return 0;

    // 将相同的元素聚在一起，并统计它们的计数
    vector<pair<int, int>> data;
    int st = 0;
    for (int i = 1; i < n; ++i) {
        if (skills[i] != skills[i-1]) {
            data.push_back({skills[i-1], i - st});
            st = i;
        }
    }
    data.push_back({skills.back(), n - st});

    // 计算下一个同数值元素的位置
    int m = data.size();
    vector<int> nxt(m, m);
    unordered_map<int, int> seen;
    for (int i = m - 1; i >= 0; --i) {
        int v = data[i].first;
        if (seen.find(v) != seen.end()) {
            nxt[i] = seen[v];
        }
        seen[v] = i;
    }

    // 动态规划表
    vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(k + 2, vector<int>(2, 0)));

    for (int i = m - 1; i >= 0; --i) {
        for (int j = 0; j <= k + 1; ++j) {
            for (int diff = 0; diff <= 1; ++diff) {
                int ans = 0;
                if (diff == 1) {
                    ans = dp[i + 1][j][1];
                    if (j - diff >= 0) {
                        ans = max(ans, dp[nxt[i]][j - diff][0] + data[i].second);
                        ans = max(ans, dp[i + 1][j - diff][1] + data[i].second);
                    }
                } else {
                    ans = max(dp[nxt[i]][j][0] + data[i].second, dp[i + 1][j][1] + data[i].second);
                }
                dp[i][j][diff] = ans;
            }
        }
    }

    return dp[0][k + 1][1];
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <skills>... <k>" << endl;
        return 1;
    }

    vector<int> skills;
    int k;

    // Read skills from command line arguments
    for (int i = 1; i < argc - 1; ++i) {
        skills.push_back(atoi(argv[i])); // Convert string to integer
    }

    // Read the last argument as the value of k
    k = atoi(argv[argc - 1]);

    int result = findMaxLength(skills, k);
    cout << "Maximum length: " << result << endl;
    
    return 0;
}
