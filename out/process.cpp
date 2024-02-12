#include<bits/stdc++.h>

using namespace std;

set<string> algs = {"dijkstra","rdijkstra","rdijkstra-v2","rauction","rauction-v2"};
int main(){
    cout<<fixed<<setprecision(2);
    string s;
    string name_alg = "empty",name_dataset = "empty";
    double soma=0;
    int qt=0;
    cout<<"instâncias,dijkstra,rdijkstra,rdijkstra-v2,rauction,rauction-v2";
    while(getline(cin,s)){
        if(s.front()!='/'){
            if(algs.find(s)!=algs.end()){
                if(s!=name_alg && name_alg!="empty"){
                    cout<<(soma/qt)<<",";
                    name_alg=s;
                    soma=0;
                    qt=0;
                }
                name_alg=s;
            }
            else if(isalpha(s.back())){
                if(name_alg!="empty"){
                    cout<<(soma/qt)<<",";
                    soma=0;
                    qt=0;
                    name_alg = "empty";
                }
                cout<<endl<<s<<","; //printa nome de dataset
                name_dataset=s;
            }
            else if(name_dataset!=s){
                soma+=stod(s);
                qt++;
            }
        }
    }
}