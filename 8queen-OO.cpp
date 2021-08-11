//OO-8queen

#include<bits/stdc++.h>
using namespace std;
typedef vector<pair<int,int>> matriz;
class solucao{
public:
matriz ma;
void imprime();
solucao();
};
class conjunto{
  public:
  solucao *estado;
  vector<solucao>solucoes;
  void solve(int pos);
  bool valida();
  void imprime();
  conjunto();
};
int main()
{
  conjunto * solver = new conjunto();
  solver->solve(0);
  solver->imprime();


  return 0;
}

void conjunto::solve(int i){

 if(i==8){
   if(valida()){
           solucoes.push_back(*estado);
   }
 }
else{
 for(int j=0;j<8;j++){
      estado->ma[i].first=i;
      estado->ma[i].second=j;
      solve(i+1);
 }
}
}

bool conjunto::valida(){
for(int i=0;i<8;i++){
   for(int j=i+1;j<8;j++){
     if(estado->ma[i].first==estado->ma[j].first || estado->ma[i].second==estado->ma[j].second ||
       (abs(estado->ma[i].second-estado->ma[j].second))==(abs(estado->ma[i].first-estado->ma[j].first)))return false;
     
   }
}
return true;
}

void solucao::imprime(){
for (int i=0;i <8;i++){
  cout<<"("<<ma[i].first<<"," <<ma[i].second<<" )"<<endl;
}

}
conjunto::conjunto(){
 
  estado = new solucao();
}
solucao::solucao(){
  ma.resize(8);

}
void conjunto::imprime(){
cout<<"Soluções\n";
  for(solucao s:solucoes){
        s.imprime();
        cout<<"\n";     
  }
}