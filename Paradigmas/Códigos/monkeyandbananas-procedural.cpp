//Procedural - Monkey

#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;


struct estado
{ 

    int macaco;//posicao do macaco
    int graveto;//posicao do graveto

    int caixa;//posicao da caixa

    bool sobe_caixa;//variavel para indicar se o macaco subiu na caixa
    bool possuiGraveto;// variavel para indicar se possui graveto
    bool possuiBanana;// variavel para indicar se possui banana

    int movimento;
    int valor;

};


// armazena de acordo com os valores. Menores valores tem
// maior prioridade

#define MAXIMO 1024



vector<estado>vetor(MAXIMO);

int ContadorItens = 0; 

bool Vazia()
{
   if( ContadorItens == 0)
   return true;
   return false;
}

void inserir(struct estado dado){//inserir no vetor de estados

    int it = 0;

    // insere data se a fila tiver vazia 

    if(ContadorItens == 0){

        vetor[ContadorItens++] = dado;        

    }else{

        // começa do final da fila
			
    for(it = ContadorItens - 1; it >= 0; it-- ){

        // se os dados forem grandes, joga o item no final

        if(dado.valor < vetor[it].valor){

               vetor[it+1] = vetor[it];

        }else{

            break;

        }            

    }  

    // inserir data 

    vetor[it+1] = dado;

    ContadorItens++;

    }

}

struct estado removerDados(){

   return vetor[--ContadorItens]; 

}

struct estado geraEst(int macaco, int graveto,int caixa,bool sobe_caixa, bool possuiGraveto, bool possuiBanana) 

{ 

    struct estado e;

    e.macaco = macaco;

    e.graveto = graveto;

    e.possuiGraveto = possuiGraveto;

    e.possuiBanana = possuiBanana;

    e.movimento = 0;

    e.valor = 0;

    e.caixa = caixa;

    e.sobe_caixa = sobe_caixa;

    return e; 

}

//calcula o alcance do macaco
int calcula_alcance(struct estado e, struct estado objetivo)
{

    int guarda = 0;

    if (e.macaco == objetivo.macaco) guarda++;

    if (e.macaco == e.graveto && !e.possuiGraveto) guarda++;

    if (e.caixa == objetivo.caixa) guarda++;

    if (e.sobe_caixa == objetivo.sobe_caixa) guarda++;

    if (e.possuiGraveto == objetivo.possuiGraveto) guarda++;

    if (e.possuiBanana == objetivo.possuiBanana) guarda++;

    return guarda;

}

void imprimeEstado(struct estado e)

{

    printf("Localizacao do Macaco = %d\nLocalizacao do Bastao = %d\nLocalizacao da Caixa = %d\nEm cima da Caixa = %d\nPossui o Bastão = %d\nPossui a Banana = %d\n\n", e.macaco, e.graveto, e.caixa, e.sobe_caixa, e.possuiGraveto, e.possuiBanana);

}

struct estado altera(struct estado e, int movimento, int posicao)

{
    //movimento = -2 est2 nao entra na fila
    //movimento = 1 macaco anda
    //movimento = 2 macaco empurra caixa
    //movimento = 3 macaco sobe na caixa
    //movimento = 4 macaco bate com o bastao no cacho
    //movimento = 5 macaco pega o cacho
    switch (movimento)

    {

        case 1:

            if (!e.sobe_caixa && e.macaco != posicao)

            {

                e.macaco = posicao;

                return e;

            }

            else

            {   

                e.movimento = -2;

                return e;

            } 

        break;

        case 2:

            if (!e.sobe_caixa && e.macaco == e.caixa && e.macaco != posicao && e.caixa !=posicao)

            {

                e.macaco = posicao;

                e.caixa =posicao;

                return e;

            }

            else

            {   

                e.movimento = -2;

                return e;

            }

        

        case 3:

            if (!e.sobe_caixa && e.macaco == e.graveto && !e.possuiGraveto)

            {

                e.possuiGraveto = true;

                return e;

            }

            else

            {   

                e.movimento = -2;

                return e;

            }

        case 4:

            if(!e.sobe_caixa && e.macaco == e.caixa)

            {

                e.sobe_caixa = true;

                return e;

            }

            else

            {   

                e.movimento = -2;

                return e;

            }

        case 5:

            if (e.sobe_caixa && e.macaco == -1 && e.caixa == -1 && e.possuiGraveto && !e.possuiBanana)

            {

                e.possuiBanana = true;

                return e;

            }

            else

            {   

                e.movimento = -2;

                return e;

            }

    }

}

// posicoes e ações do macaco 
struct estado solucao(struct estado res, struct estado objetivo)

{

    inserir(res);

    while(!Vazia())

    {

        struct estado del = removerDados();

        imprimeEstado(del);

        sleep(1);

        if(del.possuiBanana) return del;

        struct estado est2;

        //macaco anda

        int it;

        for(it=-1;it<4;it++)

        {    
            if (it != 0)

            {

                est2 = altera(del, 1, it);

                est2.valor = calcula_alcance(est2, objetivo);

                if(est2.movimento!=-2)

                    inserir(est2);

            }

        }

        //macaco empurra caixa

        for(it=-1;it<4;it++)

        {    

            if (it != 0)

            {

                est2 = altera(del, 2, it);

                est2.valor = calcula_alcance(est2, objetivo);

                if(est2.movimento!=-2) inserir(est2);

            }

        }

        //macaco sobe na caixa

        est2 = altera(del, 4, 0);

        est2.valor = calcula_alcance(est2, objetivo);

        if(est2.movimento!=-2) inserir(est2);

        //macaco bate com o bastao no cacho

        est2 = altera(del, 3, 0);

        est2.valor = calcula_alcance(est2, objetivo);

        if(est2.movimento!=-2) inserir(est2);

        //pega o cacho

        est2 = altera(del, 5, 0);

        est2.valor = calcula_alcance(est2, objetivo);

        if(est2.movimento!=-2) inserir(est2);

    }

}

int main() 

{   

    struct estado e;

    e = geraEst(1, 2, 3, false, false, false);

    struct estado objetivo;

    objetivo = geraEst(-1, 2, -1, true, true, true);

    e.valor = calcula_alcance(e, objetivo);

    solucao(e, objetivo);

    return 0; 

} 