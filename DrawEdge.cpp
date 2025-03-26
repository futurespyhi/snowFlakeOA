#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;

// Function to return (x^y) % MOD in O(log(y))
long long power(long long x, long long y, const int& MOD) {
    long long res = 1;
    while (y > 0) {
        if (y & 1)
            res = (res * x) % MOD;
        x = (x * x) % MOD;
        y /= 2;
    }
    return res;
}

// Function to return the count of distinct graphs possible with n vertices
long long drawingEdge(int n) {
    // Maximum number of edges for a graph with n vertices
    long long x = (long long)n * (n - 1) / 2;

    // Function to calculate (2^x) % MOD
    return power(2, x, MOD);
}

// Driver code
int main() {
    int n;
    cin >> n;
    cout << drawingEdge(n) << endl;
    return 0;
}