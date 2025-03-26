#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 全局变量，用于存储所有有效的时间表
vector<string> timeTable;

// 递归函数，生成所有可能的时间表
void createTable(vector<string>& schedule, int idx, int remainingHours, int dayHours) {
    // 如果处理完所有天数
    if (idx == schedule.size()) {
        // 如果剩余需要分配的工作时间为0，说明这是一个有效的时间表
        if (remainingHours == 0) {
            string result;
            for (const string& s : schedule) {
                result += s;
            }
            timeTable.push_back(result);
        }
        return;
    }

    // 如果当前字符是问号'?'
    if (schedule[idx] == "?") {
        // 尝试所有可能的工作时间（从0到dayHours）
        for (int i = 0; i <= dayHours; i++) {
            // 如果剩余工作时间不足以分配i小时，则跳过
            if (remainingHours - i < 0) continue;

            // 保存当前字符的值，用于回溯
            string buffer = schedule[idx];
            schedule[idx] = to_string(i);

            // 递归处理下一个字符
            createTable(schedule, idx + 1, remainingHours - i, dayHours);

            // 回溯，恢复当前字符的值
            schedule[idx] = buffer;
        }
    } else {
        // 如果当前字符是固定数字，则直接递归处理下一个字符
        createTable(schedule, idx + 1, remainingHours, dayHours);
    }
}

// 构造函数，计算已确定的工作时间并调用createTable
vector<string> construct(int workHours, int dayHours, string pattern) {
    int worked_hrs = 0;
    int variation = 0;

    // 将pattern拆分为字符数组
    vector<string> list_pattern;
    for (char c : pattern) {
        list_pattern.push_back(string(1, c));
    }

    // 计算已确定的工作时间总和
    for (const string& s : list_pattern) {
        if (s != "?") {
            worked_hrs += stoi(s);
        }
    }

    // 计算需要分配的工作时间
    variation = workHours - worked_hrs;

    // 清空全局变量timeTable
    timeTable.clear();

    // 调用递归函数生成所有可能的时间表
    createTable(list_pattern, 0, variation, dayHours);

    // 返回所有有效的时间表
    return timeTable;
}

// 主函数，调用construct并返回结果
vector<string> findSchedules(int workHours, int dayHours, string pattern) {
    return construct(workHours, dayHours, pattern);
}

// 测试函数
int main() {
    // 测试用例1
    int workHours1 = 56;
    int dayHours1 = 8;
    string pattern1 = "???8???";
    vector<string> result1 = findSchedules(workHours1, dayHours1, pattern1);

    cout << "Test Case 1:" << endl;
    for (const string& s : result1) {
        cout << s << endl;
    }

    // 测试用例2
    int workHours2 = 3;
    int dayHours2 = 2;
    string pattern2 = "??2??00";
    vector<string> result2 = findSchedules(workHours2, dayHours2, pattern2);

    cout << "\nTest Case 2:" << endl;
    for (const string& s : result2) {
        cout << s << endl;
    }

    // 测试用例3
    int workHours3 = 24;
    int dayHours3 = 4;
    string pattern3 = "08??840";
    vector<string> result3 = findSchedules(workHours3, dayHours3, pattern3);

    cout << "\nTest Case 3:" << endl;
    for (const string& s : result3) {
        cout << s << endl;
    }

    return 0;
}