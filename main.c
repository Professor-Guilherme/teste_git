// 2021-C-1-aluna-Thais_Eduarda.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>


//struct Produto{
//		char  *nome;
//		float valor;
//	};


#define quantidadedeprodutos 7
char *espacos[quantidadedeprodutos] =
	{
	"", 
	"     ", 
	"       ", 
	"     ", 
	"        ", 
	"        ", 
	""
	};
char *produto[quantidadedeprodutos] = 
	{
	"Misto Quente", 
	"Salgado", 
	"Bolos", 
	"Empadão", 
	"Café", 
	"Água", 
	"Refrigerante"
	};
float valor[quantidadedeprodutos] = { 3.50, 5.50, 6.00, 8.00, 4.00, 2.50, 5.00 };
int   pedido[quantidadedeprodutos] = { 0, 0, 0, 0, 0, 0, 0 };
int   qtd, opcao = -1;

int cls()
{   // limpa a tela no windows, do jeito oficial
    CONSOLE_SCREEN_BUFFER_INFO      info;
    HANDLE      H = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD       origem = { 0,0 };
    DWORD         total;
    if (H == INVALID_HANDLE_VALUE) return -1;
    GetConsoleScreenBufferInfo(H, &info);
    int r = FillConsoleOutputCharacter(H, (TCHAR)' ',
        info.dwSize.X * info.dwSize.Y,
        origem, &total);
    int s = FillConsoleOutputAttribute(
        H, info.wAttributes,
        info.dwSize.X * info.dwSize.Y,
        origem, &total);
    SetConsoleCursorPosition(H, origem);
    return 0;
};  // end cls()

int menu(void){

//	struct Produto produtos;
//	produtos = defineProdutos(quantidadedeprodutos);
	cls();
	
    printf("\t\t\t######################################\n");
    printf("\t\t\t   Bem Vindo à Cafeteria Del Luna\n");
    printf("\t\t\t######################################\n\n");

    printf("\t\t\t********  Menu dos Produtos  *********\n\n");
    printf("\t\t\t######################################\n");

    int i;
//    for (i = 1; i <= quantidadedeprodutos; ++i){
//    	printf("%d- %s: %.2f\n", i, defineProdutos()[i-1].nome, defineProdutos()[i-1].valor);
//	};
	
	for (i = 1; i <= quantidadedeprodutos; ++i){
    	printf("\t\t\t|  %d    |    %s%s     R$%.2f |\n", i, produto[i-1], espacos[i-1], valor[i-1]);
	};
    printf("\t\t\t|-------|----------------------------|\n");
    printf("\t\t\t|  0    |    Para finalizar o pedido |\n");
    printf("\t\t\t######################################\n");
    printf("\n");

	return 0;
}

float resumocompra(){//int pedido[quantidadedeprodutos]){
	float valortotal = 0.0;
	int i;
	for (i = 0; i < quantidadedeprodutos; ++i){
		valortotal += pedido[i] * valor[i];
	}
	printf("\t\t\tO valor da sua compra é: R$%.2f\n\n", valortotal);
	return valortotal;
};

float comprovantecompra(char *Nome){
	cls();
	int i;
    printf("\t\t\t######################################\n");
    printf("\t\t\t          Obrigado por comprar        \n");
    printf("\t\t\t                  na                  \n");
    printf("\t\t\t           Cafeteria Del Luna         \n");
    printf("\t\t\t######################################\n\n");

    printf("\t\t\t***********  Sua Compra  *************\n\n");
    printf("\t\t\t######################################\n");
	float valortotal = resumocompra();
	printf("\t\t\tProduto       Quantidade   Valor total\n");
	for (i=0;i<quantidadedeprodutos;++i){
		if(pedido[i]>0){
			printf("\t\t\t%s%s  %d\t\t   R$%.2f\n", produto[i], espacos[i], pedido[i], valor[i]*pedido[i]);
		};
	};
	printf("\n\t\t\tTOTAL DA COMPRA: R$%.2f\n", valortotal);
	printf("\n\t\t\t\tA senha é: %s\n", Nome);
	
	return valortotal;
}

int solicitapedido(char *Nome, float resultado){
	opcao = -1;
    char c;
	while ((opcao < 0) || (opcao > quantidadedeprodutos))
	    {
	
	        menu();
	        resumocompra();
			if (resultado == 0){
				printf("\t\t\tOlá %s! Por favor, digite o seu pedido: ", Nome);
			}
			else{
				printf("\n\t\t\tDeseja algo mais? (0 para finalizar) ");//caso exista outra escolha pelo usuário.
			};
			scanf_s("%d", &opcao);
			while ((c = getchar()) != '\n' && c != EOF) {};
			
			if((opcao < 0) || (opcao > quantidadedeprodutos)){
				menu();
				printf("\n\n\tOpção inválida. Favor escolher algum item existente no menu...\n\n\n\n");
				system("pause");
			};
			if(opcao == 0){
				return 0;
			};
	    }
	
	printf("\t\t\tDigite a quantidade de %s que você deseja pedir: ", produto[opcao-1]);
    scanf_s("%d", &qtd);
    while ((c = getchar()) != '\n' && c != EOF) {};
    
    pedido[opcao-1] += qtd;
    
	return 0;
}

int salvardados(char *Nome){
	FILE *arquivo; // Cria ponteiro para uso na abertura e uso de arquivos
	FILE *clientes;
	arquivo  = fopen("dados_salvos.txt","a"); // Abre o arquivo e coloca os dados no ponteiro
	clientes = fopen("clientes_salvos.txt","a");
	
	//fwrite(Nome, 1, sizeof(Nome), clientes);
	fwrite(pedido, sizeof(pedido), 1, arquivo); // Salva dado binários de qualquer tipo
	
	fprintf(clientes, "%s\n", Nome);
	
	//fputs(pedido, arquivo); // Para salvar dados de texto de forma fácil
	
	//fprintf(arquivo, "%s, %d\n", Nome, pedido);
	
	/*
	int i;
	fprintf(arquivo, "%s", Nome);
	for(i = 0; i < 6; ++i){
		fprintf(arquivo, "%d", pedido[i]);// Para salvar dados exatamente como eles apareceriam na tela (como ao usarmos o printf)
	}
	fprintf(arquivo, "%d", pedido[6]);
	fprintf(arquivo, "\n");
	
	*/
	
	
	fclose(arquivo); // Fecha o arquivo e libera a memória usada pelo ponteiro.
	return 0;
}

int lerdados(){
	int i;
	FILE *arquivo;
	FILE *clientes;
	if (!(arquivo = fopen("dados_salvos.txt","r"))){
		cls();
		printf("\t\t\tErro na leitura do arquivo de dados salvos!\n");
		system("pause");
		return 1;
	}
	char Nome[50];
	clientes = fopen("clientes_salvos.txt","r");
	fread(&Nome, sizeof(char), 50, clientes);
	fread(&pedido, sizeof(pedido), 1, arquivo);

//	while (!feof(arquivo)){
//		//fgets(pedido, 7, arquivo);//Lê dados de texto do arquivo com comprimento de 7* caracteres no máximo
//		
//		
//		fscanf(arquivo, "%s", &Nome);//Lê dados como se fosse a função scanf(). O tipo de dado precisa ser explicitado.
//		for(i=0;i<6;++i){
//			fscanf(arquivo, "%d", &pedido[i]);
//		};
//		fscanf(arquivo, "%d", &pedido[6]);
//		printf("Dados do arquivo: %s, %d \n", Nome, pedido);
//		
//		
//		//comprovantecompra(Nome);
//		system("pause");
//	};
	
	fclose(arquivo);
	comprovantecompra(Nome);
	printf("\n%d\n", pedido);
	printf("\n%d", pedido[0]);
	printf("\n%d", pedido[1]);
	printf("\n%d", pedido[2]);
	printf("\n%d", pedido[3]);
	printf("\n%d", pedido[4]);
	printf("\n%d", pedido[5]);
	printf("\n%d\n\n", pedido[6]);
	
	system("pause");
	return 0;
}

int main()
{
	//Setando a localidade como a mesma atual do usuário. Isso nos
    setlocale(LC_ALL, "");
    
    //Configuração do console do windows para suportar entradas de texto com acentuação:
    unsigned int novoCp = 1252; //1252 = ANSI latin 1 Windows
    
    //Armazenamento do codepage original do console para reposição da configuração ao final:
    unsigned int cpIn = GetConsoleCP();        //Se usa para saber o codepage de entrada atual
    unsigned int cpOut = GetConsoleOutputCP(); //Se usa para saber o codepage de saída atual
    
    //Estabelecendo o codepage de entrada e saída para 1252(latin1).
    SetConsoleCP(novoCp); 
    SetConsoleOutputCP(novoCp);
    
    //Reset da memória dos pedidos para zero:
	memset(pedido, 0, sizeof(pedido));
	
	float resultado = 0.0;
	
	lerdados();
	
	// Mostra menu inicial e solicita nome do cliente
	menu();
	    
    char Nome[50];

    char c;

    printf("\t\t\tDigite seu nome: ");
    scanf_s("%s", &Nome);
    while ((c = getchar()) != '\n' && c != EOF) {};
    
    putchar('\n');
    
    opcao = -1;

    while (opcao != 0)
    {	
		// Mostra menu inicial e solicita pedidos
		solicitapedido(Nome, resultado);
		
		resultado = resumocompra();
		
        if (opcao == 0) {//para finalizar o codigo.
			menu();
            
			if(resultado != 0){
				printf("\n\t\t\tA senha é: %s\n\n", Nome);
				printf("\t\t\tO valor final da sua compra é: R$%.2f", resultado);
				comprovantecompra(Nome);
				salvardados(Nome);
        	}else{
        		printf("\n\n\t\t\t\tNenhum produto comprado.");
			}
        	printf("\n\n\t\t\t\t    Volte Sempre!\n\n\n");
			break;
        }
        
		

    }

    system("Pause");
    
    //Antes de encerrar o programa, devemos retornar às configurações originais do console:
    //setlocale(LC_ALL, "C");
    SetConsoleCP(cpIn);
    SetConsoleOutputCP(cpOut);
    
    return 0;
}
