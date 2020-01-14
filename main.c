/* 
	Projeto final de sistema de venda de ingressos para a disciplina de Programação Estruturada da UCB em 2019/1
	Profº.: Edson Francisco da Fonseca
	Alunos:	Gustavo Ribeiro dos Santos - UC18100150
			Wallisson Eduardo L. Duarte - UC18200742
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <locale.h>
#include "libFuncoes.c"
#include "conio2.c"

#define OPCOES_MENU 6

void exibeMenu(int);
int validaOpcaoMenu(void);


int main(void){
	setlocale(LC_ALL, "Portuguese");
	int codigo;
	int opcao;
	int acesso;
	
	struct tEvento evento;
	struct tLogin login;
	
	acesso = logar();
	
	switch(acesso){
		case 1: 
			do{
				textbackground(3); // cyan
			    _setcursortype(0); 
			    textcolor(0);  // black
				exibeMenu(1);
				opcao = validaOpcaoMenu();		
				switch(opcao){
					case 1:
						principalLogin();				
						
						break;
					case 2:
						principalAtracao();						
						
						break;	
					case 3:
						principalLocal();						
						
						break;		
					case 4:
						principalEvento();
						break;
					case 5:
						principalCliente();							
						break;	
					case 6:
						principalVenda();
						break;	
				}		
			} while (opcao!=0);
			break;
		case 2:	
			do{
				exibeMenu(2);
				opcao = validaOpcaoMenu();		
				switch(opcao){
					case 1:
						printf("Cadastro de Logins\n\n");
						login.codigo = incrementaCodigoLogin();
						recebeDadosLogin(&login);
						cadastraLogin(login);						
						
						break;
					case 2:
						principalAtracao();						
						
						break;	
					case 3:
						principalLocal();						
						
						break;		
					case 4:
						principalEvento();
						break;
					case 5:
						principalCliente();
					
						break;	
					case 6:
						principalVenda();
						break;	
				}		
			} while (opcao!=0);
			break;
		case 3:	
			do{
				exibeMenu(3);
				opcao = validaOpcaoMenu();		
				switch(opcao){	
					case 4:
						principalLocal();
						break;
					case 5:
						principalVenda();
						break;	
					case 6:
						printf("Cadastro de Logins\n\n");
						login.codigo = incrementaCodigoLogin();
						recebeDadosLogin(&login);
						cadastraLogin(login);
						break;	
				}		
			} while (opcao!=0);
			break;	
	}
	return 0;
}
void exibeMenu(int nvl){
	printf("\n  ..:: MENUS ::..\n\n");
	switch(nvl){
		case 1: 
			printf("  1. GERENCIAR ACESSO\n");
			printf("  2. ATRAÇÃO\n");
			printf("  3. LOCAL\n");
			printf("  4. EVENTO\n");	
			break;
		case 2:
			printf("  1. CADASTRAR LOGIN\n");
			printf("  2. ATRAÇÃO\n");
			printf("  3. LOCAL\n");
			printf("  4. EVENTO\n");	
			break;
		case 3:
			printf("  4. EVENTOS\n");
			break;
	}				
	printf("  5. CLIENTE\n");
	printf("  6. VENDA DE INGRESSO\n");			
	printf("  0. SAIR\n");
	printf("\n\n  Escolha um menu: ");
}
int validaOpcaoMenu(void){
	int op;
	do{
		scanf("%d", &op);
		if(op<0 || op>OPCOES_MENU)
			printf("\nOpcao invalida! \nDigite novamente: ");	
	}while(op<0 || op>OPCOES_MENU);
	system("cls");
	return op;
}
