//Procedural-8queen

#include<bits/stdc++.h>
using namespace std;
typedef vector<pair<int,int>> matriz;
bool valida(matriz ma);
void imprime(matriz ma);
void solve(matriz ma,int i);
int main()
{
  matriz ma(8);
  solve(ma,0);
  return 0;
}

void solve(matriz ma,int i){

 if(i==8){
   if(valida(ma)){
           imprime(ma);
           exit(0);
   }
}
else{
 for(int j=0;j<8;j++){
   ma[i].first=i;
   ma[i].second=j;

   solve(ma,i+1);
 }
}
}

bool valida(matriz ma){
for(int i=0;i<8;i++){
   for(int j=i+1;j<8;j++){
     if(ma[i].first==ma[j].first || ma[i].second==ma[j].second ||
       (abs(ma[i].second-ma[j].second))==(abs(ma[i].first-ma[j].first)))return false;
     
   }
}
return true;
}

void imprime(matriz ma){
cout<<"Solução:\n";
for (int i=0;i <8;i++){
  cout<<"("<<ma[i].first<<"," <<ma[i].second<<" )"<<endl;
}

}