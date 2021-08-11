// OO - Monkey
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

class Estado 
{
    private:

        int macaco;

        int graveto;

        int caixa;

        bool sobe_caixa;

        bool possuiGraveto;

        bool possuiBanana;

        int movimento;

        int valor;

    public:

        Estado()
        {
            return;
        }

        Estado(int macaco, int graveto,int caixa,bool sobe_caixa, bool possuiGraveto, bool possuiBanana)

        {
            this->macaco = macaco;

            this->possuiBanana = possuiBanana;

            this->movimento = 0;

            this->valor = 0;

            this->graveto = graveto;

            this->caixa = caixa;

            this->sobe_caixa = sobe_caixa;

            this->possuiGraveto = possuiGraveto;


        }

        void calcula_alcance(Estado objetivo)

        {
            int guarda=0;

            if (this->macaco == objetivo.macaco) guarda++;

            if (this->macaco == this->graveto && !this->possuiGraveto) guarda++;

            if (this->caixa == objetivo.caixa) guarda++;

            if (this->sobe_caixa == objetivo.sobe_caixa) guarda++;

            if (this->possuiGraveto == objetivo.possuiGraveto)guarda++;

            if (this->possuiBanana == objetivo.possuiBanana) guarda++;

            this->valor =  guarda;

        }

        void altera(Estado e, int movimento, int posicao)
        {
            switch (movimento)

            {
                case 1:
                    if (!e.sobe_caixa && e.macaco != posicao)

                    {
                        this->macaco = posicao;
                    }

                    else
                    {   
                        this->movimento = -2;
                    } 

                break;

                case 2:

                    if (!e.sobe_caixa && e.macaco == e.caixa && e.macaco != posicao && e.caixa !=posicao)

                    {
                        this->macaco = posicao;

                        this->caixa =posicao;
                    }

                    else
                    {   
                        this->movimento = -2;
                    }

                break;

                case 3:

                    if (!e.sobe_caixa && e.macaco == e.graveto && !e.possuiGraveto)

                    {
                        this->possuiGraveto = true;
                    }

                    else
                    {   
                        this->movimento = -2;
                    }

                break;

                case 4:

                    if(!e.sobe_caixa && e.macaco == e.caixa)

                    {
                        this->sobe_caixa = true;
                    }

                    else
                    {   
                        this->movimento = -2;
                    }

                break;

                case 5:

                    if (e.sobe_caixa && e.macaco == -1 && e.caixa == -1 && e.possuiGraveto && !e.possuiBanana)

                    {
                        this->possuiBanana = true;
                    }

                    else
                    {   
                        this->movimento = -2;
                    }

                break;

            }

        }

        struct verifica 
        { 
            bool operator()(const Estado est, const Estado est2) const
            { 
                return (est.valor) < (est2.valor); 
            } 
        };

        void solucao(Estado objetivo)
        {
            priority_queue<Estado, std::vector<Estado>, verifica> lista;

            lista.push(*this);

            while(!lista.empty())

            {
                Estado topo = lista.top();

                lista.pop(); 

                topo.imprimeEstado();

                sleep(1);

                if(topo.possuiBanana)

                {
                    break;
                }

                Estado est2;

                //macaco anda

                int it;

                for(it=-1;it<4;it++)
                {    
                    if (it != 0)
                    {
                        est2 = topo;

                        est2.altera(topo, 1, it);

                        est2.calcula_alcance(objetivo);

                        if(est2.movimento!=-2)

                            lista.push(est2);
                    }
                }

                //macaco empurra a caixa

                for(it=-1;it<4;it++)
                {    
                    if (it != 0)
                    {
                        est2 = topo;

                        est2.altera(topo, 2, it);

                        est2.calcula_alcance(objetivo);

                        if(est2.movimento!=-2)

                            lista.push(est2);

                    }
                }

                //macaco sobe na caixa

                est2 = topo;

                est2.altera(topo, 4, 0);

                est2.calcula_alcance(objetivo);

                if(est2.movimento!=-2)

                    lista.push(est2);

                //macaco bate com o bastao no cacho

                est2 = topo;

                est2.altera(topo, 3, 0);

                est2.calcula_alcance(objetivo);

                if(est2.movimento!=-2){

                    est2.imprimeEstado();

                    lista.push(est2);

                }

                //macaco pega o cacho

                est2 = topo;

                est2.altera(topo, 5, 0);

                est2.calcula_alcance(objetivo);

                if(est2.movimento!=-2)

                    lista.push(est2);

            }

        }
        
        void imprimeEstado()

        {
            printf("Localizacao do Macaco = %d\nLocalizacao do Bastao = %d\nLocalizacao da Caixa = %d\nEm cima da Caixa = %d\nPossui o Bastão = %d\nPossui a Banana = %d\n\n", this->macaco, this->graveto, this->caixa, this->sobe_caixa, this->possuiGraveto, this->possuiBanana);

        }

};

int main() 
{   
    Estado e(1, 2, 3, false, false, false);

    Estado objetivo(-1, 2, -1, true, true, true);

    e.calcula_alcance(objetivo);

    objetivo.calcula_alcance(objetivo);

    e.solucao(objetivo);

    return 0; 

} 