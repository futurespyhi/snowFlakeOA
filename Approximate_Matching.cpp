#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int findPostLength(const string& subStr, const string& suffix) {
    int max = 0;
    for (size_t i = 0; i < subStr.length(); i++) {
        int len = 0;
        string str = subStr.substr(i);
        size_t k = 0;
        for (size_t j = 0; j < suffix.length() && k < str.length(); j++, k++) {
            if (str[k] == suffix[j])
                len++;
            else
                break;
        }
        if (len > max && k == str.length())
            max = len;
    }
    return max;
}

int findPreLength(const string& subStr, const string& prefix) {
    int max = 0;
    for (size_t i = 1; i <= subStr.length(); i++) {
        int len = 0;
        int j = prefix.length() - 1;
        string str = subStr.substr(0, i);
        int k = str.length() - 1;

        for (; j >= 0 && k >= 0; j--, k--) {
            if (str[k] == prefix[j])
                len++;
            else
                break;
        }
        if (len > max && k == -1)
            max = len;
    }
    return max;
}

string calculateScore(const string& text, const string& prefix, const string& suffix) {
    int maxScore = 0;
    string result = "";

    for (size_t i = 0; i < text.length(); i++) {
        for (size_t j = i + 1; j <= text.length(); j++) {
            string subStr = text.substr(i, j - i); // 当前子字符串
            int pre = findPreLength(subStr, prefix); // 前缀匹配长度
            int post = findPostLength(subStr, suffix); // 后缀匹配长度
            int textScore = pre + post; // 当前子字符串的 textScore

            // 如果当前 textScore 更高，更新结果
            if (textScore > maxScore) {
                maxScore = textScore;
                result = subStr;
            }
            // 如果 textScore 相同，选择字典序更小的子字符串
            else if (textScore == maxScore) {
                if (subStr < result) {
                    result = subStr;
                }
            }
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <wordLen> <maxVowels>" << endl;
        return 1;
    }

    string text = argv[1];
    string prefix = argv[2];
    string suffix = argv[3];

    string result = calculateScore(text, prefix, suffix);
    cout << "Result: " << result << endl;

    return 0;
}