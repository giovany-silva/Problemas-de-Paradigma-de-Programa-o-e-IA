#include<bits/stdc++.h>
using namespace std;
float wa1, wa2, wb1, wb2;
// entradas da tabela 11.3
vector<pair<float,float>> entrada={{1,1},{9.4,6.4},{2.5,2.1},{8,7.7},{0.5,2.2},{7.9,8.4},{7,7},{2.8,0.8},{1.2,3},{7.8,6.1}};
void atualiza_peso(float &peso1, float &peso2, int i);

int main(){
  //coordenadas iniciais dos pontos
  int positivo = rand()%11;
  wa1 = positivo;
  int positivo2 = rand()%11;
  wa2 = positivo2;
  int positivo3 = rand()%11;
  wb1 = positivo3;
  int positivo4 = rand()%11;
  wb2 = positivo4;
  cout<<"Inicial A("<<wa1<<","<<wa2<<")\nInicial B("<<wb1<<","<<wb2<<")"<<endl;

  //para todos os pontos da tabela
  //nao peguei aleatório, mas talvez precise
  for(int i=0;i<10;i++){
    //dividindo a conta da distancia
    float aux1 = entrada[i].first - wa1;
    float aux2 = entrada[i].second - wa2;
    float aux3 = entrada[i].first - wb1;
    float aux4 = entrada[i].second - wb2;
    //distancia do ponto até A
    float distanciaA = pow(aux1,2) + pow(aux2,2);
    //distancia do ponto até B
    float distanciaB = pow(aux3,2) + pow(aux4,2);

    //definir o ponto que vai para atualização A ou B
    if(distanciaA < distanciaB){
      atualiza_peso(wa1, wa2,i);
    }
    else{
      atualiza_peso(wb1, wb2, i);
    }
  }
  cout<<"A("<<wa1<<", "<<wa2<<")\nB("<<wb1<<", "<<wb2<<")"<<endl;
  return 0;
}
//atualiza peso para o ponto A
void atualiza_peso(float &peso1, float &peso2, int i){
  // ponto da tabela menos wa1
  float passo1 = (entrada[i].first - peso1);
  // ponto da tabela menos wa2
  float passo2 = (entrada[i].second - peso2);
  // multiplica os resultados anteriores pela taxa de aprendizado
  float passo3 = 0.9 * passo1; 
  float passo4 = 0.9 * passo2;
  //soma o passo anterior com wa1 e wa2
  peso1 = entrada[i].first + passo3;
  peso2 = entrada[i].second + passo4;

}
