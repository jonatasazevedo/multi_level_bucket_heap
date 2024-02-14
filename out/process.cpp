#include<bits/stdc++.h>

using namespace std;

set<string> algs = {};
int main(int argc,char *argv[]){
    cout<<"k: "<<argv[1]<<", t: "<<argv[2]<<endl;
    cout<<fixed<<setprecision(2);
    string s;
    string name_alg = "empty",name_dataset = "empty";
    double soma=0;
    int qt=0;
    cout<<"instâncias,dijkstra";
    while(getline(cin,s)){
        if(s.front()!='/'){
            if(s=="dijkstra"){
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
    if(name_alg!="empty") cout<<(soma/qt);
}