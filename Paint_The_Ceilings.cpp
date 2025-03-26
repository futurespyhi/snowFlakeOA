#include <iostream>
#include <vector>
using namespace std;

long int variantsCount(int n, int s0, int k, int b, int m, long int a) {
    vector<long long int> v;
    v.push_back(s0);
    for (int i = 1; i < n; i++) {
        long long int x = ((k * v[i - 1] + b) % m) + 1 + v[i - 1];
        v.push_back(x);
    }
    long long int j = v.size() - 1;
    long res = 0;
    for (int i = 0; i < v.size(); i++) {
        while (j > i && v[i] * v[j] > a)
            j--;

        if (v[i] * v[j] <= a) {
            long int len = j - i;
            res += len * 2;
            if (v[i] * v[i] <= a)
                res++;
        }
    }
    return res;
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        cout << "Usage: " << argv[0] << " <n> <s0> <k> <b> <m> <a>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    int s0 = atoi(argv[2]);
    int k = atoi(argv[3]);
    int b = atoi(argv[4]);
    int m = atoi(argv[5]);
    long int a = atol(argv[6]);

    long int result = variantsCount(n, s0, k, b, m, a);
    cout << "Result: " << result << endl;

    return 0;
}