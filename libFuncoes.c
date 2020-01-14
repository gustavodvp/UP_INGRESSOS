/*
	--- Arquivo de funcoes para execucao do programa ---

*/

//  bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <locale.h>



// definindo tamanhos das strings e numero de op√ß√µes -----------------------------------

#define TAM 25
#define TAM_LOCAL 35
#define OPCOES 7
#define OP_VENDA 3





// Definicao dos nomes dos arquivos--------------------------------------------------------------
#define ARQ_ATR "atracao.dat"
#define ARQ_ATR_TMP "atracao.tmp"
#define ARQ_ATR_CSV "atracao.csv"
#define ARQ_CL "cliente.dat"
#define ARQ_CL_TMP "cliente.tmp"
#define ARQ_CL_CSV "cliente.csv"
#define ARQ_EVT "evento.dat"
#define ARQ_EVT_TMP "evento.tmp"
#define ARQ_EVT_CSV "evento.csv"
#define ARQ_LC "local.dat"
#define ARQ_LC_TMP "local.tmp"
#define ARQ_LC_CSV "local.csv"
#define ARQ_VD "venda.dat"
#define ARQ_VD_TMP "venda.tmp"
#define ARQ_VD_CSV "venda.txt"
#define ARQ_LG "login.dat"
#define ARQ_LG_TMP "login.tmp"
#define ARQ_LG_CSV "login.csv"



// Definindo structs -----------------------------------------------------

struct tAtracao {
	//Atributos
	int codigo;
	char nome[TAM];
	char tipo[TAM];
	//Marcadores
	char lixo; // *=deletado; espaco=OK
	//---------- Alterei -------------
	int escolhido; // Controle para a chave estrangeira no STRUCT TEVENTO -  Adicionar escolhido = 0 na funcao incluir
};

struct tNasc{
	int dia;
	int mes;
	int ano;
};

// Definindo entidade Cliente
struct tCliente {
	//Atributos
	int codigo;
	char nome[TAM];
	char cpf[TAM];
	struct tNasc dataNascimento;
	char genero;
	char email[TAM];
	//Marcadores
	char lixo; // *=deletado; espaco=OK
};

struct tData{
	int dia;
	int mes;
	int ano;
};
// Definindo entidade Evento
struct tEvento {
	//Atributos
	int codigo;
	char nome[TAM];
	struct tData data;
	char hora[5];
	float valor;
	int classInd;
	int idLocal;
	int idAtracao[TAM];
	// ******************* ADICIONAR ****************
	// Para manter o controle da lista de atracoes escolhidas
	// Controle	
	int qtdAtracoes;
	//Marcadores
	char lixo; // *=deletado; espaco=OK
};

struct tLocal {
	//Atributos
	int codigo;
	char nome[TAM];
	int capacidade;
	char endereco[TAM_LOCAL];
	//Marcadores
	char lixo; // *=deletado; espaco=OK
};


struct tVenda {
	int codigo;
	char cpfCliente[TAM];
	int idEvento;
	int quantidade;
	float total;
};

struct tLogin {
	//Atributos
	int codigo;
	char usuario[TAM];
	char senha[TAM];
	int nivel;
	//Marcadores
	char lixo; // *=deletado; espaco=OK
};






// Prototipos----------------------------------------------------------------------
// - atracao - 
void exibeMenuAtracao(void);
void exibeAtracao(int);
void mensagemContinuarAtracao(void);
void mensagemErroAtracao();
char mensagemExcluirAtracao(void);
int incrementaCodigoAtracao(void);
int recebeCodigoAtracao(void);
void recebeDadosAtracao(struct tAtracao*);
void cadastraAtracao(struct tAtracao);
void listaAtracao(void);
void consultaAtracao(void);
void alteraAtracao(void);
void excluiTempAtracao(void);
void excluiPermanenteAtracao();
void exportaExcelAtracao(void);
void mostrarDadosAtracao(struct tAtracao);
int validaOpcaoMenuAtracao(void);
void leValidaStringAtracao (char*);
// - cliente -

void exibeMenuCliente(void);
void exibeCliente(int);
void mensagemContinuarCliente(void);
void mensagemErroCliente();
char mensagemExcluirCliente(void);
int incrementaCodigoCliente(void);
int recebeCodigoCliente(void);
void recebeDadosCliente(struct tCliente*);
void cadastraCliente(struct tCliente);
void listaCliente(void);
void consultaCliente(void);
void alteraCliente(void);
void excluiTempCliente(void);
void excluiPermanenteCliente();
void exportaExcelCliente(void);
void mostrarDadosCliente(struct tCliente);
int validaOpcaoMenuCliente(void);
void leValidaStringCliente (char*);
// - evento - 

void exibeMenuEvento(void);
void exibeEvento(int);
void mensagemContinuarEvento(void);
void mensagemErroEvento();
char mensagemExcluirEvento(void);
int incrementaCodigoEvento(void);
int recebeCodigoEvento(void);
void recebeDadosEvento(struct tEvento*);
void cadastraEvento(struct tEvento);
void listaEvento(void);
void consultaEvento(void);
void alteraEvento(void);
void excluiTempEvento(void);
void excluiPermanenteEvento();
void exportaExcelEvento(void);
void mostrarDadosEvento(struct tEvento);
int validaOpcaoMenuEvento(void);
void leValidaStringEvento (char*);
// ******************* ADICIONAR ****************
// Adicionados nas ultimas linhas
void listaIdLocal(void); // Lista os Locais disponiveis, senao tiver chamar√° a funcao incluir local
void leValidaIdLocal(int*); // Valida comparando com os codigos dos locais
int contaIdAtracao(void); // Necessario para fazer o teste logico, caso os IDs sejam <=0, o o usuario nao poder√° adicionar mais 
void listaIdAtracao(void); // Lista as Atracoes disponiveis que nao foram escolhidas, senao tiver chamar√° a funcao incluir local
void leValidaIdAtracao(int*[]); // Valida comparando com os codigos das atracoes
void resetaEscolhidaAtracao(void); // Reseta as atracoes escolhidas para serem listadas nos cadastros de eventos posteriores

// -----------------------------------------------------------------------------------------
// ------------------------------------ local ---------------------------------

void exibeMenuLocal(void);
void exibeLocal(int);
void mensagemContinuarLocal(void);
void mensagemErroLocal();
char mensagemExcluirLocal(void);
int incrementaCodigoLocal(void);
int recebeCodigoLocal(void);
void recebeDadosLocal(struct tLocal*);
void cadastraLocal(struct tLocal);
void listaLocal(void);
void consultaLocal(void);
void alteraLocal(void);
void excluiTempLocal(void);
void excluiPermanenteLocal();
void exportaExcelLocal(void);
void mostrarDadosLocal(struct tLocal);
int validaOpcaoMenuLocal(void);
void leValidaStringLocal (char*);

// ------ venda ----------

void exibeMenuVenda(void);
void exibeVenda(int);
void mensagemContinuarVenda(void);
void mensagemErroVenda();
char mensagemExcluirVenda(void);
int incrementaCodigoVenda(void);
void recebeCpfClienteVenda(char[]);
void recebeDadosVenda(struct tVenda*);
void cadastraVenda(struct tVenda);
void listaVenda(void);
void consultaVenda(void);
void gerarIngressoVenda(void);
void mostrarDadosVenda(struct tVenda);
int validaOpcaoMenuVenda(void);
void leValidaStringVenda (char*);
void leValidaCpfCliente(char*[]);
void listaIdEvento(void);
void leValidaIdEvento(int*);
float calculaTotal(int, int);
void eventoVenda(int idEvento);
void clienteVenda(char[]);

//-------------------------------------------------------------------------------

void exibeMenuLogin(void);
void exibeLogin(int);
void mensagemContinuarLogin(void);
void mensagemErroLogin();
char mensagemExcluirLogin(void);
int incrementaCodigoLogin(void);
int recebeCodigoLogin(void);
void recebeDadosLogin(struct tLogin*);
void cadastraLogin(struct tLogin);
void listaLogin(void);
void consultaLogin(void);
void alteraLogin(void);
void excluiTempLogin(void);
void excluiPermanenteLogin();
void exportaExcelLogin(void);
void mostrarDadosLogin(struct tLogin);
int validaOpcaoMenuLogin(void);
void leValidaStringLogin (char*[]);
void getsSenhaWallisson(char*[]);
int logar(void);





int principalAtracao(void){
	setlocale(LC_ALL, "Portuguese");
	struct tAtracao atracao;
	int codigo;
	int opcao;
	do{
		exibeMenuAtracao();
		opcao = validaOpcaoMenuAtracao();		
		switch(opcao){
			case 1:
				printf("Cadastro de AtraÁıes\n\n");
				atracao.codigo = incrementaCodigoAtracao();
				recebeDadosAtracao(&atracao);
				cadastraAtracao(atracao);
				break;	
			case 2:
				printf("Lista de AtraÁıes\n\n");
				listaAtracao();
				break;		
			case 3:
				printf("Consulta de AtraÁıes\n");
				consultaAtracao();
				break;
			case 4:
				printf("AlteraÁ„o de AtraÁıes\n");
				alteraAtracao();
				break;
			case 5:
				printf("Exclus„o temporaria de atraÁıes\n");
				excluiTempAtracao();
				break;	
			case 6:
				printf("Exclus„o permanente de atraÁıes\n");
				excluiPermanenteAtracao();
				break;
			case 7:
				printf("Exportar Tabela de Atracoes para o Excel\n");
				exportaExcelAtracao();
				break;
		}		
	} while (opcao!=0);
	return 0;
}

// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Atracao
void exibeMenuAtracao(void){
	printf("\n..:: ATRA«√O ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERA«√O \n");
	printf("  5 - EXCLUS√O TEMPORARIA\n");
	printf("  6 - EXCLUS√O PERMANENTE\n");
	printf("  7 - EXPORTAR DADOS PARA EXCEL\n");
	printf("  0 - Voltar\n"); 
	printf("\n\n  ESCOLHA UMA OP«√O: ");	
}
void exibeAtracao(int cod){
	printf("\n>> ATRACAO - COD: %d <<\n", cod);
}
void mensagemContinuarAtracao(void){
	printf("\n\nDigite algo para continuar...", ARQ_ATR);
	getch();
	system("cls");
}
void mensagemErroAtracao(){
	printf("Erro na abertura do arquivo %s \n", ARQ_ATR);
	getch();
}
char mensagemExcluirAtracao(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR? *** ");
	do{
		printf("\n    Digite [S] - SIM ou [N] - NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoAtracao(void){
	int cod = 1;
	struct tAtracao atracao;
	FILE *arq_atracao;
	arq_atracao = fopen(ARQ_ATR, "rb");
	if (arq_atracao == NULL)	
		return cod;		
	while(fread(&atracao, sizeof(atracao), 1, arq_atracao))	
		cod = atracao.codigo;			
	fclose(arq_atracao);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoAtracao(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosAtracao(struct tAtracao *atr){
	exibeAtracao(atr->codigo);
	printf("\n>> Nome: ");
	leValidaStringAtracao (&atr->nome);
	printf("\n>> Tipo: ");
	leValidaStringAtracao (&atr->tipo);
}
// ------------------ Cadastrar ------------------
void cadastraAtracao(struct tAtracao atr){
	FILE *arq_atracao;
	
	arq_atracao = fopen(ARQ_ATR, "ab");
	
	if (arq_atracao == NULL)	
		mensagemErroAtracao();
	else {
		atr.lixo = ' ';
		atr.escolhido = 0;
		fwrite(&atr, sizeof(atr), 1, arq_atracao);
	}
	mensagemContinuarAtracao();	
	fclose(arq_atracao);
}
// ------------------ Listar ------------------
void listaAtracao(void){
	struct tAtracao atracao;
	FILE *arq_atracao;	
	arq_atracao = fopen(ARQ_ATR, "rb");	
	if (arq_atracao == NULL)	
		mensagemErroAtracao();
	else {	
		printf(" |COD  |NOME            |TIPO          |\n\n");
		while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
			if(atracao.lixo != '*')
				printf("%c|%5d|%16s|%14s|\n\n", atracao.lixo, atracao.codigo, atracao.nome, atracao.tipo);	
		mensagemContinuarAtracao();	
	}		
	fclose(arq_atracao);
}
// ------------------ Consultar ------------------
void consultaAtracao(void){
	int cod, achei = 0;
	struct tAtracao atracao;
	FILE *arq_atracao;		
	arq_atracao = fopen(ARQ_ATR, "rb");	
	if (arq_atracao == NULL)	
		mensagemErroAtracao();
	else {	
		cod = recebeCodigoAtracao();
		while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
			if (cod == atracao.codigo && atracao.lixo != '*'){
				mostrarDadosAtracao(atracao);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Atracao nao encontrada.\n");
		mensagemContinuarAtracao();
	}		
	fclose(arq_atracao);
}
// ------------------ Alterar ------------------
void alteraAtracao(void){
	int cod, achei = 0;
	struct tAtracao atracao;
	FILE *arq_atracao;		
	arq_atracao = fopen(ARQ_ATR, "r+b");	
	if (arq_atracao == NULL)	
		mensagemErroAtracao();
	else {	
		cod = recebeCodigoAtracao();
		while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
			if (cod == atracao.codigo && atracao.lixo != '*'){
				mostrarDadosAtracao(atracao);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosAtracao(&atracao);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_atracao, -sizeof(atracao), SEEK_CUR); 
				fwrite(&atracao, sizeof(atracao), 1, arq_atracao);			
				fseek(arq_atracao, 0, SEEK_CUR); // fixar ponteiro
			}
		if (!achei)
			printf("\nErro: Atracao nao encontrada.\n");
		mensagemContinuarAtracao();
	}		
	fclose(arq_atracao);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempAtracao(void){
	int cod, achei = 0;
	struct tAtracao atracao;
	FILE *arq_atracao;		
	arq_atracao = fopen(ARQ_ATR, "r+b");	
	if (arq_atracao == NULL)	
		mensagemErroAtracao();
	else {	
		cod = recebeCodigoAtracao();
		while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
			if (cod == atracao.codigo && atracao.lixo != '*'){
				mostrarDadosAtracao(atracao);
				achei = 1;
				if (mensagemExcluirAtracao()=='S'){
					atracao.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_atracao, -sizeof(atracao), SEEK_CUR); 
					fwrite(&atracao, sizeof(atracao), 1, arq_atracao);			
					fseek(arq_atracao, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Atracao nao encontrada.\n");
		mensagemContinuarAtracao();
	}		
	fclose(arq_atracao);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteAtracao(){
	struct tAtracao atracao;
	FILE *arq_atracao_novo;
	FILE *arq_atracao_velho;	
	arq_atracao_velho = fopen(ARQ_ATR, "rb");
	arq_atracao_novo = fopen(ARQ_ATR_TMP, "wb");
	if (arq_atracao_velho == NULL)	
		mensagemErroAtracao();
	else {	
		if (mensagemExcluirAtracao()=='S'){
			while(fread(&atracao, sizeof(atracao), 1, arq_atracao_velho))
				if (atracao.lixo != '*')
					fwrite(&atracao, sizeof(atracao), 1, arq_atracao_novo);	
			fclose(arq_atracao_velho);
			fclose(arq_atracao_novo);				
			remove(ARQ_ATR);
			rename(ARQ_ATR_TMP, ARQ_ATR);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelAtracao(void){
	struct tAtracao atracao;
	FILE *arq_atracao_bin;
	FILE *arq_atracao_texto;
	arq_atracao_bin = fopen(ARQ_ATR, "rb");
	arq_atracao_texto = fopen(ARQ_ATR_CSV, "w");	
	if (arq_atracao_bin == NULL || arq_atracao_texto == NULL)	
		mensagemErroAtracao();
	else {	
		fprintf(arq_atracao_texto, " ;COD; NOME; TIPO;\n");
		while(fread(&atracao, sizeof(atracao), 1, arq_atracao_bin)){
			fprintf(arq_atracao_texto, "%c;%d;%s;%s;\n", atracao.lixo, atracao.codigo, atracao.nome, atracao.tipo);
		}
		fclose(arq_atracao_bin);
		fclose(arq_atracao_texto);
		printf("\nAbrindo Excel...\n");
		// abrir excel
		system("atracao.csv"); // "\\" para entrar no arquivo da pasta pelo CMD
	}
	mensagemContinuarAtracao();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosAtracao(struct tAtracao atr){
	printf("\nExibindo dados encontrados...\n");
		exibeAtracao(atr.codigo);
		printf("\nNome: %s", atr.nome);
		printf("\nTipo: %s", atr.tipo);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuAtracao(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringAtracao (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}

// -----------------------------------------------------------------------------------------
// ----------------------------- cliente ------------------------

int principalCliente (void){
	struct tCliente cliente;
	int codigo;
	int opcao;
	do{
		exibeMenuCliente();
		opcao = validaOpcaoMenuCliente();		
		switch(opcao){
			case 1:
				printf("  ..:: CADASTRO DE CLIENTE ::..\n\n");
				cliente.codigo = incrementaCodigoCliente();
				recebeDadosCliente(&cliente);
				cadastraCliente(cliente);
				mensagemContinuarCliente();	
				break;	
			case 2:
				printf("  ..:: LISTA DE CLIENTES ::..\n\n");
				listaCliente();
				break;		
			case 3:
				printf("  ..:: CONSULTA DE CLIENTES ::..\n");
				consultaCliente();
				break;
			case 4:
				printf(" ..:: ALTERA«√O DE CLIENTE ::..\n");
				alteraCliente();
				break;
			case 5:
				printf("  ..:: EXCLUS√O TEMPORARIA DE CLIENTE ::..\n");
				excluiTempCliente();
				break;	
			case 6:
				printf("  ..:: EXCLUS√O PERMANENTE DE CLIENTES ::..\n");
				excluiPermanenteCliente();
				break;
			case 7:
				printf("  ..:: EXPORTA«√O DOS DADOS DOS CLIENTES ::..\n");
				exportaExcelCliente();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Cliente
void exibeMenuCliente(void){
	printf("\n  ..:: CLIENTE ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERA«√O \n");
	printf("  5 - EXCLUS√O TEMPORARIA\n");
	printf("  6 - EXCLUS√O PERMANENTE\n");
	printf("  7 - EXPORTAR DADOS PARA EXCEL\n");
	printf("  0 - Voltar\n"); 
	printf("\n\n  ESCOLHA UMA OP«√O: ");	
}
void exibeCliente(int cod){
	printf("\n>> CLIENTE - COD: %d <<\n", cod);
}
void mensagemContinuarCliente(void){
	printf("\n\nDigite algo para continuar...", ARQ_CL);
	getch();
	system("cls");
}
void mensagemErroCliente(){
	printf("\nErro na abertura do arquivo %s \n", ARQ_CL);
	getch();
}
char mensagemExcluirCliente(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR? *** ");
	do{
		printf("\n    Digite [S] - SIM ou [N] - NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoCliente(void){
	int cod = 1;
	struct tCliente cliente;
	FILE *arq_cliente;
	arq_cliente = fopen(ARQ_CL, "rb");
	if (arq_cliente == NULL)	
		return cod;		
	while(fread(&cliente, sizeof(cliente), 1, arq_cliente))	
		cod = cliente.codigo;			
	fclose(arq_cliente);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoCliente(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosCliente(struct tCliente *cl){
	exibeCliente(cl->codigo);
	printf("\n>>Nome: ");
	leValidaStringCliente (&cl->nome);
	printf("\n>> CPF: ");
	leValidaStringCliente (&cl->cpf);
	// Data
	printf("\n>> Data: ");
	printf("\nDia (DD): ");
    scanf("%d", &cl->dataNascimento.dia);
    printf("Mes (MM): ");
    scanf("%d", &cl->dataNascimento.mes);
    printf("Ano (AAAA): ");
    scanf("%d", &cl->dataNascimento.ano);
	printf("Genero [M] - Masc / [F] - Fem / [O] - Outros: ");
	fflush(stdin);
	cl->genero = getchar();
	printf("\n>> E-mail: ");
	leValidaStringCliente (&cl->email);
}
// ------------------ Cadastrar ------------------
void cadastraCliente(struct tCliente cl){
	FILE *arq_cliente;
	
	arq_cliente = fopen(ARQ_CL, "ab");
	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {
		cl.lixo = ' ';
		fwrite(&cl, sizeof(cl), 1, arq_cliente);
	}
	fclose(arq_cliente);
}
// ------------------ Listar ------------------
void listaCliente(void){
	struct tCliente cliente;
	FILE *arq_cliente;	
	arq_cliente = fopen(ARQ_CL, "rb");	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {	
		printf("COD |NOME              |CPF            |NASCIMENTO|GENERO|E-MAIL                |\n\n");
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
			if(cliente.lixo != '*')
				printf("%4d|%18s|%15s|%2d/%2d/%4d|%6c|%22s|\n\n", cliente.codigo, cliente.nome, cliente.cpf, 
					cliente.dataNascimento.dia, cliente.dataNascimento.mes, cliente.dataNascimento.ano,  
						cliente.genero, cliente.email);	
		mensagemContinuarCliente();	
	}		
	fclose(arq_cliente);
}
// ------------------ Consultar ------------------
void consultaCliente(void){
	int cod, achei = 0;
	struct tCliente cliente;
	FILE *arq_cliente;		
	arq_cliente = fopen(ARQ_CL, "rb");	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {	
		cod = recebeCodigoCliente();
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
			if (cod == cliente.codigo && cliente.lixo != '*'){
				mostrarDadosCliente(cliente);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Cliente nao encontrada.\n");
		mensagemContinuarCliente();
	}		
	fclose(arq_cliente);
}
// ------------------ Alterar ------------------
void alteraCliente(void){
	int cod, achei = 0;
	struct tCliente cliente;
	FILE *arq_cliente;		
	arq_cliente = fopen(ARQ_CL, "r+b");	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {	
		cod = recebeCodigoCliente();
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
			if (cod == cliente.codigo && cliente.lixo != '*'){
				mostrarDadosCliente(cliente);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosCliente(&cliente);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_cliente, -sizeof(cliente), SEEK_CUR); 
				fwrite(&cliente, sizeof(cliente), 1, arq_cliente);			
				fseek(arq_cliente, 0, SEEK_CUR); // fixar ponteiro
				}
		if (!achei)
			printf("\nErro: Cliente nao encontrado.\n");
		mensagemContinuarCliente();
	}		
	fclose(arq_cliente);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempCliente(void){
	int cod, achei = 0;
	struct tCliente cliente;
	FILE *arq_cliente;		
	arq_cliente = fopen(ARQ_CL, "r+b");	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {	
		cod = recebeCodigoCliente();
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
			if (cod == cliente.codigo && cliente.lixo != '*'){
				mostrarDadosCliente(cliente);
				achei = 1;
				if (mensagemExcluirCliente()=='S'){
					cliente.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_cliente, -sizeof(cliente), SEEK_CUR); 
					fwrite(&cliente, sizeof(cliente), 1, arq_cliente);			
					fseek(arq_cliente, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Cliente nao encontrado.\n");
		mensagemContinuarCliente();
	}		
	fclose(arq_cliente);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteCliente(){
	struct tCliente cliente;
	FILE *arq_cliente_novo;
	FILE *arq_cliente_velho;	
	arq_cliente_velho = fopen(ARQ_CL, "rb");
	arq_cliente_novo = fopen(ARQ_CL_TMP, "wb");
	if (arq_cliente_velho == NULL)	
		mensagemErroCliente();
	else {	
		if (mensagemExcluirCliente()=='S'){
			while(fread(&cliente, sizeof(cliente), 1, arq_cliente_velho))
				if (cliente.lixo != '*')
					fwrite(&cliente, sizeof(cliente), 1, arq_cliente_novo);	
			fclose(arq_cliente_velho);
			fclose(arq_cliente_novo);				
			remove(ARQ_CL);
			rename(ARQ_CL_TMP, ARQ_CL);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelCliente(void){
	struct tCliente cliente;
	FILE *arq_cliente_bin;
	FILE *arq_cliente_texto;
	arq_cliente_bin = fopen(ARQ_CL, "rb");
	arq_cliente_texto = fopen(ARQ_CL_CSV, "w");	
	if (arq_cliente_bin == NULL || arq_cliente_texto == NULL)	
		mensagemErroCliente();
	else {	
		fprintf(arq_cliente_texto, "COD;NOME;CPF;NASC;GENERO;E-MAIL\n");
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente_bin)){
			fprintf(arq_cliente_texto, " %d;%s;%s;%d/%d/%d;%c;%s\n", cliente.codigo, cliente.nome, cliente.cpf, 
			cliente.dataNascimento.dia, cliente.dataNascimento.mes, cliente.dataNascimento.ano,  
				cliente.genero, cliente.email);

		}
		fclose(arq_cliente_bin);
		fclose(arq_cliente_texto);
		printf("\nAbrindo Excel...\n");
		system(ARQ_CL_CSV);
	}
	mensagemContinuarCliente();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosCliente(struct tCliente cl){
	printf("\nExibindo dados encontrados...\n");
		exibeCliente(cl.codigo);
		printf("\n  Nome: %s", cl.nome);
		printf("\n  CPF: %s", cl.cpf);
		printf("\n  Data de Nascimento: %d/%d/%d", cl.dataNascimento.dia, cl.dataNascimento.mes,  cl.dataNascimento.ano);
		printf("\n  Genero: %c", cl.genero);
		printf("\n  E-mail: %s", cl.email);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuCliente(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringCliente (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n-> Digite algo:");
		} 		
	} while(strlen(string)==0);
}


// ---------------------------------------------------------------------------------
// ----------------------------------- evento ---------------------------


int principalEvento (void){
	struct tEvento evento;
	int codigo;
	int opcao;
	do{
		exibeMenuEvento();
		opcao = validaOpcaoMenuEvento();		
		switch(opcao){
			case 1:
				printf("  ..:: CADASTRO DE EVENTO ::..\n\n");
				evento.codigo = incrementaCodigoEvento();
				recebeDadosEvento(&evento);
				cadastraEvento(evento);
				break;	
			case 2:
				printf("  ..:: LISTA DE EVENTOS ::..\n\n");
				listaEvento();
				break;		
			case 3:
				printf("  ..:: CONSULTA DE EVENTOS ::..\n");
				consultaEvento();
				break;
			case 4:
				printf("  ..:: ALTERA«√O DE EVENTO ::..\n");
				alteraEvento();
				break;
			case 5:
				printf("  ..:: EXCLUS√O TEMPORARIA ::..\n");
				excluiTempEvento();
				break;	
			case 6:
				printf("  ..:: EXCLUS√O PERMANENTE ::..\n");
				excluiPermanenteEvento();
				break;
			case 7:
				printf("  ..:: EXPORTA«√O DOS DADOS DO EVENTO ::..\n");
				exportaExcelEvento();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Evento
void exibeMenuEvento(void){
	printf("\n  ..:: EVENTO ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERA«√O \n");
	printf("  5 - EXCLUS√O TEMPORARIA\n");
	printf("  6 - EXCLUS√O PERMANENTE\n");
	printf("  7 - EXPORTAR DADOS PARA EXCEL\n");
	printf("  0 - Voltar\n"); 
	printf("\n\n  ESCOLHA UMA OP«√O: ");		
}
void exibeEvento(int cod){
	printf("\n>> EVENTO - COD: %d <<\n", cod);
}
void mensagemContinuarEvento(void){
	printf("\n\nDigite algo para continuar...", ARQ_EVT);
	getch();
	system("cls");
}
void mensagemErroEvento(){
	printf("Erro na abertura do arquivo %s \n", ARQ_EVT);
	getch();
}
char mensagemExcluirEvento(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR? ***");
	do{
		printf("\n    Digite [S] se SIM ou [N] se NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoEvento(void){
	int cod = 1;
	struct tEvento evento;
	FILE *arq_evento;
	arq_evento = fopen(ARQ_EVT, "rb");
	if (arq_evento == NULL)	
		return cod;		
	while(fread(&evento, sizeof(evento), 1, arq_evento))	
		cod = evento.codigo;			
	fclose(arq_evento);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoEvento(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosEvento(struct tEvento *evt){
	char op;
	int qtd;
	evt->qtdAtracoes = 0;
	
	exibeEvento(evt->codigo);
	printf("\n>> Nome: ");
	leValidaStringEvento (&evt->nome);
	// Data
	printf("\n>> Data: ");
	printf("\nDia (DD): ");
    scanf("%d", &evt->data.dia);
    printf("Mes(MM): ");
    scanf("%d", &evt->data.mes);
    printf("Ano (AAAA): ");
	scanf("%d", &evt->data.ano);    	
	printf("\n>> Hora: ");
	leValidaStringEvento (&evt->hora);
	printf("\n>> Valor:R$ ");
	fflush(stdin);
	scanf("%f", &evt->valor);
	printf("\n>> Classificacao Indicativa: ");
	fflush(stdin);
	scanf("%d", &evt->classInd);
	// ---------- Adicionar (ID Atracao) ----------	
	do {
		if ((contaIdAtracao()) > 0) {
			listaIdAtracao();
			printf("\n>> Escolha uma atracao: ");
			leValidaIdAtracao(&evt->idAtracao[evt->qtdAtracoes]);
			do{
				printf("\nAdicionar outra atracao?");
				printf("\n    Digite [S] se SIM ou [N] se NAO: ");
				fflush(stdin);
				op=getchar();
				op=toupper(op);
			} while(op != 'S' && op !='N');	
			evt->qtdAtracoes++;
		} else
			op = 'N';
	} while(op=='S' && evt->qtdAtracoes<TAM);
	resetaEscolhidaAtracao();	
	// ------------- Adicionar (Id Local) -------------
	listaIdLocal();
	printf("\n>> Escolha o local: ");
	leValidaIdLocal(&evt->idLocal);
}
// ------------------ Cadastrar ------------------
void cadastraEvento(struct tEvento evt){
	FILE *arq_evento;
	
	arq_evento = fopen(ARQ_EVT, "ab");
	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {
		evt.lixo = ' ';
		fwrite(&evt, sizeof(evt), 1, arq_evento);
	}
	mensagemContinuarEvento();	
	fclose(arq_evento);
}
// ------------------ Listar ------------------
void listaEvento(void){
	int i;
	struct tEvento evento;
	FILE *arq_evento;	
	arq_evento = fopen(ARQ_EVT, "rb");	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {	
		printf("COD |NOME             |DATA      |HORA   |VALOR    |CLASSIFICACAO |LOCAL  |ATRA«√O    \n");
		while(fread(&evento, sizeof(evento), 1, arq_evento)){
			//if(evento.lixo != '*')
				printf("%4d|%17s|%2d/%2d/%4d|%7s|R$%7.2f|%14d|%7d|", evento.codigo, evento.nome,
				 	evento.data.dia, evento.data.mes, evento.data.ano, evento.hora, evento.valor, evento.classInd, evento.idLocal);
				for(i = 0; i<evento.qtdAtracoes; i++)
					printf("%d-", evento.idAtracao[i]);
				printf("\n");			
		}
		mensagemContinuarEvento();	
	}		
	fclose(arq_evento);
}
// ------------------ Consultar ------------------
void consultaEvento(void){
	int cod, achei = 0;
	struct tEvento evento;
	FILE *arq_evento;		
	arq_evento = fopen(ARQ_EVT, "rb");	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {	
		cod = recebeCodigoEvento();
		while(fread(&evento, sizeof(evento), 1, arq_evento))
			if (cod == evento.codigo && evento.lixo != '*'){
				mostrarDadosEvento(evento);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Evento nao encontrada.\n");
		mensagemContinuarEvento();
	}		
	fclose(arq_evento);
}
// ------------------ Alterar ------------------
void alteraEvento(void){
	int cod, achei = 0;
	struct tEvento evento;
	FILE *arq_evento;		
	arq_evento = fopen(ARQ_EVT, "r+b");	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {	
		cod = recebeCodigoEvento();
		while(fread(&evento, sizeof(evento), 1, arq_evento))
			if (cod == evento.codigo && evento.lixo != '*'){
				mostrarDadosEvento(evento);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosEvento(&evento);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_evento, -sizeof(evento), SEEK_CUR); 
				fwrite(&evento, sizeof(evento), 1, arq_evento);			
				fseek(arq_evento, 0, SEEK_CUR); // fixar ponteiro
				}
		if (!achei)
			printf("\nErro: Evento nao encontrada.\n");
		mensagemContinuarEvento();
	}		
	fclose(arq_evento);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempEvento(void){
	int cod, achei = 0;
	struct tEvento evento;
	FILE *arq_evento;		
	arq_evento = fopen(ARQ_EVT, "r+b");	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {	
		cod = recebeCodigoEvento();
		while(fread(&evento, sizeof(evento), 1, arq_evento))
			if (cod == evento.codigo && evento.lixo != '*'){
				mostrarDadosEvento(evento);
				achei = 1;
				if (mensagemExcluirEvento()=='S'){
					evento.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_evento, -sizeof(evento), SEEK_CUR); 
					fwrite(&evento, sizeof(evento), 1, arq_evento);			
					fseek(arq_evento, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Evento nao encontrada.\n");
		mensagemContinuarEvento();
	}		
	fclose(arq_evento);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteEvento(){
	struct tEvento evento;
	FILE *arq_evento_novo;
	FILE *arq_evento_velho;	
	arq_evento_velho = fopen(ARQ_EVT, "rb");
	arq_evento_novo = fopen(ARQ_EVT_TMP, "wb");
	if (arq_evento_velho == NULL)	
		mensagemErroEvento();
	else {	
		if (mensagemExcluirEvento()=='S'){
			while(fread(&evento, sizeof(evento), 1, arq_evento_velho))
				if (evento.lixo != '*')
					fwrite(&evento, sizeof(evento), 1, arq_evento_novo);	
			fclose(arq_evento_velho);
			fclose(arq_evento_novo);				
			remove(ARQ_EVT);
			rename(ARQ_EVT_TMP, ARQ_EVT);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelEvento(void){
	int i;
	struct tEvento evento;
	FILE *arq_evento_bin;
	FILE *arq_evento_texto;
	arq_evento_bin = fopen(ARQ_EVT, "rb");
	arq_evento_texto = fopen(ARQ_EVT_CSV, "w");	
	if (arq_evento_bin == NULL || arq_evento_texto == NULL)	
		mensagemErroEvento();
	else {	
		fprintf(arq_evento_texto, "COD; NOME; DATA; HORA; VALOR; CLASSIFICA«√O; LOCAL; ATRA«√O\n");
		while(fread(&evento, sizeof(evento), 1, arq_evento_bin)){
			fprintf(arq_evento_texto, "%d; %s; %d/%d/%d; %s; R$%.2f; %d; %d;",
				evento.codigo, evento.nome, evento.data.dia, evento.data.mes, evento.data.ano, evento.hora, evento.valor, evento.classInd, evento.idLocal);
			for(i = 0; i<evento.qtdAtracoes; i++)
					fprintf(arq_evento_texto,"%d, ", evento.idAtracao[i]);
				fprintf(arq_evento_texto,"\n");	
		}
		fclose(arq_evento_bin);
		fclose(arq_evento_texto);
		printf("\nAbrindo Excel...\n");
		system(ARQ_EVT_CSV);
	}
	mensagemContinuarEvento();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosEvento(struct tEvento evt){
	int i;
	printf("\n  Exibindo dados encontrados...\n");
	exibeEvento(evt.codigo);
	printf("\n  Nome: %s", evt.nome);
	printf("\n  Data: %d/%d/%d", evt.data.dia, evt.data.mes, evt.data.ano);
	printf("\n  Hora: %s", evt.hora);
	printf("\n  Valor: R$%.2f", evt.valor);
	printf("\n  ClassificaÁ„o: %d", evt.classInd);
	printf("\n  ID Local: %d", evt.idLocal);
	printf("\n  ID Atracoes: ");
	for(i = 0; i<evt.qtdAtracoes; i++)
		printf("%d, ", evt.idAtracao[i]);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuEvento(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringEvento (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}
// ******************* ADICIONAR ****************
// Valida Local 
void listaIdLocal(void){
	struct tLocal local;
	int achei;
	FILE *arq_local;	
	arq_local = fopen(ARQ_LC, "rb");	
	if (arq_local == NULL){
		mensagemErroLocal();
		printf("\nRedirecionando para o menu de Locais");
		printf("Cadastro de Locais\n\n");
		local.codigo = incrementaCodigoLocal();
		recebeDadosLocal(&local);
		cadastraLocal(local);
	}
	printf("\n\n--- LOCAIS DISPONIVEIS ---");
	printf("\nCOD |NOME               |CAPACIDADE   |ENDERECO               |\n\n");
	while(fread(&local, sizeof(local), 1, arq_local))
		if(local.lixo != '*')
			printf("%4d|%20s|%14d|%24s\n\n", local.codigo, 
				local.nome, local.capacidade, local.endereco);	
	fclose(arq_local);	
}

void leValidaIdLocal(int *idLocal){
	struct tLocal local;
	int achei;
		FILE *arq_local;
		do{	
			scanf("%d", idLocal);
			arq_local = fopen(ARQ_LC, "rb");	
			achei = 0;		
			while(fread(&local, sizeof(local), 1, arq_local))
				if(local.lixo != '*' && local.codigo == *idLocal)
						achei = 1;		
			if(!achei)
				printf("\nLocal Invalido! Digite novamente: ");
			fclose(arq_local);
		}while(!achei);
}

// Lista ID Atracao 
void listaIdAtracao(void){
	int cont  = 0;
	struct tAtracao atracao;
	FILE *arq_atracao;	
	arq_atracao = fopen(ARQ_ATR, "r+b");	
	if (arq_atracao == NULL){
		mensagemErroLocal();
		printf("Cadastro de Atracoes\n\n");
		atracao.codigo = incrementaCodigoAtracao();
		recebeDadosAtracao(&atracao);
		cadastraAtracao(atracao);
	}	
	printf("\n\n---- ATRACOES DISPONIVEIS ----");
	printf("\nCOD |NOME              |TIPO        \n\n");
	while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
		if (atracao.lixo != '*' && atracao.escolhido == 0)
			printf("%4d|%19s|%13s %c\n\n", atracao.codigo, atracao.nome, atracao.tipo, atracao.lixo);
	fclose(arq_atracao);
}

// Conta ID Atracao 
int contaIdAtracao(void){
	int cont  = 0;
	struct tAtracao atracao;
	FILE *arq_atracao;	
	arq_atracao = fopen(ARQ_ATR, "rb");	
	if (arq_atracao == NULL)
		mensagemErroLocal();
	while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
		if (atracao.lixo != '*' && atracao.escolhido == 0) 
			cont++;
	fclose(arq_atracao);
	return cont;
}

void leValidaIdAtracao(int *idAtracao[]){
	struct tAtracao atracao;
	int achei;
		FILE *arq_atracao;
		do{	
			scanf("%d", idAtracao);
			arq_atracao = fopen(ARQ_ATR, "r+b");	
			achei = 0;		
			while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
				if(atracao.lixo != '*' && atracao.codigo == *idAtracao && atracao.escolhido == 0){
					achei = 1;
					atracao.escolhido = 1;					
					/* posicionando o cursor no registro encontrado */
					fseek(arq_atracao, -sizeof(atracao), SEEK_CUR); 
					fwrite(&atracao, sizeof(atracao), 1, arq_atracao);			
					fseek(arq_atracao, 0, SEEK_CUR); // fixar ponteiro	
					}
			if(!achei)
				printf("\nAtracao Invalida! Digite novamente: ");
			fclose(arq_atracao);
		}while(!achei);
}

// Resetar atracao escolhida
void resetaEscolhidaAtracao(void){
	struct tAtracao atracao;
	FILE *arq_atracao;
	arq_atracao = fopen(ARQ_ATR, "r+b");		
	while(fread(&atracao, sizeof(atracao), 1, arq_atracao))
		if(atracao.lixo != '*' && atracao.escolhido == 1){
			atracao.escolhido = 0;					
			/* posicionando o cursor no registro encontrado */
			fseek(arq_atracao, -sizeof(atracao), SEEK_CUR); 
			fwrite(&atracao, sizeof(atracao), 1, arq_atracao);			
			fseek(arq_atracao, 0, SEEK_CUR); // fixar ponteiro	
		}
	fclose(arq_atracao);
}

// -----------------------------------------------------------------------------
// ------------------------------ local --------------------------------

int principalLocal (void){
	struct tLocal local;
	int codigo;
	int opcao;
	do{
		exibeMenuLocal();
		opcao = validaOpcaoMenuLocal();		
		switch(opcao){
			case 1:
				printf("  ..:: CADASTRO DE LOCAL ::..\n\n");
				local.codigo = incrementaCodigoLocal();
				recebeDadosLocal(&local);
				cadastraLocal(local);
				break;	
			case 2:
				printf("  ..:: LISTA DE LOCAIS ::..\n\n");
				listaLocal();
				break;		
			case 3:
				printf("  ..:: CONSULTAR LOCAL ::..\n");
				consultaLocal();
				break;
			case 4:
				printf("  ..:: ALTERAR LOCAL ::..\n");
				alteraLocal();
				break;
			case 5:
				printf("  ..:: EXCLUS√O TEMPORARIA DE LOCAL ::..\n");
				excluiTempLocal();
				break;	
			case 6:
				printf("  ..:: EXCLUS√O PERMANENTE ::..\n");
				excluiPermanenteLocal();
				break;
			case 7:
				printf("  ..:: EXPORTAR DADOS PARA O EXCEL ::..\n");
				exportaExcelLocal();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Local
void exibeMenuLocal(void){
	printf("\n  ..:: LOCAL ::..\n\n");
	printf("  1 - CADASTRAR \n");
	printf("  2 - LISTAR\n");
	printf("  3 - CONSULTAR POR CODIGO\n");
	printf("  4 - ALTERA«√O \n");
	printf("  5 - EXCLUS√O TEMPORARIA\n");
	printf("  6 - EXCLUS√O PERMANENTE\n");
	printf("  7 - EXPORTAR DADOS PARA EXCEL\n");
	printf("  0 - Voltar\n"); // executado na "main.c" volta
	printf("\n\n  ESCOLHA UMA OP«√O: ");	
}
void exibeLocal(int cod){
	printf("\n>> LOCAL - COD: %d <<\n", cod);
}
void mensagemContinuarLocal(void){
	printf("\n\nDigite algo para continuar...", ARQ_LC);
	getch();
	system("cls");
}
void mensagemErroLocal(){
	printf("\nErro na abertura do arquivo %s \n", ARQ_LC);
	getch();
}
char mensagemExcluirLocal(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR?*** ");
	do{
		printf("\n    Digite [S] se SIM ou [N] se NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoLocal(void){
	int cod = 1;
	struct tLocal local;
	FILE *arq_local;
	arq_local = fopen(ARQ_LC, "rb");
	if (arq_local == NULL)	
		return cod;		
	while(fread(&local, sizeof(local), 1, arq_local))	
		cod = local.codigo;			
	fclose(arq_local);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoLocal(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosLocal(struct tLocal *lc){
	exibeLocal(lc->codigo);
	printf("\n>> Nome: ");
	leValidaStringLocal (&lc->nome);
	printf("\n>> Capacidade: ");
	scanf("%d", &lc->capacidade);
	printf("\n>> Endereco: ");
	leValidaStringLocal (&lc->endereco);
}
// ------------------ Cadastrar ------------------
void cadastraLocal(struct tLocal lc){
	FILE *arq_local;
	
	arq_local = fopen(ARQ_LC, "ab");
	
	if (arq_local == NULL)	
		mensagemErroLocal();
	else {
		lc.lixo = ' ';
		fwrite(&lc, sizeof(lc), 1, arq_local);
	}
	mensagemContinuarLocal();	
	fclose(arq_local);
}
// ------------------ Listar ------------------
void listaLocal(void){
	struct tLocal local;
	FILE *arq_local;	
	arq_local = fopen(ARQ_LC, "rb");	
	if (arq_local == NULL)	
		mensagemErroLocal();
	else {	
		printf("COD |NOME                 |CAPACIDADE   |ENDERECO                           |\n\n");
		while(fread(&local, sizeof(local), 1, arq_local))
			//if(local.lixo != '*')
				printf("%4d|%21s|%13d|%35s|%c\n\n", local.codigo, 
					local.nome, local.capacidade, local.endereco, local.lixo);	
		mensagemContinuarLocal();	
	}		
	fclose(arq_local);
}
// ------------------ Consultar ------------------
void consultaLocal(void){
	int cod, achei = 0;
	struct tLocal local;
	FILE *arq_local;		
	arq_local = fopen(ARQ_LC, "rb");	
	if (arq_local == NULL)	
		mensagemErroLocal();
	else {	
		cod = recebeCodigoLocal();
		while(fread(&local, sizeof(local), 1, arq_local))
			if (cod == local.codigo && local.lixo != '*'){
				mostrarDadosLocal(local);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Local nao encontrada.\n");
		mensagemContinuarLocal();
	}		
	fclose(arq_local);
}
// ------------------ Alterar ------------------
void alteraLocal(void){
	int cod, achei = 0;
	struct tLocal local;
	FILE *arq_local;		
	arq_local = fopen(ARQ_LC, "r+b");	
	if (arq_local == NULL)	
		mensagemErroLocal();
	else {	
		cod = recebeCodigoLocal();
		while(fread(&local, sizeof(local), 1, arq_local))
			if (cod == local.codigo && local.lixo != '*'){
				mostrarDadosLocal(local);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosLocal(&local);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_local, -sizeof(local), SEEK_CUR); 
				fwrite(&local, sizeof(local), 1, arq_local);			
				fseek(arq_local, 0, SEEK_CUR); // fixar ponteiro
				}
		if (!achei)
			printf("\nErro: Local nao encontrada.\n");
		mensagemContinuarLocal();
	}		
	fclose(arq_local);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempLocal(void){
	int cod, achei = 0;
	struct tLocal local;
	FILE *arq_local;		
	arq_local = fopen(ARQ_LC, "r+b");	
	if (arq_local == NULL)	
		mensagemErroLocal();
	else {	
		cod = recebeCodigoLocal();
		while(fread(&local, sizeof(local), 1, arq_local))
			if (cod == local.codigo && local.lixo != '*'){
				mostrarDadosLocal(local);
				achei = 1;
				if (mensagemExcluirLocal()=='S'){
					local.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_local, -sizeof(local), SEEK_CUR); 
					fwrite(&local, sizeof(local), 1, arq_local);			
					fseek(arq_local, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Local nao encontrada.\n");
		mensagemContinuarLocal();
	}		
	fclose(arq_local);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteLocal(){
	struct tLocal local;
	FILE *arq_local_novo;
	FILE *arq_local_velho;	
	arq_local_velho = fopen(ARQ_LC, "rb");
	arq_local_novo = fopen(ARQ_LC_TMP, "wb");
	if (arq_local_velho == NULL)	
		mensagemErroLocal();
	else {	
		if (mensagemExcluirLocal()=='S'){
			while(fread(&local, sizeof(local), 1, arq_local_velho))
				if (local.lixo != '*')
					fwrite(&local, sizeof(local), 1, arq_local_novo);	
			fclose(arq_local_velho);
			fclose(arq_local_novo);				
			remove(ARQ_LC);
			rename(ARQ_LC_TMP, ARQ_LC);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelLocal(void){
	struct tLocal local;
	FILE *arq_local_bin;
	FILE *arq_local_texto;
	arq_local_bin = fopen(ARQ_LC, "rb");
	arq_local_texto = fopen(ARQ_LC_CSV, "w");	
	if (arq_local_bin == NULL || arq_local_texto == NULL)	
		mensagemErroLocal();
	else {	
		fprintf(arq_local_texto, " COD;  NOME;  CAP;  ENDERECO; EXCLUIDO\n");
		while(fread(&local, sizeof(local), 1, arq_local_bin)){
			fprintf(arq_local_texto, " %d; %s;  %d;  %s; [%c]\n", local.codigo, 
					local.nome, local.capacidade, local.endereco, local.lixo);
		}
		fclose(arq_local_bin);
		fclose(arq_local_texto);
		printf("\nAbrindo Excel...\n");
		system(ARQ_LC_CSV);
	}
	mensagemContinuarLocal();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosLocal(struct tLocal lc){
	printf("\nExibindo dados encontrados...\n");
		exibeLocal(lc.codigo);
		printf("\nNome: %s", lc.nome);
		printf("\nCapacidade: %d", lc.capacidade);
		printf("\nEndereco: %s", lc.endereco);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuLocal(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringLocal (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}


// -----------------------------------------------------------------------------------------
// ----------------------------- venda -----------------------------------


int principalVenda (void){
	struct tVenda venda;
	int codigo;
	int opcao;
	do{
		exibeMenuVenda();
		opcao = validaOpcaoMenuVenda();		
		switch(opcao){
			case 1:
				printf("  ..:: INICIAR VENDA DE INGRESSO ::..\n\n");
				venda.codigo = incrementaCodigoVenda();
				recebeDadosVenda(&venda);
				cadastraVenda(venda);
				break;	
			case 2:
				printf("  ..:: LISTAR INGRESSOS VENDIDOS ::..\n\n");
				listaVenda();
				break;		
			case 3:
				printf("  ..:: CONSULTAR INGRESSOS POR CPF ::..\n");
				consultaVenda();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Venda
void exibeMenuVenda(void){
	printf("\n  ..:: VENDA ::..\n\n");
	printf("  1 - INICIAR VENDA DE INGRESSOS\n");
	printf("  2 - LISTAR INGRESSOS VENDIDOS \n");
	printf("  3 - CONSULTAR INGRESSOS POR CPF\n");
	printf("  0 - VOLTAR\n"); // executado na "main.c" volta
	printf("\n\nEscolha uma opcao: ");	
}
void exibeVenda(int cod){
	printf("\n>> VENDA - COD: %d <<\n", cod);
}
void mensagemContinuarVenda(void){
	printf("\n\nDigite algo para continuar...", ARQ_VD);
	getch();
	system("cls");
}
void mensagemErroVenda(){
	printf("\nErro na abertura do arquivo %s \n", ARQ_VD);
	getch();
}
char mensagemExcluirVenda(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR?***");
	do{
		printf("\n    Digite [S] se SIM ou [N] se NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoVenda(void){
	int cod = 1;
	struct tVenda venda;
	FILE *arq_venda;
	arq_venda = fopen(ARQ_VD, "rb");
	if (arq_venda == NULL)	
		return cod;		
	while(fread(&venda, sizeof(venda), 1, arq_venda))	
		cod = venda.codigo;			
	fclose(arq_venda);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------

// ------------------ Receber Dados ------------------
void recebeDadosVenda(struct tVenda *vd){
	exibeVenda(vd->codigo);
	printf("\n>> Digite o CPF do Cliente: ");
	leValidaCpfCliente(&vd->cpfCliente);
	listaIdEvento();
	printf("\n>> Digite o ID do Evento: ");
	leValidaIdEvento(&vd->idEvento);
	printf("\n>> Digite a quantidade de ingressos desejados: ");
	scanf("%d", &vd->quantidade);
	
	vd->total = calculaTotal(vd->idEvento, vd->quantidade);
}
// ------------------ Cadastrar ------------------
void cadastraVenda(struct tVenda vd){
	int op;
	FILE *arq_venda;
	
	arq_venda = fopen(ARQ_VD, "ab");
	
	if (arq_venda == NULL)	
		mensagemErroVenda();
	else {
		system("cls");
			
		printf(" --- MOSTRANDO DADOS DA COMPRA  ---\n");
		clienteVenda(vd.cpfCliente);
		eventoVenda(vd.idEvento);
		printf("\n >>> Quantidade de Ingressos: %d", vd.quantidade);
		printf("\n >>> Valor Total: R$%.2f <<<", vd.total);
		do{
			printf("\n Deseja confirmar [s] - [n]:\n");
			fflush(stdin);
			op=getchar();
			op=toupper(op);
		} while(op != 'S' && op !='N');	
		if(op!='S'){
			printf("Compra cancelada!\n");
			printf("Aguarde...\n");
			Sleep(2000);			
		} else {
			printf("Compra confirmada!\n");
			/* MOSTRA DADOS DA COMPRA: NOME DO CLIENTE, NOME DO EVENTO,
			DATA DO EVENTO, VALOR PAGO NO TOTAL, QUANTIDADE COMPRADA 
			--- SALVAR EM ARQUIVO TXT --- */
			fwrite(&vd, sizeof(vd), 1, arq_venda);
			fclose(arq_venda);
			printf("Aguarde...\n");
			Sleep(2000);
			do{
				printf("\n\nDeseja gerar ingresso [s] - [n]:\n");
				fflush(stdin);
				op=getchar();
				op=toupper(op);
			} while(op != 'S' && op !='N');
			if(op=='S')
				gerarIngresso(vd.codigo);	
		}
	}
}
// ------------------ Listar ------------------
void listaVenda(void){
	struct tVenda venda;
	FILE *arq_venda;	
	arq_venda = fopen(ARQ_VD, "rb");	
	if (arq_venda == NULL)	
		mensagemErroVenda();
	else {	
		printf("COD |IdCliente  |IdEvento  |Ingressos |ValorTotal\n\n");
		while(fread(&venda, sizeof(venda), 1, arq_venda))
				printf("%4d|%12s|%11d|%11d|R$%11.2f\n\n", venda.codigo, 
					venda.cpfCliente, venda.idEvento, venda.quantidade, venda.total);	
		mensagemContinuarVenda();	
	}		
	fclose(arq_venda);
}
// ------------------ Consultar ------------------
void consultaVenda(void){
	int cod, achei = 0;
	char cpf[TAM];
	char op;
	struct tVenda venda;
	FILE *arq_venda;		
	arq_venda = fopen(ARQ_VD, "rb");	
	if (arq_venda == NULL)	
		mensagemErroVenda();
	else {	
		printf("\nDigite o cpf do cliente para ser consultado:");
		fflush(stdin);
		gets(cpf);
		while(fread(&venda, sizeof(venda), 1, arq_venda))
			if(strcmp(cpf, venda.cpfCliente) == 0){
				mostrarDadosVenda(venda);
				achei = 1;				
			}
		do{
			printf("\n\n>>Deseja gerar ingresso [S] - [S]:\n");
			fflush(stdin);
			op=getchar();
			op=toupper(op);
		} while(op != 'S' && op !='N');	
		if(op=='S'){
			printf("\n--Digite o codigo da venda: ");
			scanf("%d", &cod);
			gerarIngresso(cod);	
		}
		if (!achei)
			printf("\nErro: Venda nao encontrada.\n");
		mensagemContinuarVenda();
	}		
	fclose(arq_venda);
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosVenda(struct tVenda vd){
	printf("\nExibindo dados encontrados...\n");
		exibeVenda(vd.codigo);
		printf("\nCPF Cliente: %s", vd.cpfCliente);
		printf("\nId Evento: %d", vd.idEvento);
		printf("\nQuantidade: %d", vd.quantidade);
		printf("\nValor Total: R$ %.2f", vd.total);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuVenda(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OP_VENDA)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OP_VENDA);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringVenda (char *string){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}

// Valida ID Cliente
void leValidaCpfCliente(char *cpfCliente[]){
	struct tCliente cliente;
	int achei;
	char op;
		FILE *arq_cliente;
		do{
			fflush(stdin);	
			gets(cpfCliente);
			fflush(stdin);
			arq_cliente = fopen(ARQ_CL, "rb");	
			achei = 0;		
			while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
				if(cliente.lixo != '*' && strcmp(cpfCliente, cliente.cpf) == 0)
						achei = 1;		
			if(!achei){
				do{
					fflush(stdin);
					printf("\nCliente Nao Cadastrado! Deseja cadastra-lo?(S/N)");
					fflush(stdin);
					op=getchar();
					op=toupper(op);
				}while(op != 'S' && op !='N');	
				if(op=='S'){
					fflush(stdin);
					printf("Cadastro de Clientes\n\n");
					cliente.codigo = incrementaCodigoCliente();
					recebeDadosCliente(&cliente);
					cadastraCliente(cliente);
				}
				fflush(stdin);
				printf("\nDigite o CPF do Cliente: ");
			}
			fclose(arq_cliente);
		}while(!achei);
}
// Valida Evento 
void listaIdEvento(void){
	struct tEvento evento;
	int achei;
	FILE *arq_evento;	
	arq_evento = fopen(ARQ_EVT, "rb");	
	if (arq_evento == NULL){
		mensagemErroEvento();
		return;
	}
	printf("\n\n---- EVENTOS DISPONIVEIS ----\n\n");
	printf("COD |NOME             |DATA      |HORA   |VALOR    |CLASSIFICACAO |LOCAL  |ATRA«√O    \n");
	while(fread(&evento, sizeof(evento), 1, arq_evento))
		if(evento.lixo != '*')
			printf("%4d|%17s|%2d/%2d/%4d|%7s|R$%7.2f|%14d|%7d|\n", evento.codigo, evento.nome,
				 	evento.data.dia, evento.data.mes, evento.data.ano, evento.hora, evento.valor, evento.classInd, evento.idLocal);	
	fclose(arq_evento);	
}

void leValidaIdEvento(int *idEvento){
	struct tEvento evento;
	int achei;
		FILE *arq_evento;
		do{	
			scanf("%d", idEvento);
			arq_evento = fopen(ARQ_EVT, "rb");	
			achei = 0;		
			while(fread(&evento, sizeof(evento), 1, arq_evento))
				if(evento.lixo != '*' && evento.codigo == *idEvento)
						achei = 1;		
			if(!achei)
				printf("\nEvento Invalido! Digite novamente: ");
			fclose(arq_evento);
		}while(!achei);
}	

float calculaTotal(int idEvento, int qtd){
	struct tEvento evento;
	float total;
	FILE *arq_evento;
	arq_evento = fopen(ARQ_EVT, "rb");	
	while(fread(&evento, sizeof(evento), 1, arq_evento))
		if(evento.lixo != '*' && evento.codigo == idEvento)
				total = evento.valor*qtd;
	fclose(arq_evento);
	return total;
}

// ------------------ Consultar ------------------
void eventoVenda(int idEvento){
	int cod, achei = 0;
	struct tEvento evento;
	FILE *arq_evento;		
	arq_evento = fopen(ARQ_EVT, "rb");	
	if (arq_evento == NULL)	
		mensagemErroEvento();
	else {	
		while(fread(&evento, sizeof(evento), 1, arq_evento))
			if (idEvento == evento.codigo && evento.lixo != '*')
				mostrarDadosEvento(evento);
	}		
	fclose(arq_evento);
}	

void clienteVenda(char cpfCliente[]){
	int cod, achei = 0;
	struct tCliente cliente;
	FILE *arq_cliente;		
	arq_cliente = fopen(ARQ_CL, "rb");	
	if (arq_cliente == NULL)	
		mensagemErroCliente();
	else {	
		while(fread(&cliente, sizeof(cliente), 1, arq_cliente))
			if (strcmp(cpfCliente, cliente.cpf) == 0 && cliente.lixo != '*')
				mostrarDadosCliente(cliente);
	}		
	fclose(arq_cliente);
}	


// ------------------ Gerar Ingresso ------------------
void gerarIngresso(int idVenda){
	struct tVenda venda;
	FILE *arq_venda_bin;
	FILE *arq_venda_texto;
	arq_venda_bin = fopen(ARQ_VD, "rb");
	arq_venda_texto = fopen(ARQ_VD_CSV, "w");	
	if(arq_venda_bin == NULL)
		mensagemErroVenda();
	else {	
		fprintf(arq_venda_texto, "<<< INGRESSO >>>\n");
		while(fread(&venda, sizeof(venda), 1, arq_venda_bin)){
			if(idVenda==venda.codigo)
				fprintf(arq_venda_texto, "CLIENTE: %s\n\n EVENTO: %d\n", venda.cpfCliente, venda.idEvento);
		}
		fclose(arq_venda_bin);
		fclose(arq_venda_texto);
		printf("\nGerando Ingresso...\n");
		system(ARQ_VD_CSV);
	}
	mensagemContinuarVenda();
}


int principalLogin (void){
	struct tLogin login;
	int codigo;
	int opcao;
	do{
		exibeMenuLogin();
		opcao = validaOpcaoMenuLogin();		
		switch(opcao){
			case 1:
				printf("Cadastro de Logins\n\n");
				login.codigo = incrementaCodigoLogin();
				recebeDadosLogin(&login);
				cadastraLogin(login);
				break;	
			case 2:
				printf("Lista de Logins\n\n");
				listaLogin();
				break;		
			case 3:
				printf("Consulta de Logins\n");
				consultaLogin();
				break;
			case 4:
				printf("Alteracao de Logins\n");
				alteraLogin();
				break;
			case 5:
				printf("Exclusao temporaria de Logins\n");
				excluiTempLogin();
				break;	
			case 6:
				printf("Exclusao Permanente de Logins\n");
				excluiPermanenteLogin();
				break;
			case 7:
				printf("Exportar Tabela de Logins para o excel\n");
				exportaExcelLogin();
				break;
		}		
	} while (opcao!=0);
	return 0;
}
// ------------------ EXIBICAO ------------------
// Funcao Exibir Menu da Login
void exibeMenuLogin(void){
	printf("\n>> LOGIN <<\n\n");
	printf("1. CADASTRAR\n");
	printf("2. LISTAR\n");
	printf("3. CONSULTAR\n");
	printf("4. ALTERAR \n");
	printf("5. EXCLUIR TEMPORARIAMENTE\n");
	printf("6. EXCLUIR PERMANENTEMENTE\n");
	printf("7. EXPORTAR\n");
	printf("0. VOLTAR\n"); // executado na "main.c" volta
	printf("\n\nEscolha uma opcao: ");	
}
void exibeLogin(int cod){
	printf("\n>> LOGIN - COD: %d <<\n", cod);
}
void mensagemContinuarLogin(void){
	printf("\n\nDigite algo para continuar...", ARQ_LG);
	getch();
	system("cls");
}
void mensagemErroLogin(){
	printf("\nErro na abertura do arquivo %s \n", ARQ_LG);
	getch();
}
char mensagemExcluirLogin(void){
	char op;
	printf("\n\n*** ATENCAO: ESSA ACAO NAO PODERA SER DESFEITA.");
	printf("\n    TEM CERTEZA QUE DESEJA CONTINUAR?");
	do{
		printf("\n    Digite \"S\" se SIM ou \"N\" se NAO: ");
		fflush(stdin);
		op=getchar();
		op=toupper(op);
	} while(op != 'S' && op !='N');	
	return op;
}
// ------------------ Incrementa Codigo ------------------
int incrementaCodigoLogin(void){
	int cod = 1;
	struct tLogin login;
	FILE *arq_login;
	arq_login = fopen(ARQ_LG, "rb");
	if (arq_login == NULL)	
		return cod;		
	while(fread(&login, sizeof(login), 1, arq_login))	
		cod = login.codigo;			
	fclose(arq_login);			
	return ++cod;
}
// ------------------ Receber Codigo para consulta ------------------
int recebeCodigoLogin(void){
	int cod;
	printf("\nDigite o codigo para ser consultado:");
	scanf("%d", &cod);
	return cod;
}
// ------------------ Receber Dados ------------------
void recebeDadosLogin(struct tLogin *lg){
	exibeLogin(lg->codigo);
	printf("\n>> Usuario: ");
	leValidaStringLogin (&lg->usuario);
	printf("\n>> Senha: ");
	getsSenhaWallisson(&lg->senha);
	// ------------- Nivel -------------
	do{
		printf("\n\n***Nivel de acesso***\n 2-Gerente\n 3-Atendente");
		printf("\n\n>> Escolha um nivel: ");
		scanf("%d", &lg->nivel);
	}while(lg->nivel!=2 && lg->nivel!=3);	
}
// ------------------ Cadastrar ------------------
void cadastraLogin(struct tLogin lg){
	FILE *arq_login;
	
	arq_login = fopen(ARQ_LG, "ab");
	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {
		lg.lixo = ' ';
		fwrite(&lg, sizeof(lg), 1, arq_login);
	}
	mensagemContinuarLogin();	
	fclose(arq_login);
}
// ------------------ Listar ------------------
void listaLogin(void){
	struct tLogin login;
	FILE *arq_login;	
	arq_login = fopen(ARQ_LG, "rb");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		printf(" COD  USUARIO SENHA NIVEL \n\n");
		while(fread(&login, sizeof(login), 1, arq_login))
			//if(login.lixo != '*')
				printf(" %d %s  %s  %d\n\n", login.codigo, 
					login.usuario, login.senha, login.nivel);	
		mensagemContinuarLogin();	
	}		
	fclose(arq_login);
}
// ------------------ Consultar ------------------
void consultaLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "rb");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				achei = 1;
			}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Alterar ------------------
void alteraLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "r+b");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				printf("\n\n*** ATENCAO: CODIGO NAO PODERA SER ALTERADO. ***\n");
				printf("Digite os novos dados:");	
				recebeDadosLogin(&login);
				achei = 1;
				/* posicionando o cursor no registro encontrado */
				fseek(arq_login, -sizeof(login), SEEK_CUR); 
				fwrite(&login, sizeof(login), 1, arq_login);			
				fseek(arq_login, 0, SEEK_CUR); // fixar ponteiro
				}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Exclusao Temporaria ------------------
void excluiTempLogin(void){
	int cod, achei = 0;
	struct tLogin login;
	FILE *arq_login;		
	arq_login = fopen(ARQ_LG, "r+b");	
	if (arq_login == NULL)	
		mensagemErroLogin();
	else {	
		cod = recebeCodigoLogin();
		while(fread(&login, sizeof(login), 1, arq_login))
			if (cod == login.codigo && login.lixo != '*'){
				mostrarDadosLogin(login);
				achei = 1;
				if (mensagemExcluirLogin()=='S'){
					login.lixo = '*'; // adicionar um texcolor com vermelho aqui
					/* posicionando o cursor no registro encontrado */
					fseek(arq_login, -sizeof(login), SEEK_CUR); 
					fwrite(&login, sizeof(login), 1, arq_login);			
					fseek(arq_login, 0, SEEK_CUR); // fixar ponteiro
				}
			}
		if (!achei)
			printf("\nErro: Login nao encontrada.\n");
		mensagemContinuarLogin();
	}		
	fclose(arq_login);
}
// ------------------ Exclusao Permanente ------------------ 
void excluiPermanenteLogin(){
	struct tLogin login;
	FILE *arq_login_novo;
	FILE *arq_login_velho;	
	arq_login_velho = fopen(ARQ_LG, "rb");
	arq_login_novo = fopen(ARQ_LG_TMP, "wb");
	if (arq_login_velho == NULL)	
		mensagemErroLogin();
	else {	
		if (mensagemExcluirLogin()=='S'){
			while(fread(&login, sizeof(login), 1, arq_login_velho))
				if (login.lixo != '*')
					fwrite(&login, sizeof(login), 1, arq_login_novo);	
			fclose(arq_login_velho);
			fclose(arq_login_novo);				
			remove(ARQ_LG);
			rename(ARQ_LG_TMP, ARQ_LG);	
		}
	}		
}
// ------------------ Exporta para o Excel ------------------
void exportaExcelLogin(void){
	struct tLogin login;
	FILE *arq_login_bin;
	FILE *arq_login_texto;
	arq_login_bin = fopen(ARQ_LG, "rb");
	arq_login_texto = fopen(ARQ_LG_CSV, "w");	
	if (arq_login_bin == NULL || arq_login_texto == NULL)	
		mensagemErroLogin();
	else {	
		fprintf(arq_login_texto, " COD;  USUARIO; SENHA; NIVEL\n");
		while(fread(&login, sizeof(login), 1, arq_login_bin)){
			fprintf(arq_login_texto, " %d; %s;  %s;  %d\n", login.codigo, 
					login.usuario, login.senha, login.nivel);
		}
		fclose(arq_login_bin);
		fclose(arq_login_texto);
		printf("\nAbrindo Excel...\n");
		system(ARQ_LG_CSV);
	}
	mensagemContinuarLogin();
}
// ------------------ Mostrar Dados ------------------
void mostrarDadosLogin(struct tLogin lg){
	printf("\nExibindo dados encontrados...\n");
		exibeLogin(lg.codigo);
		printf("\nUsuario: %s", lg.usuario);
		printf("\nSenha: %d", lg.senha);
		printf("\nNivel: %s", lg.nivel);
}
// ------------------ VALIDACAO DE DADOS ------------------
// Funcao Validar opcao do MENU
int validaOpcaoMenuLogin(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES);
	system("cls");
	return op;
}
// Funcao que valida variaveis do tipo STRING 
void leValidaStringLogin (char *string[]){
	do{
		fflush(stdin);
		gets(string);
		  if(strlen(string)==0){
			printf("\n---->Digite algo:");
		} 		
	} while(strlen(string)==0);
}
//Valida senha
void getsSenhaWallisson(char *string[]){
	int pos;
	
	pos = 0;
	
	do{	
		string[pos] =  getch();
		if(string[pos]!=13)
			printf("*");	
	}while(string[pos++]!=13);

	string[pos-1]='\0';
}

//PROCESSAMENTO LOGIN
int logar(void){
	int achei = 0;
	char user[TAM], password[TAM];
	struct tLogin login;
	FILE *arq_login;
	do{		
		arq_login = fopen(ARQ_LG, "rb");	
		if (arq_login == NULL)	
			mensagemErroLogin();
		else {	
			printf("<<< LOGIN >>>");
			printf("\n>> Usuario: ");
			fflush(stdin);
			leValidaStringLogin (&user);
			printf("\n>> Senha: ");
			fflush(stdin);
			getsSenhaWallisson(&password);
			while(fread(&login, sizeof(login), 1, arq_login))
				if (login.lixo != '*' && strcmp(user, login.usuario) == 0 && strcmp(password, login.senha) == 0){
					achei = 1;
					printf("\n\nAguarde...\n");
					Sleep(2000);
					system("cls");
					return login.nivel;
				}
			if (!achei)
				printf("\nErro: Usuario ou Senha invalidos!\n");
		}		
		fclose(arq_login);
	}while(!achei);	
}
