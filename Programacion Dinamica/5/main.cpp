#include <iostream>
#include "vector"

using namespace std;
int n = 4;
int k = 20;
vector<vector<bool>> M (n,vector<bool>(k,NULL));
bool subset_sum(vector<int> C,int i, int j){
    if(j<0) return false;
    else if(i == 0) return j == 0;
    else if(M[i][j] ==NULL){
        M[i][j] = subset_sum(C,i-1,j) || subset_sum(C,i-1,j-C[i]);
    }
    return M[i][j];
}
int main() {
    vector<int> C = {3,4,2,6};
    int f = 6;
    bool puede = subset_sum(C,3,f);
    cout << puede << endl;
    return 0;
}
