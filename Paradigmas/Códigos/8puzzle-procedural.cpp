//Procedural-8puzzle

#include<bits/stdc++.h>
#include<unistd.h>

using namespace std;
typedef vector<vector<char>> matriz;
vector<matriz> retorna_possibilidades(matriz m);
void troca(char &p1,char &p2);
bool eh_igual(matriz a,matriz b);
void imprime(matriz ma);
int main()
{
 vector<matriz>abertos,fechados;
 matriz aux(3),objetivo(3);

 for(int i=0;i<3;i++){
     aux[i].resize(3);
     objetivo[i].resize(3);
 }
   cout<<"Digite o estado incial:\n";
   /*Example
   132
   4*7
   845*/

 for(int i=0;i<3;i++){

   
    for(int j=0;j<3;j++){
      cin>>aux[i][j];
       
    } 

 }  
    cout<<"Digite o estado final:\n";
  /*Example
   132
   4*5
   678*/
   
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       cin>>objetivo[i][j];
    }  

  } 
   
abertos.push_back(aux);

while(!abertos.empty()){
   aux=abertos.front();
   imprime(aux);
   cout<<"processando"<<endl;
   if(eh_igual(aux,objetivo)){cout<<"Sucesso!\n";
     break;}
   
   fechados.push_back(aux);
   abertos.erase(abertos.begin());
   //cout<<abertos.size()<<endl;
   vector<matriz>possibilidades=retorna_possibilidades(aux);
   
   for(matriz ma:possibilidades){
     bool tem=false;
      for(matriz ab:abertos){
          if(eh_igual(ma,ab)){
            tem=true;
            break;
          }
      }
      if(!tem){
          for(matriz fech:fechados){
            if(eh_igual(ma,fech)){
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
// faz todas as possibilidades do espaço vazio
 vector<matriz> retorna_possibilidades(matriz m){
 vector<matriz>possibilidades;
 int posi,posj;
 // pega as posições da matriz
 for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
       if(m[i][j]=='*'){
          posi=i;
          posj=j;
          break;
       }
    }  
 }  

// analisa as possibilidades de movimento do vazio
 
 if(posi+1<=2){
   troca(m[posi+1][posj],m[posi][posj]);
   possibilidades.push_back(m);
   troca(m[posi+1][posj],m[posi][posj]);
 }        
 if (posj+1<=2){
   troca(m[posi][posj+1],m[posi][posj]);
   possibilidades.push_back(m);
   troca(m[posi][posj+1],m[posi][posj]);
 }        
     
 if(posi-1 >= 0){
   troca(m[posi-1][posj],m[posi][posj]);
   possibilidades.push_back(m);
   troca(m[posi-1][posj],m[posi][posj]);
 }
    
 if(posj-1 >= 0){
   troca(m[posi][posj-1],m[posi][posj]);
   possibilidades.push_back(m);
   troca(m[posi][posj-1],m[posi][posj]);
 }

  return possibilidades;
}

void troca(char &p1,char &p2){
 char aux=p1;
 p1=p2;
 p2=aux;
}

// verifica se 2 matrizes são iguais
bool eh_igual(matriz a,matriz b){

for(int i=0;i<3;i++){
  for(int j=0;j<3;j++){
    if(a[i][j]!=b[i][j])return false;
  }
}
return true;
}
void imprime(matriz ma){
   for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<ma[i][j]<<" ";
        }
        cout<<endl;
   }
}