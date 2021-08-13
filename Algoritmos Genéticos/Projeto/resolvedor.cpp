#include<bits/stdc++.h>

using namespace std;

vector<int>solucao;
int fitness=INT_MAX;
vector<vector<int>>grafo;
void cross_OX(vector<int>&pai1,vector<int>&pai2,int V);
void Swap(vector<int>&individuo);
void cross_over(vector<int>sequencia_pai,vector<int>&descendente,int marcador1,int marcador2,int V);
void Calcula_custo(vector<int>vetor,int V);
    int main()

    {
       int V,A,n_geracoes=100,n_individuos=10,max_mutacao=3;
       cin>>V>>A;
       grafo.resize(V);
       solucao.resize(V);
       for(int i=0;i<V;i++){
		grafo[i].resize(V,0);
       }

//le entrada

       for(int i=0;i<A;i++){

		int vertice1,vertice2,custo;
        	cin>>vertice1>>vertice2>>custo;
		grafo[vertice1][vertice2]=custo;
		grafo[vertice2][vertice1]=custo;
		
       }


	vector<vector<int>>lista_individuos;	
	


	//cria uma lista_individuos inicial

        for(int i=0;i<n_individuos;i++){
		vector<int>aleatorio;  

        	for(int i=0;i<V;i++){
			aleatorio.push_back(i);
		} 


		vector<int>individuo;        
 	//Gera um individuo aleatorio inicial	
		while(!aleatorio.empty()){
                        int tam=aleatorio.size();
 			int deletado;//vértice deletado do vetor aleatório
			deletado=rand()%tam;
			individuo.push_back(aleatorio[deletado]);
			aleatorio.erase(aleatorio.begin()+deletado);
		}
	//armazena individuo
		lista_individuos.push_back(individuo);
        } 
        //crossover
		
	//Passa de geração em geração...
        for(int i=0;i<n_geracoes;i++){//para cada geracao


		int qtde_mutacao;//setar
		
            	for(int j=0;j<n_individuos;j+=2){//escolhe o primeiro e segundo    

				Calcula_custo(lista_individuos[j],V);
				Calcula_custo(lista_individuos[j+1],V);
				

			cross_OX(lista_individuos[j],lista_individuos[j+1],V);//realiza o crossover
			if(qtde_mutacao<max_mutacao){
				Swap(lista_individuos[j]);
				qtde_mutacao++;
			}


			
						
			
	    	}


	}		
	
     
		
        cout<<"Solucao: ";
	for(int i=0;i<V;i++){
		cout<<solucao[i]<<" ";
	}
 	cout<<"\nValor: "<<fitness<<endl;
 	
        return 0;

    }   

void cross_OX(vector<int>&pai1,vector<int>&pai2,int V){

//cria os marcadores
 int marcador1= rand()%V,marcador2= rand()%V;
 marcador1=min(marcador1,marcador2);
 marcador2=max(marcador1,marcador2);

//cria os descendentes
 vector<int>descendente1(V),descendente2(V);

//copia os valores entre os marcadores para os descendentes
 for(int i=marcador1;i<=marcador2;i++){
  	descendente1[i]=pai1[i];
        descendente2[i]=pai2[i];
 }
//cria um vetor para o crossover
 vector<int>sequencia_pai1,sequencia_pai2;

//carrega para o 1º descendente partindo do marcador2  ateh adicionar todos os vértices 

 for(int i=marcador2;i<V;i++){
   	sequencia_pai1.push_back(pai1[i]);
 }
 for(int i=0;i<marcador1;i++){
   sequencia_pai1.push_back(pai1[i]);
 }  

 cross_over(sequencia_pai1,descendente2,marcador1,marcador2,V);
 
 //carrega para o 2º descendente  partindo do marcador2  ateh adicionar todos os vértices 
 
 for(int i=marcador2;i<V;i++){
   sequencia_pai2.push_back(pai2[i]);

 }
 for(int i=0;i<marcador2;i++){
   sequencia_pai2.push_back(pai2[i]);
 }  
 cross_over(sequencia_pai2,descendente1,marcador1,marcador2,V);
 
}

void cross_over(vector<int>sequencia_pai,vector<int>&descendente,int marcador1,int marcador2,int V){

 //crossover
 //carrega os valores restantes
 for(int i=marcador2;i<V;i++){
        descendente[i]=sequencia_pai[i];

 }
 for(int i=0;i<marcador2;i++){
        descendente[i]=sequencia_pai[i];
 }  

}

void Swap(vector<int>&individuo){
 int V=individuo.size();
 int a= rand()%V,b= rand()%V,auxiliar;
 auxiliar=individuo[a];
 individuo[a]=individuo[b];
 individuo[b]=auxiliar;
}
void Calcula_custo(vector<int>vetor,int V)
{
	int valor=0;
	for(int k=0;k<V;k++){

		valor+=grafo[vetor[k]][vetor[(k+1)%V]];//soma o custo da aresta				}
					
	}
	if(valor<fitness){// se for melhor
		solucao=vetor;//copia o aux1 para a melhor solucao
		fitness=valor;
	}
}

