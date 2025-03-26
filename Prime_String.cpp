#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// 判断一个数是否为素数
bool isPrime(int num) {
    if (num < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int countPrimeStrings(string s) {
    int n = s.length();
    vector<long long> dp(n + 1, 0); // dp[i] 表示字符串 s[:i] 的拆分方式数量
    dp[0] = 1; // 空字符串有一种拆分方式
    long long MOD = 1000000007;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(i, 6); ++j) { // 素数范围限制在 10^6 以内，所以最多取 6 位
            string sub = s.substr(i - j, j);
            if (sub[0] != '0') {
                int num = stoi(sub);
                if (2 <= num && num <= 1000000 && isPrime(num)) {
                    dp[i] = (dp[i] + dp[i - j]) % MOD;
                }
            }
        }
    }

    return dp[n];
}

int main() {
    // 测试用例
    string s1 = "11375";
    cout << "字符串 '" << s1 << "' 的拆分方式数量: " << countPrimeStrings(s1) << endl;

    string s2 = "2";
    cout << "字符串 '" << s2 << "' 的拆分方式数量: " << countPrimeStrings(s2) << endl;

    string s3 = "23";
    cout << "字符串 '" << s3 << "' 的拆分方式数量: " << countPrimeStrings(s3) << endl;

    string s4 = "111111";
    cout << "字符串 '" << s4 << "' 的拆分方式数量: " << countPrimeStrings(s4) << endl;

    string s5 = "999999";
    cout << "字符串 '" << s5 << "' 的拆分方式数量: " << countPrimeStrings(s5) << endl;

    return 0;
}