#include <iostream>
#include<stdio.h>
#include<math.h>
#include<string>
#include<string.h>
#define LOCAL

using namespace std;


long long jiami(char ch ,int E , int N){
    int a = ch;
    long long b = pow(a,E);
    b = b%N;
    return b;
}

char jiemi(int a,int D,int N){
    long long b = pow(a,D);
    int c = b%N;
    char d = b;
    return d;
}

int main()
{
    int p ,q , E, D;
    cin>>p>>q;
    int N = p*q;
    int L = (p-1) * (q-1);
    for(int i = p; i < L; i++){
        if(i%(p-1) == 0 && i%(q-1) == 0){
            L = i;
            break;
        }
    }
    int flag = 0;

    for(int i = 2; i < L; i++){
            for(int j = 2; j <= i; j++){
                if(i%j == 0 && L%j == 0){
                    flag = 1;
                }
            }
            if(flag == 0){
                E = i;
                break;
            }
            flag = 0;
    }

    for(int i = 2; i < L; i++){
        if((E*i)%L == 1){
            D = i;
            break;
        }
    }
    #ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
    #endif

    string input;
    while(getline(cin,input)){
        for(int i = 0; i < input.size(); i++){
            int t = jiami(input[i], E, N);
            cout<<t<<" ";
        }
    }
    cout<<endl;


    return 0;
}
