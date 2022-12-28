#include <iostream>
using namespace std; 

int bk(int n){ //backtracking
  if(n < 0)
    return 0; 
  if(n == 0)
    return 1; 
  return bk(n-4)+bk(n-3)+bk(n-1); 
}

int dp_buttonup(int n, int *a){ //dp using button up 
  for(int i = 4; i < n; ++i)
    a[n] = a[i-4]+a[i-3]+a[i-1];
  return a[n]; 
}

int dp_topdown(int n, int *a){ // dp using topdown 
  if(a[n] == 0)
    a[n] = dp_topdown(n-4,a)+dp_topdown(n-3,a)+dp_topdown(n-1,a); 
  return a[n]; 
}

int main(){
  cout << bk(5) << endl;  
  int a[10] = {0,1,1,2,4,0,0,0,0,0};  
  cout << dp_buttonup(5, a) << endl;    
  cout << dp_topdown(5, a) << endl;    
}