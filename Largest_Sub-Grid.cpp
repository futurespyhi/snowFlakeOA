#include <vector>
#include <iostream>
using namespace std;
vector<vector<int>> preSum;
int getSum(int row, int col){
  if(row < 0 || col < 0)
    return 0;
  return preSum[row][col];
}

int sumRegion(int row1, int col1, int row2, int col2) {
  return getSum(row2,col2) - getSum(row1-1,col2) - getSum(row2,col1-1) + getSum(row1-1,col1-1);
}

int largestSubgrid(vector<vector<int>>& grid, int k){
  int n = grid.size();
  preSum.resize(n,vector<int>(n,0));
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      preSum[i][j] = getSum(i-1,j) + getSum(i,j-1) - getSum(i-1,j-1) + grid[i][j];
    }
  }
  int low = 0, high = n, ans = 0;
  while(low <= high){
    int mid = low + (high - low)/2;
    if(mid == 0)
    return 0;
    bool stop = false;
    for(int i=mid-1; i<n && !stop; i++){
      for(int j=mid-1; j<n && !stop; j++){
        int subSum = sumRegion(i-mid+1,j-mid+1,i,j);
        if(subSum > k){
          stop = true;
        }
      }
    }
    if(stop){
      high = mid - 1;
    }
    else{
      ans = mid;
      low = mid + 1;
    }
  }
  return ans;
}
int main() {
  // Test Case 0
  vector<vector<int>> mat0 = {
      {1, 1, 1},
      {1, 1, 1},
      {1, 1, 1}
  };
  cout << "Test Case 0: " << largestSubgrid(mat0, 4) << endl;

  // Test Case 1
  vector<vector<int>> mat1 = {
      {1, 1, 1, 1},
      {2, 2, 2, 2},
      {3, 3, 3, 3},
      {4, 4, 4, 4}
  };
  cout << "Test Case 1: " << largestSubgrid(mat1, 39) << endl;

  // Test Case 2
  vector<vector<int>> mat2 = {
      {4, 5},
      {6, 7}
  };
  cout << "Test Case 2: " << largestSubgrid(mat2, 2) << endl;

  // Your original test case
  vector<vector<int>> mat3 = {
      {2,2,2},
      {3,3,3},
      {4,4,4}
  };
  cout << "Original Test Case: " << largestSubgrid(mat3, 3) << endl;

  return 0;
}