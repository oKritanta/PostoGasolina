#include <stdio.h>
#include <locale.h>

#define RESET "\033[0m"
#define BLACK "\033[30m"              /* Black */
#define RED "\033[31m"                /* Red */
#define GREEN "\033[32m"              /* Green */
#define YELLOW "\033[33m"             /* Yellow */
#define BLUE "\033[34m"               /* Blue */
#define MAGENTA "\033[35m"            /* Magenta */
#define CYAN "\033[36m"               /* Cyan */
#define WHITE "\033[37m"              /* White */
#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */

void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
void limpaTela(void){printf("\e[1;1H\e[2J");}

void esperar(void){
    printf("APERTE ENTER PARA CONTINUAR");
    flush_in();
    limpaTela();
}

void menu(void){
    int opcao = 0;
    while (opcao != 5){
        limpaTela();
        printf("1 - Adicionar um carro na fila;\n");
        printf("2 - Abastecimento;\n");
        printf("3 - Exibir carros na fila de espera;\n");
        printf("4 - Relatórios;\n");
        printf("5 - Encerrar.\n");
        printf("Informe opção:");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }


    }

}
int main() {
    //inicialização
    setlocale(LC_ALL, "Portuguese");
    //vars
    int filaTamanhoMaximo = 0;
    float preco = 0.0;

    printf("\ninforme valor da Gasolina:");
    scanf("%f",&preco);
    printf("informe tamanho maximo da fila:");
    scanf("%d", &filaTamanhoMaximo);

    printf("Autor: João Victor Lima!\n");
    esperar();


    //inicio principal
    menu();
    return 0;
}