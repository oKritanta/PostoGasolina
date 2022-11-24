#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>


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

struct TCarro {
    char cor[30];
    char placa[7];
    char modelo[50];
    float litros;
};


void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
void limpaTela(void){printf("\e[1;1H\e[2J");}

void esperar(void){
    printf("\nAPERTE ENTER PARA CONTINUAR");
    flush_in();
    limpaTela();
}

int main() {
    //inicialização
    setlocale(LC_ALL, "Portuguese");
    //vars
    struct TCarro *atendidos;
    char op2 = 0;
    int opcao = 0;
    int contadorFila = 0;
    int carrosAtendidos = 0;
    int tamanhoVariavelFila = 1;
    int filaTamanhoMaximo = 0;
    float litrosVendidos = 0;
    float vendaEsperando = 0;
    float preco = 0.0;
    float bomba = 200.00;
    struct TCarro *fila;
    printf("\ninforme valor da Gasolina:");
    scanf("%f",&preco);
    printf("informe tamanho maximo da fila:");
    scanf("%d", &filaTamanhoMaximo);
    //aloca espaco na memoria
    fila = (struct TCarro *) malloc(1 * sizeof (struct TCarro));
    atendidos = (struct TCarro *) malloc(1 * sizeof (struct TCarro));

    if (fila == NULL) {
        printf("Erro de alocacao");
        exit(1);
    }

    printf("Autor: João Victor Lima!\n");
    esperar();

    //inicio principal

    while (opcao != 5){
        limpaTela();
        printf("1 - Adicionar um carro na fila;\n");
        printf("2 - Abastecimento;\n");
        printf("3 - Exibir carros na fila de espera;\n");
        printf("4 - Relatórios;\n");
        printf("5 - encher bomba\n");
        printf("6 - Encerrar.\n");
        printf("Informe opção:");

        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                limpaTela();
                if(contadorFila >= filaTamanhoMaximo){
                    printf("Fila Cheia");
                } else {
                    contadorFila++;
                    if(contadorFila > tamanhoVariavelFila){
                        fila = (struct TCarro *) realloc(fila, (contadorFila + 1) * sizeof (struct  TCarro));
                        tamanhoVariavelFila++;
                    }
                    //inicia recolhimento de informacoes
                    printf("informe cor do carro:");
                    flush_in();
                    fgets(fila[contadorFila-1].cor,30,stdin);
                    printf("informe placa do carro:");
                    fgets(fila[contadorFila-1].placa,7,stdin);
                    printf("informe modelo do carro:");
                    fgets(fila[contadorFila-1].modelo,50,stdin);

                    printf("informe quantidade a ser abastecida:");
                    scanf("%f",&fila[contadorFila-1].litros);
                        while (fila[contadorFila-1].litros > (bomba - vendaEsperando) || fila[contadorFila-1].litros <= 0){
                            printf("quantidade informada invalida\n");
                            printf("bomba: %.2f L\n",bomba);
                            printf("fila de espera: %.2f L\n",vendaEsperando);
                            printf("total disponivel %.2f L\n", bomba - vendaEsperando);
                            printf("\ninforme quantidade a ser abastecida:");
                            scanf("%f",&fila[contadorFila-1].litros);
                        }
                        vendaEsperando = vendaEsperando + fila[contadorFila-1].litros;

                    limpaTela();
                    printf("carro adiconado");
                }
                esperar();
                break;
            case 2:
                if(contadorFila <= 0){
                    //caso seja menor
                    contadorFila = 0;
                    printf("Não ha carros na fila de espera");
                } else{
                    if(carrosAtendidos != 0){
                        atendidos = (struct TCarro *) realloc(fila, (carrosAtendidos + 1) * sizeof (struct  TCarro));
                    }
                    strcpy(atendidos[carrosAtendidos].cor , fila[0].cor);
                    strcpy(atendidos[carrosAtendidos].placa , fila[0].placa);
                    strcpy(atendidos[carrosAtendidos].modelo , fila[0].modelo);
                    litrosVendidos = litrosVendidos + fila[0].litros;
                    atendidos[carrosAtendidos].litros = fila[0].litros;
                    bomba = bomba - atendidos[carrosAtendidos].litros;
                    vendaEsperando = vendaEsperando - atendidos[carrosAtendidos].litros;
                    carrosAtendidos++;
                    contadorFila--;
                    //inicia reorganização
                    if(contadorFila > 0){
                        for(int i = 0; i< contadorFila;i++){

                            strcpy(fila[i].cor , fila[i+1].cor);
                            strcpy(fila[i].placa , fila[i+1].placa);
                            strcpy(fila[i].modelo , fila[i+1].modelo);
                            fila[i].litros = fila[i+1].litros;
                        }
                    }
                }
                limpaTela();
                printf("Carro Abastecido");
                flush_in();
                esperar();
                break;
            case 3:
                if(contadorFila == 0){
                    printf("Não há carros na fila");
                } else{
                    limpaTela();
                    for (int i = 0; i < contadorFila; ++i) {
                        printf("carro %d:\n",i+1);
                        printf("cor: %s",fila[i].cor);
                        printf("placa: %s",fila[i].placa);
                        printf("modelo: %s",fila[i].modelo);
                        printf("litros: %.2f",fila[i].litros);
                        printf("\n\n");
                    }
                }
                flush_in();
                esperar();
                break;
            case 4:
                flush_in();
                op2 = 0;
                while (op2 != 'f'){
                    limpaTela();
                    printf("a - Quantidade de litros vendida;\nb - Valor total arrecadado com "
                           "as vendas;\nc - Carros atendidos;\nd - Quantidade "
                           "de "
                           "combustível restante no tanque;\ne - Gerar arquivo para impressão "
                           "(com todas as informações de A, B, C e D);\nf - Voltar ao menu "
                           "anterior.\n");
                    printf("\n");
                    printf("Selecione a opção: ");
                    op2 = getchar();
                    op2 = tolower(op2);
                    limpaTela();
                    switch (op2) {
                        case 'a':
                            printf("Foi vendido: %.2f L",litrosVendidos);
                            break;

                        case 'b':
                            printf("Foi Arrecadado: R$ %.2f",litrosVendidos * preco);
                            break;
                        case 'c':
                            printf("Foi Atentido %d carros",carrosAtendidos);
                            break;
                        case 'd':
                            printf("Resta ainda %f Litros",bomba - litrosVendidos);
                            break;
                        case 'e':
                            printf("Arquivo com relatórios: ");

                            FILE *pont_arq = NULL;
                            pont_arq = fopen("relatorios.txt", "w");
                            if (pont_arq == NULL)
                                printf("Erro ao abrir o arquivo.\n");
                            else {
                                printf("Arquivo criado com sucesso!\n" );
                                fprintf(
                                        pont_arq,
                                        "Total de litros de combustível vendidos: %.2fL\nQuantia total "
                                        "arrecadada com as vendas: R$%.2f\nCarros atendidos: "
                                        "%d\nQuantia de combustível restante no tanque: %.2f",
                                        litrosVendidos, litrosVendidos * preco, carrosAtendidos, bomba - litrosVendidos);
                                int k = 1;
                                while (k <= carrosAtendidos) {
                                    fprintf(pont_arq,"\n\ncarro %d\n\nModelo: %sCor: %sPlaca: %slitros: %.2f\n",
                                            k,
                                            atendidos[k - 1].modelo,
                                            atendidos[k - 1].cor,
                                            atendidos[k - 1].placa,
                                            atendidos[k-1].litros);
                                    k++;
                                }

                                fclose(pont_arq);
                            }
                            pont_arq = fopen("relatorios.txt", "r");
                            break;
                        case 'f':
                            printf("voltando...");
                            break;
                        default:
                            printf("opção invalida");
                            break;
                    }
                    flush_in();
                    esperar();

                }

                break;
            case 5:
                bomba = 200;
                printf("bomba reenchida");
                break;
            case 6:
                printf("Saindo...");
                return 0;
                break;
            default:
                printf("Opção invalida, tente novamente");
                break;
        }


    }
    return 0;
}