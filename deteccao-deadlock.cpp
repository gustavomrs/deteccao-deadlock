#include <stdio.h>

#define N 3
#define M 3

#define S1 0
#define S2 1
#define S3 2

/*						S0  	S1  	S2				*/
int disponivel[M] = { 	10, 	6, 		2 		};
int alocacao[N][M] = 
						{
/*								S0		S1		S2		*/
			/*P0*/			{	1,		2,		2	},
			/*P1*/			{	0,		0,		3	},
			/*P2*/			{	3,		3,		0	}
						};	
int solicitacao[N][M] =
						{
/*								S0		S1		S2		*/
			/*P0*/			{	13,		9,		3	},
			/*P1*/			{	2,		3,		2	},
			/*P2*/			{	1,		2,		3	}
						};


/*A partir daqui inicia o seu código*/

int i, j, k, atendido;
bool verifica_atendimento[N];
bool verifica_deadlock = false;
int ordem_atendimento[N], numero_atendimento = 0;


void tenta_atender_processos_nao_atendidos(int num_processo) {
	atendido = 0;
	for(j = 0; j < M; j++) {
		if(solicitacao[num_processo][j] <= disponivel[j]) {
			// pra debug: printf("%d => %d\n", solicitacao[i][j], disponivel[j]);
			atendido++;
		}
	}

	if(atendido == M) {
		/*se o processo pode ser atendido, atualiza  o array de disponiveis (o que é feito de verdade é a atualização do array disponivel
		a ideia de atender um processo é abstrata*/
		int z;
		for(z = 0; z < M; z++) {
			disponivel[z] = disponivel[z] + alocacao[num_processo][z];
			alocacao[num_processo][z] = 0;
		}
		/* 	verifica atendimento armazena se o processo foi atendido ou nao, com uma flag true ou false
			ordem_atendimento armazena a ordem que os processos foram atendidos
		*/
		verifica_atendimento[num_processo] = true;
		ordem_atendimento[numero_atendimento] = num_processo;
		numero_atendimento++;
		// pra debug: printf("Mprocesso p%d atendido!\n", num_processo);
	}
}

int main (int argc, char *argv[])
{
	for(i = 0 ; i < N; i++)
		verifica_atendimento[i] = true;

	for(i = 0; i < N; i++) {
		atendido = 0;
		// pra debug: printf("%d : \n\n", i);
		for(j = 0; j < M; j++) {
			if(solicitacao[i][j] <= disponivel[j]) {
				// pra debug: printf("%d => %d\n", solicitacao[i][j], disponivel[j]);
				atendido++;
			}
		}
		//se a condicao for verdadeira, significa que o processo pode ser atendido com os recursos que ele deseja
		if(atendido == M) {
			/*se o processo pode ser atendido, atualiza  o array de disponiveis (o que é feito de verdade é a atualização do array disponivel
			a ideia de atender um processo é abstrata*/
			for(k = 0; k < M; k++) {
				disponivel[k] = disponivel[k] + alocacao[i][k];
				alocacao[i][k] = 0;
			}
			/* 	verifica atendimento armazena se o processo foi atendido ou nao, com uma flag true ou false
				ordem_atendimento armazena a ordem que os processos foram atendidos
			*/
			verifica_atendimento[i] = true;
			ordem_atendimento[numero_atendimento] = i;
			numero_atendimento++;
			// pra debug: printf("processo p%d atendido!\n", i);
			//varrer a lista de nao atendidos, para ver se um novo processo pode ser atendido agora
			for(k = 0; k < N; k++) {
				if(verifica_atendimento[k] == false)
					tenta_atender_processos_nao_atendidos(k);				
			}

		}
		else {
			verifica_atendimento[i] = false;
		}
		
	}

	for(i = 0; i < N; i++)
		if(!verifica_atendimento[i])
			verifica_deadlock = true;

	if(verifica_deadlock) { 
		printf("Houve deadlock com os seguintes processos:");
		for(i = 0; i < N; i++)
			if(verifica_atendimento[i] == false)
				printf("p%d, ", i);
	}
	else {
		printf("Não houve deadlock. Os processos podem ser atendidos na seguinte ordem:");
		for(i = 0; i < N; i++)
			printf("p%d, ", ordem_atendimento[i]);
	}
	printf("\n");	
	return 0;
}