/**
 * \file
 *
 * \brief Exemplos diversos de tarefas e funcionalidades de um sistema operacional multitarefas.
 *
 */

/**
 * \mainpage Sistema operacional multitarefas
 *
 * \par Exemplso de tarefas
 *
 * Este arquivo contem exemplos diversos de tarefas e 
 * funcionalidades de um sistema operacional multitarefas.
 *
 *
 * \par Conteudo
 *
 * -# Inclui funcoes do sistema multitarefas (atraves de multitarefas.h)
 * -# Inicializa  o do processador e do sistema multitarefas
 * -# Cria  o de tarefas de demonstra  o
 *
 */

/*
 * Inclusao de arquivos de cabecalhos
 */
#include <asf.h>
#include "stdint.h"
#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
void tarefa_4(void);
void tarefa_5(void);
void tarefa_6(void);
void tarefa_7(void);
void tarefa_8(void);
/* Prototipo da Nova Tarefa : A_Tarefa */
void A_Tarefa(void);


/*
 * Declaracao das pilhas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_5[TAM_PILHA_5];
uint32_t PILHA_TAREFA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_7[TAM_PILHA_7];
uint32_t PILHA_TAREFA_8[TAM_PILHA_8];
/* Pilha da Nova Tarefa : A_Tarefa */
uint32_t PILHA_A_TAREFA[TAM_A_TAREFA];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

*/
 * tamanhos das pilhas
 */
#define TAM_PILHA_1			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_7			(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_8			(TAM_MINIMO_PILHA + 24)
/* Tamanho de Pilha da Nova Tarefa : A_Tarefa */
#define TAM_A_TAREFA		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)



/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	system_init();
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa( A_Tarefa, "A TAREFA", PILHA_A_TAREFA, TAM_A_TAREFA, 1);
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 2);
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 3);
	
	
	
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

/* Tarefas de exemplo que usam funcoes para suspender/continuar as tarefas */

void A_Tarefa(void)
{
	volatile uint16_t z = 0;
	for(;;)
	{
		z++;
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE); /* Liga LED. */
		TarefaContinua(1);
		
	}
}


void tarefa_1(void)
{
	volatile uint16_t z = 0;
	for(;;)
	{
		z++;
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE); /* Liga LED. */
		TarefaContinua(2);
	
	}
}

void tarefa_2(void)
{
	volatile uint16_t x = 0;
	for(;;)
	{
		x++;
		TarefaSuspende(2);	
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE); 	/* Turn LED off. */
	}
}

/* Tarefas de exemplo que usam funcoes para suspender as tarefas por algum tempo (atraso/delay) */
void tarefa_3(void)
{
	volatile uint16_t z = 0;
	for(;;)
	{
		z++;	
			
		/* Liga LED. */
		port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 em espera por 3 ticks */
		
		/* Desliga LED. */
		port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		TarefaEspera(1000); 	/* tarefa 1 em espera por 3 ticks */
	}
}

void tarefa_4(void)
{
	volatile uint16_t x = 0;
	for(;;)
	{
		x++;
		TarefaEspera(5);	/* tarefa em espera por 5 ticks */
	}
}

/* Tarefas de exemplo que usam funcoes de semaforo */

semaforo_t SemaforoTeste = {0,0}; /* declaracao e inicializacao de um semaforo */

void tarefa_5(void)
{

	uint32_t z = 0;			/* inicializacoes para a tarefa */
	
	for(;;)
	{
		
		z++;				/* codigo exemplo da tarefa */

		TarefaEspera(3); 	/* tarefa em espera por 3 ticks */
		
		SemaforoLibera(&SemaforoTeste); /* tarefa libera semaforo para tarefa que esta esperando-o */
		
	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_6(void)
{
	
	uint32_t x = 0;	    /* inicializacoes */
	
	for(;;)
	{
		
		x++; 			/* codigo exemplo  */
		
		SemaforoAguarda(&SemaforoTeste); /* tarefa se coloca em espera por semaforo */

	}
}

/* solucao com buffer compartihado */
/* Tarefas de exemplo que usam funcoes de semaforo */

#define TAM_BUFFER 10
uint8_t buffer[TAM_BUFFER]; /* declaracao de um buffer (vetor) ou fila circular */

semaforo_t SemaforoCheio = {0,0}; /* declaracao e inicializacao de um semaforo */
semaforo_t SemaforoVazio = {TAM_BUFFER,0}; /* declaracao e inicializacao de um semaforo */

void tarefa_7(void)
{

	uint8_t z = 1;			/* inicializacoes para a tarefa */
	uint8_t i = 0;
	
	for(;;)
	{
		SemaforoAguarda(&SemaforoVazio);
		
		buffer[i] = z++;
		i = (i+1)%TAM_BUFFER;
		
		SemaforoLibera(&SemaforoCheio); /* tarefa libera semaforo para tarefa que esta esperando-o */
		
		TarefaEspera(10); 	/* tarefa se coloca em espera por 10  (ticks), equivalente a 10ms */		
	}
}

/* Exemplo de tarefa que usa semaforo */
void tarefa_8(void)
{
	static uint8_t f = 0;
	volatile uint8_t valor;
		
	for(;;)
	{
		volatile uint8_t contador;
		
		do{
			REG_ATOMICA_INICIO();			
				contador = SemaforoCheio.contador;			
			REG_ATOMICA_FIM();
			
			if (contador == 0)
			{
				TarefaEspera(100);
			}
				
		} while (!contador);
		
		SemaforoAguarda(&SemaforoCheio);
		
		valor = buffer[f];
		f = (f+1) % TAM_BUFFER;	
		
		(void)valor;	/* leitura da variavel  */
		
		SemaforoLibera(&SemaforoVazio);
	}
}
