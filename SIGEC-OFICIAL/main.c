#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

int main()
{

   setlocale(LC_ALL, "");

    char sair;
    int opcao, executando = 1;

    executando = 1;

    do
    {
        system("cls");
        printf("Menu Opções\n");
        printf("1 - Cadastro Famílias\n");
        printf("2 - Registro de Distribuição\n");
        printf("3 - Estoque\n");
        printf("4 - Sair\n");


        printf("\nEscolha uma Opção: ");
        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                system("cls");
                printf("1 - Cadastro Famílias\n");
                system("pause");
                break;

            case 2:
                system("cls");
                printf("2 - Registro de Distribuição\n");
                system("pause");
                break;

            case 3:
                system("cls");
                printf("3 - Estoque\n");
                system("pause");
                break;

            case 4:

                system("cls");
                printf("3 - Sair\n");
                printf("Deseja mesmo sair (s/n): ");
                scanf(" %c", &sair);
                if(toupper(sair) == 'S')
                {
                    executando = 0;
                }

                break;

            default:
                system("cls");
                printf("\nOpção Inválida!!!\n");
                system("pause");
        }

    }
    while(executando);

    printf("\nFim da Execução!!!\n");

    return 0;
}
