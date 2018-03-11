#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Definicoes de estruturas

//Definicão do endereço cliente
struct Endereco_cliente {
	
	char bairro[50];
	char cidade[50];
	char complemento[50];
	char estado[50];
	char logradouro[50];
	//Devido ao número de dígitos de um cep, usando long long int para não estourar.
	long long int cep;
	
};
typedef struct Endereco_cliente Endereco; // Redefinindo a struct em apenas Endereco

//Definição estrutura do cliente
struct Cliente {
	
	char name[100];
	long long int cnpj;
	int codigo;
	//Devido ao número de dígitos de um telefone, usando long long int para não estourar.
	long long int telefone;
	Endereco endereco;
		
};
typedef struct Cliente Cliente; // Idem acima

//Definição da conta
struct Conta_def {

	int agencia;
	int codigo;
	double saldo;
	
	Cliente cliente;
};
typedef struct Conta_def Conta; // Idem acima

//Definição enumerador Opção
enum Opcao{
	 DEBITO = 1,
	 CREDITO,
	};
typedef enum Opcao opcao;


//Definição estrutura transação
struct Transacao_def {
	
	char descricao[100];
	double valor;
	int data;
	
	Conta conta;
	opcao tipo;
};
typedef struct Transacao_def Transacao;


//Fim de definição de estruturas

//Arquivos que serão usados, declarando as variáveis.
//Seguindo o uso intuitivo pelo nome.
FILE* arqClientes;
FILE* arqContas;
FILE* arqTransacoes;

FILE* tempClientes;
FILE* tempContas;

//Variáveis auxiliares na leitura em algumas funções criadas
Cliente* clientes;
Cliente* ler;
Conta contas;
Conta* auxConta;

// variáveis globais que auxiliam nas funções criadas, seguindo intuição pelo nome
char nomeC[200];
int codigoC;
long long int cpfC;
int transferenciaAtiva = 0;
int ativa = 0;
int qtd = 10;
int contador = 0;
int agenciaTS;
int codigoTS;
int agenciaTD;
int codigoTD;

//Protótipos das funções CLIENTE
void cadastrarCliente(); //OK.
void listarCliente(); // Falta implementar ordem alfabética
void buscarCliente(char* nome, int codigo, long long int cpf, int modo); // OK.
void atualizarCliente(char* nome, int codigo, long long int cpf, int modoA); // OK.
void excluirCliente(char* nome, int codigo, long long int cpf, int modoE); // OK.
Cliente* retornaCliente(char* nome, int codigo, long long int cpf, int modo); //OK.

//Protótipos das funções CONTAS
void cadastrarConta();
void listarTodasContas();
void listarContas();
void realizarSaque();
void realizarDeposito();
void realizarTransferencia();
void retirarExtrato();


//Na main, é leitura básica do desejo do cliente e a chamada da função equivalente.
int main (){
	
	char nomeO[200];
	int codigoO;
	long long int cpfO;
	
	printf("Digite um comando para prosseguir: \n\n");
	printf("C - Gerenciar Clientes\n");
	printf("T - Gerenciar Contas\n");
	printf("S - Sair\n\n");

	char escolha;
	
	scanf(" %c", &escolha);
	getchar();
	
	if (escolha == 'C') {
		printf("============ Gerenciar Clientes ============\n\n");
		printf("Digite um comando para prosseguir:\n\n");
		printf("C - Cadastrar um cliente.\n");
		printf("L - Listar todos os clientes cadastrados.\n");
		printf("B - Buscar cliente ja cadastrados.\n");
		printf("A - Atualizar um cliente cadastrado.\n");
		printf("E - Excluir um cliente cadastrado.\n\n");
		
		scanf(" %c", &escolha);
		//getchar usado para capturar o caracter '\n' que sobra, evitando lixo no buffer (stdin)
		getchar();
		
		if (escolha == 'C') {
			
			cadastrarCliente();
			
		} else if (escolha == 'L') {
			
			listarCliente();
			
		} else if (escolha == 'B') {
			
			//É solicitado ao usuário que ele selecione que filtro utilizar
			//na busca de um cliente.
			printf("\nDigite a opcao pelo qual deseja buscar um cliente:\n");
			printf("1 - nome\n");
			printf("2 - codigo\n");
			printf("3 - cpf/cnpj\n\n");
			
			int escolhida;
			scanf(" %d", &escolhida);
			getchar();
			
			//Ao ser selecionada a opção de busca, apenas esta opção terá valor válido.
			//Os demais parâmetros da função são preenchidos com valores no sentido de anulá-los.
			if (escolhida == 1) {
				
				printf("\nDigite o nome do cliente: \n");
				gets(nomeO);
				buscarCliente(nomeO, -1, -1, 1);
				
			} else if (escolhida == 2) {
				
				printf("\nDigite o codigo do cliente: \n");
				scanf(" %d", &codigoO);
				buscarCliente("NULL", codigoO, -1, 2);
				
			} else if (escolhida == 3) {
				
				printf("\nDigite o cpf/cnpj do cliente: \n");
				scanf(" %lli", &cpfO);
				buscarCliente("NULL", -1, cpfO, 3);
				
			} else {
				
				printf("Opcao invalida.\n");
				printf("\n============ Retornando para o menu! ============\n\n");
				return main();
			}
			
		} else if (escolha == 'A') {
			
			printf("\nDigite a opcao pelo qual deseja buscar um cliente:\n");
			printf("1 - nome\n");
			printf("2 - codigo\n");
			printf("3 - cpf/cnpj\n\n");
			
			int escolhida;
			scanf(" %d", &escolhida);
			getchar();
						
			if (escolhida == 1) {
				
				printf("\nDigite o nome do cliente: \n");
				gets(nomeO);
				printf("\n");
				atualizarCliente(nomeO, -1, -1, 1);
				
			} else if (escolhida == 2) {
				
				printf("\nDigite o codigo do cliente: \n");
				scanf(" %d", &codigoO);
				printf("\n");
				atualizarCliente("NULL", codigoO, -1, 2);
				
			} else if (escolhida == 3) {
				
				printf("\nDigite o cpf/cnpj do cliente: \n");
				scanf(" %lli", &cpfO);
				printf("\n");
				atualizarCliente("NULL", -1, cpfO, 3);
				
			} else {
				
				printf("Opcao invalida.\n");
				printf("\n============ Retornando para o menu! ============\n\n");
				return main();
			}
			
			
		} else if (escolha == 'E') {
			
			printf("\nDigite a opcao pelo qual deseja buscar um cliente:\n");
			printf("1 - nome\n");
			printf("2 - codigo\n");
			printf("3 - cpf/cnpj\n\n");
			
			int escolhida;
			scanf(" %d", &escolhida);
			getchar();
			
			if (escolhida == 1) {
				
				printf("\nDigite o nome do cliente: \n");
				gets(nomeO);
				excluirCliente(nomeO, -1, -1, 1);
				
			} else if (escolhida == 2) {
				
				printf("\nDigite o codigo do cliente: \n");
				scanf(" %d", &codigoO);
				excluirCliente("NULL", codigoO, -1, 2);
				
			} else if (escolhida == 3) {
				
				printf("\nDigite o cpf/cnpj do cliente: \n");
				scanf(" %lli", &cpfO);
				excluirCliente("NULL", -1, cpfO, 3);
				
			} else {
				
				printf("Opcao invalida.\n");
				printf("\n============ Retornando para o menu! ============\n\n");
				return main();
			}

		} else {
			printf("Opcao invalida, tente novamente.\n\n");
			return main();
		}
	} else if (escolha == 'T') {
		
		printf("============ Gerenciar Contas ============\n\n");
		printf("Digite um comando para prosseguir:\n\n");
		printf("R - Listagem de todas as contas cadastradas.\n");
		printf("C - Cadastrar uma conta para um cliente.\n");
		printf("L - Listar todas as contas de um cliente.\n");
		printf("S - Realizar um saque em uma conta.\n");
		printf("D - Realizar um deposito em uma conta.\n");
		printf("T - Realizar uma transferencia entre contas.\n");
		printf("E - Exibir extrato de uma conta.\n\n");
		
		scanf(" %c", &escolha);
		getchar();
		
		if (escolha == 'R') {
			
			listarTodasContas();
		
		} else if (escolha == 'C') {
			
			cadastrarConta();
			
		} else if (escolha == 'L') {
			
			listarContas();
		
		} else if (escolha == 'S') {
			
			realizarSaque();
				
		} else if (escolha == 'D') {
			
			realizarDeposito();
			
		} else if (escolha == 'T') {
			
			realizarTransferencia();
			
		} else if (escolha == 'E') {
			
			retirarExtrato();
			
		} else {
			
			printf("Opcao invalida, tente novamente.\n");
			return main();
		}
			
	} else {
		
		printf("\nFinalizando o programa.\n");
		exit(0);
	}
	
	
	return 0;
}

// Implementando as funções | CLIENTE

//Cadastra um cliente,	
void cadastrarCliente(){
	
	//Alocação dinâmica de um cliente.
	//Nesse sentido, sempre que houver espaço em memória equivalente ao tamanho abaixo,
	//conseguiremos cadastrar clientes.
	clientes = (Cliente*) malloc (sizeof (Cliente) * 1);

	
	//Abertura de um arquivo em modo de escrever ao final.
	arqClientes = fopen("clientes.txt", "a");
	
	//Verificação se houve problema ao abrir o arquivo.
	if (!arqClientes) {
		printf("Falha ao abrir o arquive clientes\\.txt\n");
	} else {
		
		printf("Digite o seu nome: ");
		fgets(clientes[contador].name, 100, stdin);
		
		printf("Digite o seu CPF/CNPJ: ");
		scanf(" %lli", &clientes[contador].cnpj);
		
		printf("Digite o seu codigo: ");
		scanf(" %d", &clientes[contador].codigo);
		
		printf("Digite o seu telefone: ");
		scanf(" %lli", &clientes[contador].telefone);
		
		getchar();
		
		printf("Digite o logradouro: ");
		fgets(clientes[contador].endereco.logradouro, 100, stdin);
		
		printf("Digite o seu bairro: ");
		fgets(clientes[contador].endereco.bairro, 100, stdin);
		
		printf("Digite a sua cidade: ");
		fgets(clientes[contador].endereco.cidade, 100, stdin);
	
		printf("Digite o complemento: ");
		fgets(clientes[contador].endereco.complemento, 100, stdin);
		
		
		printf("Digite o seu estado: ");
		fgets(clientes[contador].endereco.estado, 100, stdin);
		
		printf("Digite o seu cep: ");
		scanf(" %lli", &clientes[contador].endereco.cep);
		
		//Utilizando função fprintf para "escrever" no arquivo de forma formatada.
		fprintf(arqClientes, "%s%s%s%s%s%s%lli %d %lli %lli\n",clientes[contador].name
			,clientes[contador].endereco.logradouro
			,clientes[contador].endereco.bairro
			,clientes[contador].endereco.cidade
			,clientes[contador].endereco.complemento
			,clientes[contador].endereco.estado
			,clientes[contador].cnpj
			,clientes[contador].codigo
			,clientes[contador].telefone
			,clientes[contador].endereco.cep
		);

	}
	//Fechando o arquivo aberto.
	fclose(arqClientes);
	printf("Arquivo fechado\n");
	//Liberando a memória alocada para clientes.
	free(clientes);
	printf("Cliente cadastrado com sucesso.\n");
	printf("\n============ Retornando para o menu! ============\n\n");
	return main();
}

//Lista os clientes presentes no arquivo Cliente.
//Documentações similares ditas acima, serão evitadas nas linhas abaixo
//para melhor legibilidade do código.

void listarCliente() {
	
	arqClientes = fopen("clientes.txt", "r");
	
	ler = (Cliente*) malloc(sizeof (Cliente) * 1);
	
	if (!arqClientes) {
		printf("Falha ao abrir o arquive clientes\.txt\n");
	} else {
		
		//String para armazenamento
		char buff[200];
		int contadorClientes = 1;
		
		//Enquanto ler uma linha do arquivo, e o mesmo for diferente de NULL
		//realizará os passos abaixo
		
		//Armazena na variável ler->name, uma linha com no máximo 100 caracteres, do arquivo 
		// representado por arqClientes
		while (fgets(ler->name, 100,arqClientes) != NULL) {
			
			printf("\n============ Cliente[%d] ============\n\n", contadorClientes);
			contadorClientes++;
			
			printf("Nome: %s\n", ler->name);
			
			fgets(ler->endereco.logradouro, 100,arqClientes);
			printf("Logradouro: %s\n", ler->endereco.logradouro);
			
			fgets(ler->endereco.bairro, 100,arqClientes);
			printf("Bairro: %s\n", ler->endereco.bairro);
			
			fgets(ler->endereco.cidade, 100,arqClientes);
			printf("Cidade: %s\n", ler->endereco.cidade);
			
			fgets(ler->endereco.complemento, 100,arqClientes);
			printf("Complemento[nominal]: %s\n", ler->endereco.complemento);
			
			fgets(ler->endereco.estado, 100,arqClientes);
			printf("Estado: %s\n", ler->endereco.estado);
			
			fgets(buff, 200, arqClientes);
			
			//Função sscanf formarta a leitura de uma dada string
			sscanf(buff, "%lli %d %lli %lli", &ler->cnpj
				,&ler->codigo
				,&ler->telefone
				,&ler->endereco.cep
			);
			
			printf ("CPF/CNPJ: %lli\n", ler->cnpj);
			printf ("\nCodigo: %d\n", ler->codigo);
			printf ("\nTelefone: %lli\n", ler->telefone);
			printf ("\nCEP: %lli\n\n", ler->endereco.cep);
			
		}
	}
	
	fclose(arqClientes);
	free(ler);
	
	printf("\n============ Retornando para o menu! ============\n\n");
	return main();
	
}

//Busca cliente baseado no modo que é passado como oarâmetro
// inteiro 1 para nome
// inteiro 2 para codigo
// inteiro 3 para cpf/cnpj
//Seja busca por nome, codigo ou cpf
void buscarCliente(char* nome, int codigo, long long int cpf, int modo) {
	
	arqClientes = fopen("clientes.txt", "r");
	
	ler = (Cliente*) malloc(sizeof (Cliente) * 1);
	
	if (!arqClientes) {
		//printf("Falha ao abrir o arquive clientes\.txt\n");
	} else {
		
		char buff[200];
		//Flag utilizada para sinalizar a presença ou não do cliente no arquivo
		int flag = 0;
		
		while (fgets(ler->name, 100,arqClientes) != NULL) {
			
			//Substituindo o \n que o fgets coloca na string, e isto atrapalha a comparacao com nome
			//Função strlen retorna o tamanho da string, isto, quantos caracteres ela possui
			//Sendo assim, parar retirar o '\n' que sobra, colocamos na última posição o caracter
			//nulo '\0', finalizando o fim da string
			int tam = strlen(ler->name);
			tam--;
			ler->name[tam] = '\0';
						
			fgets(ler->endereco.logradouro, 100,arqClientes);
			fgets(ler->endereco.bairro, 100,arqClientes);
			fgets(ler->endereco.cidade, 100,arqClientes);
			fgets(ler->endereco.complemento, 100,arqClientes);
			fgets(ler->endereco.estado, 100,arqClientes);
			fgets(buff, 200, arqClientes);
			
			sscanf(buff, "%lli %d %lli %lli", &ler->cnpj
				,&ler->codigo
				,&ler->telefone
				,&ler->endereco.cep
			);
			
			//Como explicado, o valor passado como modo, define a busca.
			//Ex: Se os nomes comparados forem iguais e o modo de busca ser por nome,
			//as informações do cliente são visualizadas, caso contrário não.

			if ( (strcmp(ler->name, nome) == 0) && modo == 1
					|| ler->codigo == codigo && modo == 2
					|| ler->cnpj == cpf && modo ==3) {
				flag = 1;
				printf("\nNome: %s\n\n", ler->name);
				printf("Logradouro: %s\n", ler->endereco.logradouro);
				printf("Bairro: %s\n", ler->endereco.bairro);
				printf("Cidade: %s\n", ler->endereco.cidade);
				printf("Complemento[nominal]: %s\n", ler->endereco.complemento);
				printf("Estado: %s\n", ler->endereco.estado);
				printf ("CPF/CNPJ: %lli\n", ler->cnpj);
				printf ("\nCodigo: %d\n", ler->codigo);
				printf ("\nTelefone: %lli\n", ler->telefone);
				printf ("\nCEP: %lli\n\n", ler->endereco.cep);
				//Ao identificar que o cliente está presente, já que entrou neste if
				//Evitamos processamento a mais, utilizando break para interromper o while
				break;
			}
		}
		
		//Se a flag não for verdadeira, isto é, não encontrar cliente, printar o mesmo.
		if (!flag) {
			printf("Cliente nao encontrado.\n");
		}
	}
	fclose(arqClientes);
	free(ler);
	
	printf("\n============ Retornando para o menu! ============\n\n");
	return main();
}

//Função adicional criada para auxiliar na atualização/exclusão de um cliente
//Identificando a posição/linha do cliente, fica fácil realizar operações sobre o cliente correspondente
//Seja para atualizar ou excluir
int buscarLinha(char* nome, int codigo, long long int cpf, int modoBu) {
	
	//Utilizando o modo de abertura "r", que significa apenas leitura
	arqClientes = fopen("clientes.txt", "r");
	
	ler = (Cliente*) malloc(sizeof (Cliente) * 1);
	
	int contadorLinhas = 0;
	
	if (!arqClientes) {
		printf("Falha ao abrir o arquive clientes\.txt\n");
	} else {
		
		char buff[200];
		
		while (fgets(ler->name, 100,arqClientes) != NULL) {
			
			contadorLinhas++;
			
			//Substituindo o \n que o fgets coloca na string, e isto atrapalha a comparacao com nome
			int tam = strlen(ler->name);
			tam--;
			ler->name[tam] = '\0';
						
			fgets(ler->endereco.logradouro, 100,arqClientes);
			
			fgets(ler->endereco.bairro, 100,arqClientes);
			
			fgets(ler->endereco.cidade, 100,arqClientes);
			
			fgets(ler->endereco.complemento, 100,arqClientes);
			
			fgets(ler->endereco.estado, 100,arqClientes);
			
			fgets(buff, 200, arqClientes);
			
			sscanf(buff, "%lli %d %lli %lli", &ler->cnpj
				,&ler->codigo
				,&ler->telefone
				,&ler->endereco.cep
			);
			
			//Condição já explicada em função anterior
			if ( (strcmp(ler->name, nome) == 0) && modoBu == 1
					|| ler->codigo == codigo && modoBu == 2
					|| ler->cnpj == cpf && modoBu == 3) {
				
				printf("Nome: %s\n", ler->name);
				printf("Logradouro: %s\n", ler->endereco.logradouro);
				printf("Bairro: %s\n", ler->endereco.bairro);
				printf("Cidade: %s\n", ler->endereco.cidade);
				printf("Complemento[nominal]: %s\n", ler->endereco.complemento);
				printf("Estado: %s\n", ler->endereco.estado);
				printf ("CPF/CNPJ: %lli\n", ler->cnpj);
				printf ("\nCodigo: %d\n", ler->codigo);
				printf ("\nTelefone: %lli\n", ler->telefone);
				printf ("\nCEP: %lli\n\n", ler->endereco.cep);
				
				fclose(arqClientes);
				free(ler);
				
				//Se encontrar o cliente, retorna a posição (1°, 2°, ...) que ele está presente no arquivo
				return contadorLinhas;
			}
		}
	}
	//Caso não encontra o cliente, retorna 0, sinalizando que não teve sucesso
	return 0;
}

//Realiza a exclusão de um cliente caso nome, codigo ou cpf/cnpj batam
void excluirCliente(char* nome, int codigo, long long int cpf, int modoE){
	
	//Busca o número do cliente no arquivo
	//buscarLinha retorna a posição númerica (1º, 2º) do cliente ou 0 caso não encontrado.
	int busca = buscarLinha(nome, codigo, cpf, modoE);
	int min;
	int contadorLinha = 1;
	int escolha;
	
	if (!busca) {	
		printf("Cliente nao encontrado.\n");
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	} else {
		
		printf("Tem certeza que quer excluir? Digite: 1 p/ Sim | 2 p/ Nao\n");
		scanf(" %d", &escolha);
		if (escolha == 2) {
			//Caso o cliente deseja de excluir, retorna para a função principal.
			printf("\n============ Retornando para o menu! ============\n\n");
			return main();
			
		} else {
			
			
			//O campo de cada cliente, são 7 linhas
			//Sendo assim, o cálculo abaixo é usado para identificar
			//a linha que inicia o cliente, isto é, armazena na variável min
			//Caso o cliente esteja seja o 1º, min = 1
			//Caso o cliente esteja em outra posição, calcula-se = (busca-1) * 7 + 1
			//Exemplo: Qual a linha do segundo cliente?
			//busca irá retonar 2, isto é, é o segundo cliente
			//min = (2-1) * 7 + 1 = 1 * 7 + 1 = 7 + 1 = 8, ou seja, o segundo cliente
			//se inicia na linha 8
			if (busca == 1){
				min = 1;
			} else {
				min = (busca-1) * 7 + 1;
			}
			
			arqClientes = fopen("clientes.txt", "r");
			
			//Arquivo temporário criado para ser o novo arquivo, após exclusão do cliente desejado.
			tempClientes = fopen("tempClientes.txt", "w");
			
			ler = (Cliente*) malloc(sizeof (Cliente) * 1);
			
			if (!arqClientes) {
				
				printf("Falha ao abrir o arquive clientes\.txt\n");
				
			} else if (!tempClientes) {
				
				printf("Falha ao abrir o arquive tempClientes\.txt\n");
				
			} else {
				
				char buff[200];
				
				while (fgets(ler->name, 100,arqClientes) != NULL) {
				
					fgets(ler->endereco.logradouro, 100,arqClientes);
					
					fgets(ler->endereco.bairro, 100,arqClientes);
					
					fgets(ler->endereco.cidade, 100,arqClientes);
					
					fgets(ler->endereco.complemento, 100,arqClientes);
					
					fgets(ler->endereco.estado, 100,arqClientes);
					
					fgets(buff, 200, arqClientes);
					sscanf(buff, "%lli %d %lli %lli", &ler->cnpj
						,&ler->codigo
						,&ler->telefone
						,&ler->endereco.cep
					);
					
					if (contadorLinha != min) {
						fprintf(tempClientes, "%s", ler->name);
						fprintf(tempClientes, "%s", ler->endereco.logradouro);
						fprintf(tempClientes, "%s", ler->endereco.bairro);
						fprintf(tempClientes, "%s", ler->endereco.cidade);
						fprintf(tempClientes, "%s", ler->endereco.complemento);
						fprintf(tempClientes, "%s", ler->endereco.estado);
						fprintf(tempClientes,"%lli %d %lli %lli\n", ler->cnpj
							,ler->codigo
							,ler->telefone
							,ler->endereco.cep
						);
						
					}
					//Incrementa 7, pois cada cliente, ocupa 7 linhas no arquivo
					contadorLinha += 7;
				}
		
			}
		}
		printf("Cliente excluido com sucesso.\n");
		fclose(tempClientes);
		fclose(arqClientes);
		
		//Deleta o arquivo clientes antigo
		remove("clientes.txt");
		//Renomeia o arquivo temporário no novo clientes
		rename("tempClientes.txt", "clientes.txt");
		
		free(ler);
		
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	}
}	

//Atualiza o cliente caso nome, codigo ou cpnj/cpf batam
//Explicação segue função anterior
void atualizarCliente(char* nome, int codigo, long long int cpf, int modoA) {
	
	int busca = buscarLinha(nome, codigo, cpf, modoA);
	int min;
	int contadorLinha = 1;
	
	if (!busca) {	
		printf("Cliente nao encontrado.\n");
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	} else {
		
		if (busca == 1){
			min = 1;
		} else {
			min = (busca-1) * 7 + 1;
		}
		
		arqClientes = fopen("clientes.txt", "r");
		
		tempClientes = fopen("tempClientes.txt", "w");
		
		ler = (Cliente*) malloc(sizeof (Cliente) * 1);
		
		if (!arqClientes) {
			
			printf("Falha ao abrir o arquive clientes\.txt\n");
			
		} else if (!tempClientes) {
			
			printf("Falha ao abrir o arquive tempClientes\.txt\n");
			
		} else {
			
			char buff[200];
			
			while (fgets(ler->name, 100,arqClientes) != NULL) {
			
				fgets(ler->endereco.logradouro, 100,arqClientes);
				
				fgets(ler->endereco.bairro, 100,arqClientes);
				
				fgets(ler->endereco.cidade, 100,arqClientes);
				
				fgets(ler->endereco.complemento, 100,arqClientes);
				
				fgets(ler->endereco.estado, 100,arqClientes);
				
				fgets(buff, 200, arqClientes);
				sscanf(buff, "%lli %d %lli %lli", &ler->cnpj
					,&ler->codigo
					,&ler->telefone
					,&ler->endereco.cep
				);
				
				if (contadorLinha != min) {
					fprintf(tempClientes, "%s", ler->name);
					fprintf(tempClientes, "%s", ler->endereco.logradouro);
					fprintf(tempClientes, "%s", ler->endereco.bairro);
					fprintf(tempClientes, "%s", ler->endereco.cidade);
					fprintf(tempClientes, "%s", ler->endereco.complemento);
					fprintf(tempClientes, "%s", ler->endereco.estado);
					fprintf(tempClientes,"%lli %d %lli %lli\n", ler->cnpj
						,ler->codigo
						,ler->telefone
						,ler->endereco.cep
					);
				} else {
					//Identificado o campo a ser atualizado,
					//os novos dados são solicitados e depois escritos no arquivo
					printf("Atualize todos os dados abaixo. Sem excecao.\n");
					
					printf("Digite o seu nome: ");
					fgets(ler->name, 100, stdin);
					
					printf("Digite o seu CPF/CNPJ: ");
					scanf(" %lli", &ler->cnpj);
					
					printf("Digite o seu codigo: ");
					scanf(" %d", &ler->codigo);
					
					printf("Digite o seu telefone: ");
					scanf(" %lli", &ler->telefone);
					getchar();
					
					printf("Digite o logradouro: ");
					fgets(ler->endereco.logradouro, 100, stdin);
					
					printf("Digite o seu bairro: ");
					fgets(ler->endereco.bairro, 100, stdin);
					
					printf("Digite a sua cidade: ");
					fgets(ler->endereco.cidade, 100, stdin);
					
					printf("Digite o complemento: ");
					fgets(ler->endereco.complemento, 100, stdin);
					
					printf("Digite o seu estado: ");
					fgets(ler->endereco.estado, 100, stdin);

					printf("Digite o seu cep: ");
					scanf(" %lli", &ler->endereco.cep);

					fprintf(tempClientes, "%s", ler->name);
					fprintf(tempClientes, "%s", ler->endereco.logradouro);
					fprintf(tempClientes, "%s", ler->endereco.bairro);
					fprintf(tempClientes, "%s", ler->endereco.cidade);
					fprintf(tempClientes, "%s", ler->endereco.complemento);
					fprintf(tempClientes, "%s", ler->endereco.estado);
					fprintf(tempClientes,"%lli %d %lli %lli\n", ler->cnpj
						,ler->codigo
						,ler->telefone
						,ler->endereco.cep
					);
				}
				contadorLinha += 7;
			}
		}
	}
	fclose(tempClientes);
	fclose(arqClientes);
	free(ler);
	
	//Mesma descrição da função anterior
	remove("clientes.txt");
	rename("tempClientes.txt", "clientes.txt");
	printf("\n============ Retornando para o menu! ============\n\n");
	return main();

}

// Implementando funções CONTA

//Cadastra um conta caso o cliente seja cadastrado
void cadastrarConta() {
	
	//variável auxiliar para apoio na função referente a dados de Contas
	//Será responsável por "segurar" informações sobre contas
	auxConta = (Conta*) malloc (sizeof (Conta) * 1);
				
	printf("\nDigite a opcao pelo qual deseja buscar um cliente:\n");
	printf("1 - nome\n");
	printf("2 - codigo\n");
	printf("3 - cpf/cnpj\n\n");
	
	int escolhida;
	scanf(" %d", &escolhida);
	getchar();
	

	//Variável auxiliar para apoio na função referete a dados de clientes
	//Será responsável por armazenar o cliente, caso encontrado
	Cliente* auxiliar = (Cliente*) malloc(sizeof (Cliente) * 1);
	
	if (escolhida == 1) {
		
		printf("\nDigite o nome do cliente: \n");
		gets(nomeC);
		//É buscado o cliente com os parâmetros escolhidos
		//No caso abaixo, os parâmetros válidos são nome e 1, que foi a opção escolhida do usuário
		auxiliar = retornaCliente(nomeC, -1, -1, 1);
		
	} else if (escolhida == 2) {
		
		printf("\nDigite o codigo do cliente: \n");
		scanf(" %d", &codigoC);
		auxiliar = retornaCliente("NULL", codigoC, -1, 2);
		
	} else if (escolhida == 3) {
		
		printf("\nDigite o cpf/cnpj do cliente: \n");
		scanf(" %lli", &cpfC);
		auxiliar = retornaCliente("NULL", -1, &cpfC, 3);
		
	} else {
		
		printf("Opcao invalida.\n");
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	}
	
	if (auxiliar != NULL) {
		
		//Se existir o cliente
		//Solicitado agencia e conta (codigo) para cadastro
		printf ("Digite o numero da agencia: \n");
		scanf(" %d", &auxConta->agencia);
		
		printf("Digite o codigo/conta da agencia: \n");
		scanf(" %d", &auxConta->codigo);
		
		//Saldo inicializado com 0.
		auxConta->saldo = 0.0;
		
		arqContas = fopen("contas.txt", "a");
	
		if (!arqContas) {
			printf("Problema ao abrir o arquivo.\n");
			exit(0);
		}
		
		//Cadastrando informações
		fprintf(arqContas, "%s\n", nomeC);
		fprintf(arqContas, "%d %d %d %d %lli\n", auxConta->agencia
			,auxConta->codigo
			,-1
			,auxiliar->codigo
			,auxiliar->cnpj
		);
		fprintf(arqContas, "%.2lf\n",auxConta->saldo);
		free(auxConta);
		fclose(arqContas);
		printf("Conta cadastrado com sucesso.\n");
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
		
	} else {
		
		printf("Cliente nao cadastrado.\n");
		free(auxConta);
		fclose(arqContas);
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	}
}

//Lista todas as contas presentes no arquivo
void listarTodasContas() {
	
	arqContas = fopen("contas.txt", "r");
	
	int contadorContas = 1;
	int linhaC;
	//Strings para uso na função
	char buff[100];
	char buff2[300];
	char buff3[100];
	
	auxConta = (Conta*) malloc(sizeof (Conta) * 1);
	
	if (!arqContas) {
		//printf("Problema na abertura do arquivo.\n");
	} else {
		
		while (fgets(buff, 300, arqContas) != NULL) {
			
			fgets(buff2, 300, arqContas);
			
			sscanf(buff2, "%d %d %d %d %lli", &auxConta->agencia
				,&auxConta->codigo
				,&linhaC
				,&auxConta->cliente.codigo
				,&auxConta->cliente.cnpj
			);
			
			fgets(buff3, 100, arqContas);
			sscanf(buff3, "%lf", &auxConta->saldo);
			
			printf("Conta %d.\n\n", contadorContas);
			contadorContas++;
			
			printf("Agencia: %d\n", auxConta->agencia);
			printf("Codigo agencia: %d\n", auxConta->codigo);
			printf("Saldo da conta: %.2lf\n", auxConta->saldo);
			printf("Nome: %s", buff);
			printf("Codigo: %d\n", auxConta->cliente.codigo);
			printf("CPF/CNPJ: %lli\n\n", auxConta->cliente.cnpj);
		}
	}
	
	free(auxConta);
	fclose(arqContas);
	printf("\n============ Retornando para o menu! ============\n\n");
	return main();
}

//Função auxiliar criada para verificar se a conta existe
//Retorna 1 se sim, e 0 se não			
int existeConta(int agencia, int codigo) {
	
	Conta* auxBuscaC = (Conta*) malloc(sizeof (Conta) * 1);
	
	int existeC = 0;
	int linhaC;
	
	arqContas = fopen("contas.txt", "r");

	char buff[100];
	char buff2[300];
	char buff3[100];
	
	if (!arqContas) {
		//printf("Problema na abertura do arquivo.\n");
	} else {
		
		while (fgets(buff, 300, arqContas) != NULL) {
			
			fgets(buff2, 300, arqContas);
			
			sscanf(buff2, "%d %d %d %d %lli", &auxBuscaC->agencia
				,&auxBuscaC->codigo
				,&linhaC
				,&auxBuscaC->cliente.codigo
				,&auxBuscaC->cliente.cnpj
			);
			
			fgets(buff3, 100, arqContas);
			sscanf(buff, "%lf", &auxBuscaC->saldo);
			
			//Se código(conta) for igual à agência, conta identificada
			if(auxBuscaC->codigo == codigo && auxBuscaC->agencia == agencia) {

				existeC = 1;
				break; 
			}
		}
		fclose(arqContas);
	}
	
	if (existeC) {
		free(auxBuscaC);
		return existeC;
	} else {
		printf("Conta nao encontrada.\n");
		free(auxBuscaC);
		return existeC;
	}
}

//Retorna a conta se encontrada ou NULL se não encontrada
Conta* buscarConta() {
	
	printf("Confirme/Digite o numero da agencia e o codigo/conta: \n");
	
	//Variável auxiliar criada para "segurar" informações referentes a Conta
	Conta* auxBuscaC = (Conta*) malloc(sizeof (Conta) * 1);
	
	int codigo;
	int agencia;
	int linhaC;
	int existeC = 0;
		
	scanf(" %d %d", &agencia, &codigo);
	getchar();
	
	arqContas = fopen("contas.txt", "r");

	int tamanho;
	char buff[100];
	char buff2[300];
	char buff3[100];
	
	if (!arqContas) {
		printf("Problema na abertura do arquivo.\n");
	} else {
		
		//Leitura das contas
		while (fgets(buff, 300, arqContas) != NULL) {
			
			fgets(buff2, 300, arqContas);
			sscanf(buff2, "%d %d %d %d %lli", &auxBuscaC->agencia
				,&auxBuscaC->codigo
				,&linhaC
				,&auxBuscaC->cliente.codigo
				,&auxBuscaC->cliente.cnpj
			);
			
			fgets(buff3, 100, arqContas);
			sscanf(buff3, "%lf", &auxBuscaC->saldo);

			//Se encontrada conta com codigo/conta e agencia idênticos ao pesquisados
			//O loop é finalizado e a conta será retornada
			if(auxBuscaC->codigo == codigo && auxBuscaC->agencia == agencia) {
				
				existeC = 1;
				printf("Agencia: %d\n", auxBuscaC->agencia);
				printf("Codigo agencia: %d\n", auxBuscaC->codigo);
				printf("Saldo da conta: %.2lf\n", auxBuscaC->saldo);
				printf("Nome: %s", buff);
				printf("Codigo: %d\n", auxBuscaC->cliente.codigo);
				printf("CPF/CNPJ: %lli\n", auxBuscaC->cliente.cnpj);
				break; 
			}
		}
		fclose(arqContas);
	}
	if (existeC) {
		return auxBuscaC;
	} else {
		printf("Conta nao encontrada.\n");
		free(auxBuscaC);
		fclose(arqContas);
		return NULL;
	}
}

//Lista as contas de um dado cliente
//Tem como entrada o nome, codigo e cpf/cnpj do cliente
void listarContas() {
				
	printf("\nDigite a opcao pelo qual deseja buscar um cliente:\n");
	printf("1 - nome\n");
	printf("2 - codigo\n");
	printf("3 - cpf/cnpj\n\n");
	
	int escolhida;
	scanf(" %d", &escolhida);
	getchar();
	
	Cliente* auxiliar = (Cliente*) malloc(sizeof (Cliente) * 1);
	char buff[100];
	char buff2[100];
	char buff3[100];
	int tamanho;
	int num;
	
	if (escolhida == 1) {
		
		printf("\nDigite o nome do cliente: \n");
		gets(nomeC);
		auxiliar = retornaCliente(nomeC, -1, -1, 1);
		
	} else if (escolhida == 2) {
		
		printf("\nDigite o codigo do cliente: \n");
		scanf(" %d", &codigoC);
		auxiliar = retornaCliente("NULL", codigoC, -1, 2);
		
	} else if (escolhida == 3) {
		
		printf("\nDigite o cpf/cnpj do cliente: \n");
		scanf(" %lli", &cpfC);
		auxiliar = retornaCliente("NULL", -1, &cpfC, 3);
		
	} else {
		
		printf("Opcao invalida.\n");
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	}
	
	if (auxiliar != NULL) {
		
		arqContas = fopen("contas.txt", "r");
		
		auxConta = (Conta*) malloc(sizeof (Conta) * 1);
	
		if (!arqContas) {
			printf("Problema na abertura do arquivo.\n");
		} else {
			
			while (fgets(buff, 300, arqContas) != NULL) {
				
				fgets(buff2, 300, arqContas);
				
				sscanf(buff2, "%d %d %d %d %lli ", &auxConta->agencia
					,&auxConta->codigo
					,&num
					,&auxConta->cliente.codigo
					,&auxConta->cliente.cnpj
				);
				
				fgets(buff3, 100, arqContas);
				sscanf(buff3, "%lf", &auxConta->saldo);
				
				//Tratamento para retirar o '\n' que o fgets deixa no buffer
				tamanho = strlen(buff);
				buff[--tamanho] = '\0';
				
				//Se nome, codigo e cpf bater, conta printada
				if( (strcmp(buff,auxiliar->name) == 0) && auxConta->cliente.codigo == auxiliar->codigo && auxConta->cliente.cnpj == auxiliar->cnpj) {
					
					printf("\nAgencia: %d\n", auxConta->agencia);
					printf("Codigo agencia: %d\n", auxConta->codigo);
					printf("Saldo da conta: %.2lf\n", auxConta->saldo);
					printf("Nome: %s\n", buff);
					printf("Codigo: %d\n", auxConta->cliente.codigo);
					printf("CPF/CNPJ: %lli\n", auxConta->cliente.cnpj);
					
				}
			}
			
			free(auxConta);
			free(auxiliar);
			fclose(arqContas);
			printf("\n============ Retornando para o menu! ============\n\n");
			return main();
			
		}
	} else {
		
		printf("Cliente nao cadastrado.\n");
		free(auxConta);
		free(auxiliar);
		fclose(arqContas);
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
		
	}
}	

//Realiza o saque em uma conta
//Dentro desta função, chamamos a função atualizarConta para fins intuitivos
void realizarSaque() {
	
	int agencia;
	int codigoAg;
	double saque;
	
	printf("\n============ SAQUE ============\n");
	
	printf("Digite o numero da agencia: \n");
	scanf(" %d", &agencia);
	
	
	printf("Digite o numero da conta/codigo: \n");
	scanf(" %d", &codigoAg);
	
	
	Conta* auxContaS = buscarConta();
	
	//Se não encontrar conta, retorna para a main
	if (auxContaS == NULL) {
		
		printf("Conta nao encontrada. Operacao cancelada.\n");
		free(auxContaS);
		return main();
		
	} else { //Senão, realiza o saque.
		
		Conta auxContaSaque = *auxContaS;
		
		free(auxContaS);
		
		//Solicitando valor do saque
		printf("Digite o valor do saque: \n");
		scanf(" %lf", &saque);
		getchar();
		
		//verificando se o saque é maior que o saldo da conta
		//Se sim, retorna para a main
		if (saque > auxContaSaque.saldo) {
			
			printf("Saldo insuficiente para realizar a operacao.\n");
			return main();
			
		} else { //Senão, realiza o saque e atualizar a conta referente
						
			auxContaSaque.saldo = auxContaSaque.saldo - saque;
			
			//Se att retornar 1 conta foi atualizada, senão falhou
			int att = atualizarConta(auxContaSaque);
			
			if (!att) {
				printf("Erro ao atualizar a conta.\n");
				return main();
			}
			
			//Toda transação deve ser registrada
			//Declarando as variáveis necessárias
			Transacao* transacaoSaque;
			
			transacaoSaque = (Transacao*) malloc (sizeof (Transacao) * 1);
			
			//Se não for uma transferência, ele pede uma descrição
			if (!transferenciaAtiva) {
				printf("Descricao da operacao: \n");
				gets(transacaoSaque->descricao);
			}
			
			//Digitando data da transação
			printf("Digite a data de hoje. ex:12112017\n");
			scanf(" %d", &transacaoSaque->data);
			
		
			transacaoSaque->valor = saque;
		
			transacaoSaque->tipo = DEBITO;
			
			//Abrindo arquivo para registrar
			arqTransacoes = fopen("transacoes.txt", "a");
			
			fprintf(arqTransacoes, "%d %.2lf %d %d %d\n", transacaoSaque->data
				,transacaoSaque->valor
				,transacaoSaque->tipo
				,agencia
				,codigoAg
			);

			//Se não for uma transferência, adiciona a descrição da transação
			if (!transferenciaAtiva) {
				fprintf(arqTransacoes, "%s\n", transacaoSaque->descricao);
			} else {
				//Se for transferência, adiciona uma string informando
				//de qual conta está sendo realizado o saque
				fprintf(arqTransacoes, "Transferencia de conta: {%d}-{%d}\n", agenciaTS
					, codigoTS
				);
				//Seta transferência para 0, tornando a inativa
				transferenciaAtiva = 0;
			}
			
			fclose(arqTransacoes);
			free(transacaoSaque);
			
			//Cálculo para notas gastas na transação
			long int n,qu;

			qu=0;
			n = saque;
			
			printf("\nForam liberadas as seguintes notas na operacao: \n\n");
			
			qu=n/100;
			n=n%100;
			printf("%li nota(s) de R$ 100,00\n",qu);
			qu=n/50;
			n=n%50;
			printf("%li nota(s) de R$ 50,00\n",qu);
			qu=n/20;
			n=n%20;
			printf("%li nota(s) de R$ 20,00\n",qu);
			qu=n/10;
			n=n%10;
			printf("%li nota(s) de R$ 10,00\n",qu);
			qu=n/5;
			n=n%5;
			printf("%li nota(s) de R$ 5,00\n",qu);
			qu=n/2;
			n=n%2;
			printf("%li nota(s) de R$ 2,00\n",qu);
			//qu=n;
			//printf("%li nota(s) de R$ 1,00\n",qu);
			
			if (!transferenciaAtiva) {
				printf("\n============ Retornando para o menu! ============\n\n");
				return main();
			}
		}
	}
	
}

//Função similar ao realizar Saque
//Documentação evitada para melhor legibilidade do código
//Dúvida, retornar função anterior, lógica análoga
void realizarDeposito() {
	
	int agencia;
	int codigoAg;
	double deposito;
	
	printf("\n============ DEPOSITO ============\n");
	
	printf("Digite o numero da agencia: \n");
	scanf(" %d", &agencia);
	
	printf("Digite o numero da conta/codigo: \n");
	scanf(" %d", &codigoAg);
	
	Conta* auxContaS = buscarConta();
	
	if (auxContaS == NULL) {
		
		printf("Conta nao encontrada. Operacao cancelada.\n");
		free(auxContaS);
		return main();
		
	} else {
		
		Conta auxContaDeposito = *auxContaS;
		
		printf("Digite o valor do deposito: \n");
		scanf(" %lf", &deposito);
		getchar();
					
		auxContaDeposito.saldo = auxContaDeposito.saldo + deposito;
		
		int att = atualizarConta(auxContaDeposito);
			
		if (!att) {
			printf("Erro ao atualizar a conta.\n");
			return main();
		}
		
		Transacao* transacaoDeposito;
		
		transacaoDeposito = (Transacao*) malloc (sizeof (Transacao) * 1);
		
		if (!transferenciaAtiva) {
			printf("Descricao da operacao: \n");
			gets(transacaoDeposito->descricao);
		}
		
		printf("Digite a data de hoje. ex:12112017\n");
		scanf(" %d", &transacaoDeposito->data);
	
		
		transacaoDeposito->valor = deposito;
		transacaoDeposito->tipo = CREDITO;
		
		arqTransacoes = fopen("transacoes.txt", "a");
		
		fprintf(arqTransacoes, "%d %.2lf %d %d %d\n", transacaoDeposito->data
			,transacaoDeposito->valor
			,transacaoDeposito->tipo
			,agencia
			,codigoAg
		);
		
		if (!transferenciaAtiva) {
			fprintf(arqTransacoes, "%s\n", transacaoDeposito->descricao);
		} else {
			fprintf(arqTransacoes, "Transferencia para conta: {%d}-{%d}\n", agenciaTD
				, codigoTD
			);
			transferenciaAtiva = 0;
		}
		
		fclose(arqTransacoes);
		free(transacaoDeposito);
		free(auxContaS);
		
		long int n,qu;

		qu=0;
		n = deposito;
		
		printf("\nForam liberadas as seguintes notas na operacao: \n\n");
		
		qu=n/100;
		n=n%100;
		printf("%li nota(s) de R$ 100,00\n",qu);
		qu=n/50;
		n=n%50;
		printf("%li nota(s) de R$ 50,00\n",qu);
		qu=n/20;
		n=n%20;
		printf("%li nota(s) de R$ 20,00\n",qu);
		qu=n/10;
		n=n%10;
		printf("%li nota(s) de R$ 10,00\n",qu);
		qu=n/5;
		n=n%5;
		printf("%li nota(s) de R$ 5,00\n",qu);
		qu=n/2;
		n=n%2;
		printf("%li nota(s) de R$ 2,00\n",qu);
		//qu=n;
		//printf("%li nota(s) de R$ 1,00\n",qu);
		if (!transferenciaAtiva) {
				printf("\n============ Retornando para o menu! ============\n\n");
				return main();
		}			
	}
}

//Realiza a transferência entre duas contas
//Realizando o saque em uma e depósito na outra
//Utiliza as funções realizarSaque e a realizarDepósito deste programa
void realizarTransferencia () {
	
	int agencia;
	int codigo;
	
	printf("============ Dados para saque ============\n\n");
	
	printf("Digite o numero da agencia: \n");
	scanf(" %d", &agencia);
	
	printf("Digite o numero da conta/codigo: \n");
	scanf(" %d", &codigo);
	
	//Variáveis globais utilizadas nas funções realizarSaque e a realizarDepósito
	//Para servir como parâmetro ao definir as contas de saque e de depósito
	//ex: agenciaTS = Agencia transferência Saque
	agenciaTS = agencia;
	codigoTS = codigo;
	
	//é retornado se a conta existe ou não
	int procuraSaque = existeConta(agencia, codigo);
	
	if (!procuraSaque) {
		printf("Conta nao encontrada.\n");
		return main();
	} 
	
	printf("============ Dados para deposito ============\n\n");
	
	printf("Digite o numero da agencia: \n");
	scanf(" %d", &agencia);
	
	printf("Digite o numero da conta/codigo: \n");
	scanf(" %d", &codigo);
	
	
	//Variáveis globais utilizadas nas funções realizarSaque e a realizarDepósito
	//Para servir como parâmetro ao definir as contas de saque e de depósito
	//ex: agenciaTD = Agencia transferência Depósito
	agenciaTD = agencia;
	codigoTD = codigo;
	
	//é retornado se a conta existe ou não
	int procuraDeposito = existeConta(agencia, codigo);
	
	if (!procuraDeposito) {
		
		printf("Conta nao encontrada.\n");
		exit(0);
		
	}
	
	//ativa transferência
	transferenciaAtiva = 1;
	realizarSaque();
	//Na função saque, a transferência é desativada
	//Sendo assim, é necessário reativá-la na linha abaixo
	//Foi a medida criada para definir quando é ou não transferência
	transferenciaAtiva = 1;
	realizarDeposito();
	
}

//Atualiza a conta que é passada na função
int atualizarConta(Conta contaAtualizar) {
	
	//Variável auxiliar para "segurar" informações das contas no arquivo
	//para fins de comparação
	Conta auxAtualizar;
	
	int linhaC;
	int existeC = 0;
	
	arqContas = fopen("contas.txt", "r+");
	
	char buff[100];
	char buff2[300];
	char buff3[100];
	
	if (!arqContas) {
		sprintf("Problema na abertura do arquivo.\n");
	} else {
		
		while (fgets(buff, 300, arqContas) != NULL) {
			
			fgets(buff2, 300, arqContas);
			
			sscanf(buff2, "%d %d %d %d %lli ", &auxAtualizar.agencia
				,&auxAtualizar.codigo
				,&linhaC
				,&auxAtualizar.cliente.codigo
				,&auxAtualizar.cliente.cnpj
			);
			
			//Se cpf/cpnj igual e codigo do cliente iguais, conta a ser atualizada foi encontrada
			if(auxAtualizar.cliente.cnpj == contaAtualizar.cliente.cnpj
				&& auxAtualizar.cliente.codigo == contaAtualizar.cliente.codigo) {
				
				existeC = 1;
				//Para escrita no modo r+, é necessário usar a função fseek.
				//A função abaixo, simplesmente faz o reposicionamento do ponteiro do arquivo
				//para o ponto atual de leitura
				fseek(arqContas, 0, SEEK_CUR);
				fprintf(arqContas, "%.2lf\n", contaAtualizar.saldo);
				break;
				
			} else {
				
				fgets(buff3, 100, arqContas);
				sscanf(buff3, "%lf", &auxAtualizar.saldo);
			}
		}
		fclose(arqContas);
	}
	
	if (existeC) {
		printf("Conta atualizada.\n");
		return existeC;
	} else {
		printf("Conta nao encontrada.\n");
		return existeC;
	}
}

//retira o extrato de transações de um cliente
//A lógica foi explicada em funções anteriores,
//sendo assim, evitada para melhor legibilidade
void retirarExtrato() {
	
	printf("Digite a agencia e a conta/codigo do cliente desejado: \n");
	
	int agenciaE;
	long long int contaE;
	
	scanf(" %d %lli", &agenciaE, &contaE);
	getchar();
	
	arqContas = fopen("contas.txt", "r");

	//int tamanho;
	int linhaC;
	int agenciaEx;
	int codigoEx;
	int existeC = 0;
	char buff[100];
	char buff2[300];
	char buff3[100];
	
	auxConta = (Conta*) malloc(sizeof (Conta) * 1);
	
	if (!arqContas) {
		//printf("Problema na abertura do arquivo.\n");
	} else {
		
		while (fgets(buff, 300, arqContas) != NULL) {
			
			fgets(buff2, 300, arqContas);
			
			sscanf(buff2, "%d %d %d %d %lli ", &auxConta->agencia
				,&auxConta->codigo
				,&linhaC
				,&auxConta->cliente.codigo
				,&auxConta->cliente.cnpj
			);
			
			fgets(buff3, 100, arqContas);
			sscanf(buff3, "%lf", &auxConta->saldo);
			
			//Se encontrada agência e codigo idênticos ao passado
			//é printado as informações da conta e notado que existe conta

			if(auxConta->agencia == agenciaE && auxConta->codigo == contaE) {
				
				printf("\nAgencia: %d\n", auxConta->agencia);
				printf("Codigo agencia: %d\n", auxConta->codigo);
				printf("Saldo da conta: %.2lf\n", auxConta->saldo);
				printf("Nome: %s", buff);
				printf("Codigo: %d\n", auxConta->cliente.codigo);
				printf("CPF/CNPJ: %lli\n", auxConta->cliente.cnpj);
				existeC = 1;
			}
		}
		fclose(arqContas);
		
		Transacao* transacaoExtrato;
		
		//Se a conta existe, verificado pela variável existeC, 1 = Existe, 0 = não existe
		//É printado todas as transações correspondentes a conta e agencia passada
		if (existeC) {
			
			arqTransacoes = fopen("transacoes.txt", "r");
			
			transacaoExtrato = (Transacao*) malloc (sizeof (Transacao) * 1);
			
			while (fgets(buff, 100, arqTransacoes) != NULL ) {
				
				sscanf(buff, "%d %lf %d %d %d", &transacaoExtrato->data
					,&transacaoExtrato->valor
					,&transacaoExtrato->tipo
					,&agenciaEx
					,&codigoEx
				);
				
				fgets(buff2, 100, arqTransacoes);
				
				if (agenciaEx == auxConta->agencia && codigoEx == auxConta->codigo) {
					printf("\nData: %d\n", transacaoExtrato->data);
					printf("\nValor: %.2lf\n", transacaoExtrato->valor);
					printf("\nTipo: %d\n", transacaoExtrato->tipo);
					printf("\nDescricao: %s\n", buff2);
				}
				
			}
			
		}
		free(transacaoExtrato);
		fclose(arqTransacoes);
		free(auxConta);
		printf("\n============ Retornando para o menu! ============\n\n");
		return main();
	}
}

//Função auxiliar criada para auxílio no gerenciamento de conta
//Retorna o cliente caso encontrado ou retorna NULL como sinal de cliente não encontrado.
Cliente* retornaCliente(char* nome, int codigo, long long int cpf, int modo) {
	
	Cliente* auxBuscaCliente = (Cliente*) malloc(sizeof (Cliente) * 1);
	int flag = 0;
	
	arqClientes = fopen("clientes.txt", "r");
	
	if (!arqClientes) {
		printf("Falha ao abrir o arquive clientes\.txt\n");
	} else {
		
		char buff[200];
		
		while (fgets(auxBuscaCliente->name, 100,arqClientes) != NULL) {
			
			int tam = strlen(auxBuscaCliente->name);
			tam--;
			auxBuscaCliente->name[tam] = '\0';
						
			fgets(auxBuscaCliente->endereco.logradouro, 100,arqClientes);
			fgets(auxBuscaCliente->endereco.bairro, 100,arqClientes);
			fgets(auxBuscaCliente->endereco.cidade, 100,arqClientes);
			fgets(auxBuscaCliente->endereco.complemento, 100,arqClientes);
			fgets(auxBuscaCliente->endereco.estado, 100,arqClientes);
			fgets(buff, 200, arqClientes);
			
			sscanf(buff, "%lli %d %lli %lli", &auxBuscaCliente->cnpj
				,&auxBuscaCliente->codigo
				,&auxBuscaCliente->telefone
				,&auxBuscaCliente->endereco.cep
			);
			
						
			if ( (strcmp(auxBuscaCliente->name, nome) == 0) && modo == 1
					|| (auxBuscaCliente->codigo == codigo) && modo == 2
					|| (auxBuscaCliente->cnpj == cpf) && modo ==3) {
						
				flag = 1;
				printf("\nNome: %s\n\n", auxBuscaCliente->name);
				printf("Logradouro: %s\n", auxBuscaCliente->endereco.logradouro);
				printf("Bairro: %s\n", auxBuscaCliente->endereco.bairro);
				printf("Cidade: %s\n", auxBuscaCliente->endereco.cidade);
				printf("Complemento[nominal]: %s\n", auxBuscaCliente->endereco.complemento);
				printf("Estado: %s\n", auxBuscaCliente->endereco.estado);
				printf ("CPF/CNPJ: %lli\n", auxBuscaCliente->cnpj);
				printf ("\nCodigo: %d\n", auxBuscaCliente->codigo);
				printf ("\nTelefone: %lli\n", auxBuscaCliente->telefone);
				printf ("\nCEP: %lli\n\n", auxBuscaCliente->endereco.cep);
				break;
			}
		}
	
	fclose(arqClientes);
	}
	if (flag) {
		return auxBuscaCliente;
	} else {
		free(auxBuscaCliente);
		return NULL;
	}
}
	
