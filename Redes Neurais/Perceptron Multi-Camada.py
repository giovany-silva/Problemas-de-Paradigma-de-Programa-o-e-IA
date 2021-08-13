#Perceptron múltiplas camadas 
#biblioteca que faz cálculos com arrays
import numpy as num 

def funcao_sigmoide (x):
    return 1/(1 + num.exp(-x))

def derivada_sigmoide(x):
    return x * (1 - x)

# valores de entrada
entradas = num.array([[0,0],[0,1],[1,0],[1,1]])

saida_esperada = num.array([[0],[1],[1],[0]])

n_epocas = 10000
taxa_aprendizado = 0.1
#numero de camadas da entrada, da saída e da parte oculta
num_camada_entrada, n_camada_oculta, n_camada_saida = 2,1,1

#inicializa o vies e coloca pesos iniciais aleatórios
peso_oculto = num.random.uniform(size=(num_camada_entrada,n_camada_oculta))
vies_oculto =num.random.uniform(size=(1,n_camada_oculta))
peso_saida = num.random.uniform(size=(n_camada_oculta,n_camada_saida))
vies_saida = num.random.uniform(size=(1,n_camada_saida))

print("Pesos ocultos iniciais: ",end='')
print(*peso_oculto)
print("\nVies ocultos iniciais: ",end='')
print(*vies_oculto)
print("\nPesos inicias de saída: ",end='')
print(*peso_saida)
print("\nVies inicias de saída: ",end='')
print(*vies_saida)


#Para todas as epócas
for _ in range(n_epocas):
	camada_oculta_ativacao = num.dot(entradas,peso_oculto)

	camada_oculta_ativacao += vies_oculto

	saida_camada_oculta = funcao_sigmoide(camada_oculta_ativacao)

	saida_camada_ativacao = num.dot(saida_camada_oculta,peso_saida)

	saida_camada_ativacao += vies_saida

	saida_prevista = funcao_sigmoide(saida_camada_ativacao)

	#Cálculo do erro
	erro = saida_esperada - saida_prevista

	d_saida_prevista = erro * derivada_sigmoide(saida_prevista)
	
  #.dot produto dos dois arrays
	erro_camada_oculta = d_saida_prevista.dot(peso_saida.T)

	d_camada_oculto = erro_camada_oculta * derivada_sigmoide(saida_camada_oculta)

	#Atualizando pesos e viés
	peso_saida += saida_camada_oculta.T.dot(d_saida_prevista) * taxa_aprendizado

	vies_saida += num.sum(d_saida_prevista,axis=0,keepdims=True) * taxa_aprendizado

	peso_oculto += entradas.T.dot(d_camada_oculto) * taxa_aprendizado
  
	vies_oculto += num.sum(d_camada_oculto,axis=0,keepdims=True) * taxa_aprendizado

print("\nPesos ocultos finais: ",end='')
print(*peso_oculto)
print("\nVies oculta final: ",end='')
print(*vies_oculto)
print("\nPesos de saida final: ",end='')
print(*peso_saida)
print("\nVies de saída final: ",end='')
print(*vies_saida)

print("\nSaída da rede neural apos 10.000 epócas: ",end='')
print(*saida_prevista)