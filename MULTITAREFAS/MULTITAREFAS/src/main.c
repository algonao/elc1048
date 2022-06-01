/*
 * Inclusao de arquivos de cabecalhos
 */
#include <asf.h>
#include "stdint.h"
#include "multitarefas.h"
#include "stdlib.h"

/*
 * Prototipos das tarefas
 */

void tarefa_produtor(void);
void tarefa_consumidor(void);
void tarefa_ociosa(void);




/*
 * Configuracao dos tamanhos das pilhas
 */

#define TAM_PILHA_3			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA    (TAM_MINIMO_PILHA + 24)


/*
 * Declaracao das pilhas das tarefas
 */

uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];



#define TAM_BUFFER 10
uint8_t buffer[TAM_BUFFER]; /* declaracao de um buffer (vetor) ou fila circular */

semaforo_t SemaforoCheio = {0,0}; /* declaracao e inicializacao de um semaforo */
semaforo_t SemaforoVazio = {TAM_BUFFER,0}; /* declaracao e inicializacao de um semaforo */


/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	system_init();
	

		/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	CriarTarefa(tarefa_produtor, "Tarefa 3", PILHA_TAREFA_3, TAM_PILHA_3, 1); //produtor

	CriarTarefa(tarefa_consumidor, "Tarefa 4", PILHA_TAREFA_4, TAM_PILHA_4, 2); //consumidor com prioridade maior
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}


uint8_t i, j; 


void tarefa_produtor(void) //produtor
{
	for(;;) 
	{
	SemaforoAguarda(&SemaforoVazio);
	buffer[i] = rand()%10;
	i=(i+1)%TAM_BUFFER;
	SemaforoLibera(&SemaforoCheio);
	}
}
void tarefa_consumidor(void) //consumidor
{

	uint16_t consome; 
	for(;;)
	{
		SemaforoAguarda(&SemaforoCheio);
		consome = buffer[j];
		j = (j+1)%TAM_BUFFER;
		SemaforoLibera(&SemaforoVazio);

	}
}