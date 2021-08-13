#include<bits/stdc++.h>
using namespace std;
#define N_MAX 2
#define TAXA 0.7
double w1,w2,w3;
// entradas da tabela 11.3
vector<pair<double,double>> entrada={{1,1},{9.4,6.4},{2.5,2.1},{8,7.7},{0.5,2.2},{7.9,8.4},{7,7},{2.8,0.8},{1.2,3},{7.8,6.1}};

vector<int>saida={1,-1,1,-1,1,-1,-1,1,1,-1};
void atualiza_peso(int saida2,int i);

int main()
{
 //pesos aleatorios iniciais
   int positivo = rand()%2;
    w1 = rand()%100/100;
   if(!positivo){
     w1*=-1;
   }
   int positivo2 = rand()%2;
   w2 = rand()%100/100;
   if(!positivo2){
     w2*=-1;
   }

   int positivo3 = rand()%2;
   w3 = rand()%100/100;
   if(!positivo3){
     w3*=-1;
   }
   // para todos os pontos da tabela 

 
  for(int i=0;i<10;i++){
      for(int j=0;j<N_MAX;j++){
        
         double func_ativacao=entrada[i].first*w1+entrada[i].second*w2+w3;
         //saida da func_ativacao
         int saida2=1;        
         //verifica a saida de ativacao
         if(func_ativacao<0){
              saida2=-1;
         }
         if(saida2 != saida[i]){
           atualiza_peso(saida2, i);
         }
         else {
           break;
         }

      }   

  }
 
cout<<"Função :"<<w1<<"*x1+"<<w2<<"*x2+"<<w3<<"=0"<<endl;


  return 0;
}



void atualiza_peso(int saida2,int i){
    //compara a saida de ativacao com a da tabela
    // e passa o valor que vai multiplicar c
    int parenteses = 0;
         //if(saida2!=saida[i]){
    if(saida2 == -1 && saida[i] == 1){
        parenteses = 2.0;
    }
    if(saida2 == 1 && saida[i] == -1){
          parenteses = -2.0;
    }
    // faz o 2c ou -2c
    double aprendizado = TAXA * parenteses;
    // calcula os novos pesos
    w1 = w1 + aprendizado * entrada[i].first; 
    w2 = w2 + aprendizado * entrada[i].second;
    w3 = w3 + aprendizado;
 }

