//OO-8puzzle

#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
typedef vector<vector<char>> matriz;

class estado{
 public :
 matriz mat;
 void imprime();
 estado(matriz ma); 
 vector<estado> retorna_possibilidades();
 void troca(char &p1,char &p2);
 bool eh_igual(estado a);
 
};



int main()
{
 vector<estado>abertos,fechados;
 matriz aux(3),objetivo(3);


   /*Example
   132
   4*7
   845*/
 for(int i=0;i<3;i++){
     aux[i].resize(3);
     objetivo[i].resize(3);
 }
  cout<<"Digite o estado incial:\n";
  /*Example
   132
   4*5
   678*/
 for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       cin>>aux[i][j];
    }  
 }  
 cout<<"Digite o estado final:\n";
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       cin>>objetivo[i][j];
    }  
  }
 estado *state = new estado(aux),*objetive = new estado(objetivo);
   
abertos.push_back(*state);

while(!abertos.empty()){
   estado auxiliar=abertos.front();
   
   cout<<"processando"<<endl;
   auxiliar.imprime();
   if(auxiliar.eh_igual(*objetive)){
     cout<<"Sucesso!\n";
     break;
   }
   fechados.push_back(auxiliar);
   abertos.erase(abertos.begin());
   
  
   vector<estado>possibilidades=auxiliar.retorna_possibilidades();
   
   for(estado ma:possibilidades){
     bool tem=false;
      for(estado ab:abertos){
          if(ma.eh_igual(ab)){
            tem=true;
            break;
          }
      }
      if(!tem){
          for(estado fech:fechados){
            if(ma.eh_igual(fech)){
              tem=true;
              break;
            }
          }
      }
      if(!tem){
        abertos.push_back(ma);
      }
   }
   
}
  return 0;
}
 estado::estado(matriz ma){
  mat=ma;
}
// faz todas as possibilidades do espaço vazio
 vector<estado> estado ::retorna_possibilidades(){
 vector<estado>possibilidades;
 int posi,posj;
 // pega as posições da matriz
 for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       if(mat[i][j]=='*'){
          posi=i;
          posj=j;
          break;
       }
    }  
 }  

// analisa as possibilidades de movimento do vazio
 
 if(posi+1<=2){
   troca(mat[posi+1][posj],mat[posi][posj]);
   estado *novo = new estado(mat); 
   possibilidades.push_back(*novo);
   troca(mat[posi+1][posj],mat[posi][posj]);
 }        
 if (posj+1<=2){
   troca(mat[posi][posj+1],mat[posi][posj]);
   estado *novo = new estado(mat); 
   possibilidades.push_back(*novo);
   troca(mat[posi][posj+1],mat[posi][posj]);
 }        
     
 if(posi-1 >= 0){
   troca(mat[posi-1][posj],mat[posi][posj]);
   estado *novo = new estado(mat); 
   possibilidades.push_back(*novo);
   troca(mat[posi-1][posj],mat[posi][posj]);
 }
    
 if(posj-1 >= 0){
   troca(mat[posi][posj-1],mat[posi][posj]);
   estado *novo = new estado(mat); 
   possibilidades.push_back(*novo);
   troca(mat[posi][posj-1],mat[posi][posj]);
 }

  return possibilidades;
}

void estado ::troca(char &p1,char &p2){
 char aux=p1;
 p1=p2;
 p2=aux;
}

// verifica se 2 matrizes são iguais
bool estado ::eh_igual(estado a){

for(int i=0;i<3;i++){
  for(int j=0;j<3;j++){
    if(a.mat[i][j]!=mat[i][j])return false;
  }
}
return true;
}
void estado::imprime(){
  for(int i=0;i<3;i++){
      for(int j=0;j<3;j++){
          cout<<mat[i][j]<<" ";
      }
         cout<<endl;
   }
         cout<<endl;
}