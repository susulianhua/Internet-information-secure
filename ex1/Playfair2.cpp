#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include<vector>
#include<math.h>
#define LOCAL


using namespace std;

int main()
{

    string key;
    cin >> key;

    string plaintext = "";
    string lll;

    #ifdef LOCAL
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
    #endif
    while(getline(cin,lll)){
        for(int i = 0; i < lll.size(); i++){
            plaintext += lll[i];
        }
    }


    char a[5][5];
    string upper_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int flag, cnt;
    vector<char> str;

    for(int i = 0; i < key.length(); i++){
        flag = 0;
        for(int j = 0; j < str.size(); j++){
            if(key[i] == str[j]){
                flag = 1;
                continue;
            }
        }
        if(flag == 0){
            if(key[i] == 'J'){
                int cnt = 0;
                for(int t = 0; t < str.size(); t++){
                    if(str[t] == 'I'){
                        cnt = 1;
                        continue;
                    }
                }
                if(cnt == 0) str.push_back('I');
            }
            else str.push_back(key[i]);
        }
    }

    while(str.size() < 25){
        for(int i = 0; i < upper_list.length(); i++){
            int flag = 0;
            for(int j = 0; j < str.size(); j++){
                if(upper_list[i] == str[j]){
                    flag = 1;
                    continue;
                }
            }
            if(flag == 0) {
                if(upper_list[i] == 'J'){
                    cnt = 0;
                    for(int t = 0; t < str.size(); t++){
                        if(str[t] == 'I'){
                            cnt = 1;
                            continue;
                        }
                    }
                    if(cnt == 0) str.push_back('I');
                }
                else str.push_back(upper_list[i]);
            }

        }
    }
    //
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            a[i][j] = str[5*i + j];
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
    //²ð·ÖÎª2
    vector<string> last;
    string res = "";
    for(int i = 0; i < plaintext.size(); i++){
       if(plaintext[i] != ' '){
          res += plaintext[i];
       }
       else{

            last.push_back(res);
            res = "";
       }
       if(i == plaintext.size()-1){
            last.push_back(res);
            res = "";

       }
   }
   vector<char> hhh;
   int m1,n1,m2,n2;
   for(int i = 0; i < last.size(); i++){
    for(int j = 0; j < last[i].length()/2; j++){
        for(int m = 0; m <5; m++){
            for(int n = 0; n < 5; n++){
                if(a[m][n] == last[i][j*2]){
                    m1 = m;
                    n1 = n;
                }
                if(a[m][n] == last[i][j*2 + 1]){
                    m2 = m;
                    n2 = n;
                }

            }
        }
        if(m1 == m2 && n1 != n2){
            hhh.push_back(a[m1][(n1+4)%5 ]);
            hhh.push_back(a[m2][(n2+4)%5]);

        }
        if(n1 == n2&& m1 != m2){
                hhh.push_back(a[(m1+4)%5][n1]);
                hhh.push_back(a[(m2+4)%5][n2]);
        }
        if(abs(m1-m2) && abs(n1-n2)){
            if(abs(m1-m2) > abs(n1-n2)){
                    hhh.push_back(a[m1][n2]);
                   hhh.push_back(a[m2][n1]);
            }
            else {
                    hhh.push_back(a[m2][n1]);
                    hhh.push_back(a[m1][n2]);
        }

    }
   }
   }
    int b = 0;
   for(int i = 0; i < hhh.size()-2; i++){
    if(hhh[i] == hhh[i+2] && hhh[i+1] == 'X'){
        b = i+1;
        break;
    }
   }
 for(int i = 0; i < hhh.size()/2; i++){
    if(2*i == b){
        cout<<hhh[2*i+1];
        i++;
    }
    else if((2*i+1) == b){
        cout<<hhh[2*i];
        i++;
    }
    cout<<" "<<hhh[2*i]<<hhh[2*i+1];
 }
   cout<<endl;

    return 0;



}
