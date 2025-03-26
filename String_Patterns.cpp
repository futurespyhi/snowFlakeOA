#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// Define the modulo value to avoid integer overflow
const int MOD = 1e9 + 7;

// Function to calculate the number of string patterns
// wordLen: the length of the string
// maxVowels: the maximum number of consecutive vowels allowed
int stringPatterns(int wordLen, int maxVowels) {
    // Initialize a 3D vector for memoization
    // memo[idx][consVowelCount][MAXX] stores the result for a subproblem
    vector<vector<vector<int>>> memo(
        wordLen + 1, 
        vector<vector<int>>(maxVowels + 1, 
        vector<int>(maxVowels + 1, -1))
    );
    
    // Define a lambda function 'solve' to recursively calculate the result
    // idx: the current index in the string being built
    // consVowelCount: the current count of consecutive vowels
    // MAXX: the maximum allowed consecutive vowels
    function<int(int, int, int)> solve = 
        [&](int idx, int consVowelCount, int MAXX) {
            // Base case: if the string is fully built (idx == 0), return 1
            if (idx == 0)
                return 1;
            
            // Check if the result is already memoized
            if (memo[idx][consVowelCount][MAXX] != -1)
                return memo[idx][consVowelCount][MAXX];
            
            int result;
            // If the consecutive vowel count reaches the maximum, only consonants can be used
            if (consVowelCount == MAXX) {
                result = (21LL * solve(idx-1, 0, MAXX)) % MOD;
            } else {
                // Otherwise, we can choose either a consonant or a vowel
                // Choose a consonant (21 possibilities)
                int consonantChoice = (21LL * solve(idx-1, 0, MAXX)) % MOD;
                // Choose a vowel (5 possibilities)
                int vowelChoice = (5LL * solve(idx-1, consVowelCount+1, MAXX)) % MOD;
                // Add the results and take modulo
                result = (consonantChoice + vowelChoice) % MOD;
            }
            
            // Memoize the result
            memo[idx][consVowelCount][MAXX] = result;
            return result;
        };
    
    // Start the recursion with the full word length and initial vowel count 0
    return solve(wordLen, 0, maxVowels);
}

int main() {
    // Read the input values from standard input
    int wordLen, maxVowels;
    cin >> wordLen >> maxVowels;
    
    // Calculate and output the result
    cout << stringPatterns(wordLen, maxVowels) << endl;

    return 0;
}