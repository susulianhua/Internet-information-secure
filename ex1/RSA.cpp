#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LOCAL

using namespace std;


int qiuD(int e, int m){
    int last;
    for(int i = 1; i < m; i++){
        if((e * i) % m == 1){
            last = i;
            break;
        }
    }
    return last;
}

int ensure(int a, int b){
    int z = b;
    while(a % b != 0){
        z = a % b;
        a = b;
        b =z;
    }
    return b;
}

int jiami(char s, int e, int n){
    int m = s;
    int t = 1;
    while(e){
        t = t * m;
        t = t % n;
        e--;
    }
    return t;
}

char jiemi(int t, int d, int n){
    int m = 1;
    while(d){
        m = m * t;
        m = m % n;
        d--;
    }
    char a = m;
    return a;
}

int main(){
    int p, q , N, E, L, D, flag;

    //p， q为素数且互质
    cin>>p>>q>>E;
    N = p * q;
    L = ( p - 1 ) * ( q - 1 );
    int l = L;
    int c = ensure(l, E);
    if(c != 1){
        return 1;
    }
    D = qiuD(E, L);
    cout<<(42*42*97)%323;
    cin>>flag;

    #ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
    #endif

  // flag为1则为加密
  if(flag == 1){
    string test;
    while(getline(cin,test)){
        for(int i = 0; i < test.size(); i++){
            if(test[i] != ' ' && test[i] != '/r'){
                cout<<jiami(test[i], E, N)<<" ";

            }
        }
    }
}
 //flag 为其他数时则为解密
  else{
    string test;
    int res = 0;
    while(getline(cin,test)){
        for(int i = 0; i < test.size(); i++){
            if(test[i] != ' ' && test[i] != '/r'){
                    int hhh = test[i];
                    hhh = hhh - 48;
                    res = res * 10 + hhh;
            }
            else{
                if(res){
                    cout<<jiemi(res, D, N);
                    res = 0;
                }
            }
            if(i == test.size() - 1){
                    cout<<jiemi(res, D, N);

            }
        }
    }
}
    return 0;






}
