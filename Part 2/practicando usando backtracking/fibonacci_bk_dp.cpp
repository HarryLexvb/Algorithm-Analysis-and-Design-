#include <iostream>
using namespace std; 

int fibonacci(int n){ //O(e^n)
  if(n < 2)
    return n; 
  else 
    return fibonacci(n-1)+fibonacci(n-2); 
}

int fibonacci_dp_topdown(int n, int *dp){ //O(n) dp usando estrategia de top down 
  if(dp[n] == 0)
    dp[n] = fibonacci_dp_topdown(n-1, dp)+fibonacci_dp_topdown(n-2, dp); 
  return dp[n]; 
}
  

int main(){
  ///// fibonacci //////
  //cout << fibonacci(7) << endl; 
  ///// fibonacci_dp_topdown //////
  int n = 7, *arr;  
  arr = new int(n); 
  arr[0] = 1; 
  arr[1] = 1; 
  for (int i = 2; i < n; ++i)
    arr[i] = 0; 
  
  cout << fibonacci_dp_topdown(n-1, arr) << endl;
   
}