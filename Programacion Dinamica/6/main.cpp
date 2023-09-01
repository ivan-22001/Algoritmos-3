#include <iostream>
#include "vector"
#include <cmath>

using namespace std;
vector<vector<tuple<int,vector<int>>>> memo(6, vector<tuple<int,vector<int>>>(15, make_tuple(0, vector<int>())));
vector<vector<int>> M (6,vector<int>(20,0));
tuple<int,vector<int>> min (tuple<int,vector<int>> c1,tuple<int,vector<int>> c2){
    if(get<0>(c1)>0 && get<0>(c2)<0) return c2;
    else if(get<0>(c1)<0 && get<0>(c2)>0) return c1;
    else if(get<0>(c1)>0 && get<0>(c2)>0) {
        tuple<int,vector<int>> min = make_pair(9999,vector<int>{});
        return min;
    }
    if(abs(get<0>(c1)) < abs(get<0>(c2))) {
        return c1;
    }
    else if( abs(get<0>(c1)) ==  abs(get<0>(c2)) ){
        if(get<1>(c1).size() < get<1>(c2).size())
            return c1;
        return c2;
    }
    return c2;
}

tuple<int,vector<int>> vueltoAux(vector<int > B,int c,int i,vector<int> q){
    if(i == 0 ) {
        if(c < 0) {
            return make_pair(c,q);
        }
        else if(c - B[i] < 0){
            q.push_back(B[i]);
            return make_pair(c,q);
        }
        else if(c == 0) return make_pair(c,q);
        else
        {
            q.push_back(B[i]);
            return make_pair(c-B[i],q);
        }
    }
    if(c<0) return make_pair(c,q);
    if(get<0>(memo[i][c]) != 0 && !get<1>(memo[i][c]).empty()) return memo[i][c];

   // if(i == B.size())
     //   return make_tuple(c,q);
    q.push_back(B[i]);
    int next_i = i - 1;
    tuple<int,vector<int>> c1 = vueltoAux(B,c-B[i],next_i,q);
    q.pop_back();
    tuple<int,vector<int>> c2 = vueltoAux(B,c,next_i,q);
    memo[i][c] = min(c1,c2);
    return memo[i][c];
}
tuple<int,int> vuelto (vector<int > B,int c){
    vector<int> usados = get<1>(vueltoAux(B,c,B.size()-1,{}));
    int gasto = 0;
    for(int i : usados){
        gasto += i;
    }
    return make_tuple(gasto,usados.size());
}
int main() {
    vector<int> B = {2,6,5,4,10};
    int c = 14;

    tuple<int,int> min = vuelto(B,c);
    cout << get<0>(min) << "," <<get<1>(min)<<endl;
    return 0;
}
