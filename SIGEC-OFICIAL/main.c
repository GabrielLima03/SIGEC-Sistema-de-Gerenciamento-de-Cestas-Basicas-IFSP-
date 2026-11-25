#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

//---------------------------------------------------------------------------------------------------------------
// ESTRUTURAS
//---------------------------------------------------------------------------------------------------------------

typedef struct
{
    char nome[50];
    char endereco[100];
    char telefone[12];
    int pessoas;

} Familia;


typedef struct
{
    Familia familia;
    int quantidadeCestas;
    char data[20];

} Distribuicao;


//---------------------------------------------------------------------------------------------------------------
// PROTOTIPOS DAS FUNCOES
//---------------------------------------------------------------------------------------------------------------

// MENU PRINCIPAL E FAMILIAS
void menuFamilias();
void cadastrarFamilia();
void consultarFamilias();

// MENU DE DISTRIBUICAO
void menuDistribuicao();
void registrarDistribuicao();
void consultarHistorico();
void historicoFamilia();

// MENU DE ESTOQUE
void menuEstoque();
void adicionarEstoque();
void removerEstoque();
void mostrarEstoque();
int carregarEstoque(void);
int salvarEstoque(int quantidade);

// FUNCOES AUXILIARES
int buscarFamilia(char telefone[], Familia *familia);
int validarQuantidade(int quantidade);
int telefoneValido(char telefone[]);
int dddValido(int ddd);


//---------------------------------------------------------------------------------------------------------------
// PROGRAMA
//---------------------------------------------------------------------------------------------------------------

int main()
{
    setlocale(LC_ALL, "");

    char sair = 'N';
    int opcao;
    int resultado;

    do
    {
        system("cls");

        printf("=================================\n");
        printf("|  ========== SIGEC ==========  |\n");
        printf("|                               |\n");
        printf("| 1 - Cadastro de Familias      |\n");
        printf("| 2 - Registro de Distribuição  |\n");
        printf("| 3 - Estoque                   |\n");
        printf("| 4 - Sair                      |\n");
        printf("=================================");

        printf("\nEscolha uma Opção: ");
        resultado = scanf("%d", &opcao);

        // Limpa os caracteres restantes da entrada
        while(getchar() != '\n');

        if(resultado != 1)
        {
            opcao = -1;
        }

        switch(opcao)
        {
        case 1:
            menuFamilias();
            break;

        case 2:
            menuDistribuicao();
            break;

        case 3:
            menuEstoque();
            break;

        case 4:
            system("cls");

            do
            {
                printf("Deseja mesmo sair (S/N): ");
                scanf(" %c", &sair);

                while(getchar() != '\n');

                sair = toupper((unsigned char)sair);

                if(sair != 'S' && sair != 'N')
                {
                    printf("\nOpção invalida! Digite S ou N.\n");
                }

            }
            while(sair != 'S' && sair != 'N');

            break;

        default:
            printf("\nOpção Invalida!!!\n");
            system("pause");
            break;
        }

    }
    while(opcao != 4 || sair != 'S');

    printf("\nFim da Execução!!!\n");

    return 0;
}


//---------------------------------------------------------------------------------------------------------------
// MENU DE CADASTRO DE FAMILIAS
//---------------------------------------------------------------------------------------------------------------

void menuFamilias()
{
    int opcao;
    int resultado;

    do
    {
        system("cls");

        printf("====== CADASTRO DE FAMILIAS ======\n");
        printf("1 - Cadastrar Familia\n");
        printf("2 - Consultar Familias\n");
        printf("0 - Voltar ao Menu Principal\n");

        printf("\nEscolha uma Opção: ");
        resultado = scanf("%d", &opcao);
        while(getchar() != '\n');

        if(resultado != 1)
        {
            opcao = -1;
        }

        switch(opcao)
        {
        case 1:
            cadastrarFamilia();
            break;

        case 2:
            consultarFamilias();
            break;

        case 0:
            break;

        default:
            printf("\nOpção Invalida!\n");
            system("pause");
            break;
        }

    }
    while(opcao != 0);
}


//---------------------------------------------------------------------------------------------------------------
// CADASTRAR FAMILIA
//---------------------------------------------------------------------------------------------------------------

void cadastrarFamilia()
{
    Familia familia;
    Familia existente;
    char continuar;
    char telefoneDigitado[100];
    int valido;
    int resultado;
    int i;

    FILE *arquivo;

    do
    {
        system("cls");

        printf("====== NOVO CADASTRO ======\n");

        printf("\nNome do responsavel: ");
        scanf(" %49[^\n]", familia.nome);
        while(getchar() != '\n');

        printf("Endereco: ");
        scanf(" %99[^\n]", familia.endereco);
        while(getchar() != '\n');

        // Le e valida o telefone
        do
        {
            valido = 1;

            printf("Telefone (11 digitos): ");
            scanf(" %99[^\n]", telefoneDigitado);
            while(getchar() != '\n');

            if(strlen(telefoneDigitado) != 11)
            {
                valido = 0;
            }
            else
            {
                for(i = 0; i < 11; i++)
                {
                    if(!isdigit((unsigned char)telefoneDigitado[i]))
                    {
                        valido = 0;
                        break;
                    }
                }
            }

            if(!valido)
            {
                printf("\nERRO: O telefone deve possuir 11 digitos numericos!\n");
            }
            else if(!telefoneValido(telefoneDigitado))
            {
                // Tinha 11 digitos, mas nao e um celular valido
                valido = 0;
                printf("\nERRO: Telefone invalido! Use um DDD valido e o numero comecando com 9.\n");
            }
            else if(buscarFamilia(telefoneDigitado, &existente))
            {
                // Ja existe uma familia com esse telefone
                valido = 0;
                printf("\nERRO: Telefone ja cadastrado!\n");
            }

        }
        while(!valido);

        strcpy(familia.telefone, telefoneDigitado);

        // Le e valida a quantidade de pessoas
        do
        {
            printf("Quantidade de pessoas: ");
            resultado = scanf("%d", &familia.pessoas);
            while(getchar() != '\n');

            if(resultado != 1 || !validarQuantidade(familia.pessoas))
            {
                printf("\nERRO: Informe uma quantidade maior que zero!\n");
            }

        }
        while(resultado != 1 || !validarQuantidade(familia.pessoas));

        // Abre o arquivo para adicionar o cadastro ao final
        arquivo = fopen("familias.txt", "a");

        if(arquivo == NULL)
        {
            printf("\nErro ao salvar cadastro!\n");
            system("pause");
            return;
        }

        // Grava os dados da familia no arquivo
        fprintf(arquivo, "Nome: %s\n", familia.nome);
        fprintf(arquivo, "Endereco: %s\n", familia.endereco);
        fprintf(arquivo, "Telefone: %s\n", familia.telefone);
        fprintf(arquivo, "Pessoas: %d\n", familia.pessoas);
        fprintf(arquivo, "------------------------\n");

        fclose(arquivo);

        printf("\nFamilia cadastrada com sucesso!\n");

        printf("\nDeseja cadastrar outra familia? (S/N): ");
        scanf(" %c", &continuar);
        while(getchar() != '\n');

        continuar = toupper((unsigned char)continuar);

    }
    while(continuar == 'S');

    printf("\nCadastros finalizados!\n");
    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// CONSULTAR FAMILIAS
//---------------------------------------------------------------------------------------------------------------

void consultarFamilias()
{
    char linha[150];
    int encontrou = 0;

    FILE *arquivo;

    system("cls");

    arquivo = fopen("familias.txt", "r");

    if(arquivo == NULL)
    {
        printf("Nenhuma familia cadastrada!\n");
    }
    else
    {
        printf("====== FAMILIAS CADASTRADAS ======\n\n");

        while(fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            printf("%s", linha);
            encontrou = 1;
        }

        if(!encontrou)
        {
            printf("Nenhum cadastro encontrado!\n");
        }

        fclose(arquivo);
    }

    printf("\n");
    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// BUSCAR FAMILIA PELO TELEFONE
//---------------------------------------------------------------------------------------------------------------

// Retorna 1 se encontrar a familia e 0 se nao encontrar.
int buscarFamilia(char telefone[], Familia *familia)
{
    FILE *arquivo;
    char linha[150];

    Familia familiaAtual;

    familiaAtual.nome[0] = '\0';
    familiaAtual.endereco[0] = '\0';
    familiaAtual.telefone[0] = '\0';
    familiaAtual.pessoas = 0;

    arquivo = fopen("familias.txt", "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if(sscanf(linha, "Nome: %49[^\n]", familiaAtual.nome) == 1)
        {
            continue;
        }

        if(sscanf(linha, "Endereco: %99[^\n]", familiaAtual.endereco) == 1)
        {
            continue;
        }

        if(sscanf(linha, "Telefone: %11s", familiaAtual.telefone) == 1)
        {
            continue;
        }

        if(sscanf(linha, "Pessoas: %d", &familiaAtual.pessoas) == 1)
        {
            continue;
        }

        // Identifica o final do cadastro
        if(linha[0] == '-')
        {
            if(strcmp(telefone, familiaAtual.telefone) == 0)
            {
                *familia = familiaAtual;

                fclose(arquivo);

                return 1;
            }

            // Limpa os dados para ler a proxima familia
            familiaAtual.nome[0] = '\0';
            familiaAtual.endereco[0] = '\0';
            familiaAtual.telefone[0] = '\0';
            familiaAtual.pessoas = 0;
        }
    }

    fclose(arquivo);

    return 0;
}


//---------------------------------------------------------------------------------------------------------------
// MENU DE DISTRIBUICAO
//---------------------------------------------------------------------------------------------------------------

void menuDistribuicao()
{
    int opcao;
    int resultado;

    do
    {
        system("cls");

        printf("====== REGISTRO DE DISTRIBUIÇÃO ======\n");
        printf("1 - Registrar Distribuição\n");
        printf("2 - Consultar Historico Geral\n");
        printf("3 - Consultar Historico por Familia\n");
        printf("0 - Voltar ao Menu Principal\n");

        printf("\nEscolha uma Opção: ");
        resultado = scanf("%d", &opcao);
        while(getchar() != '\n');

        if(resultado != 1)
        {
            opcao = -1;
        }

        switch(opcao)
        {
        case 1:
            registrarDistribuicao();
            break;

        case 2:
            consultarHistorico();
            break;

        case 3:
            historicoFamilia();
            break;

        case 0:
            break;

        default:
            printf("\nOpção Invalida!\n");
            system("pause");
            break;
        }

    }
    while(opcao != 0);
}


//---------------------------------------------------------------------------------------------------------------
// REGISTRAR DISTRIBUICAO
//---------------------------------------------------------------------------------------------------------------

void registrarDistribuicao()
{
    char telefone[12];
    char telefoneDigitado[100];

    Distribuicao distribuicao;

    int valido;
    int resultado;
    int i;

    FILE *arquivo;

    time_t agora;
    struct tm *dataAtual;

    system("cls");

    printf("====== REGISTRO DE DISTRIBUIÇÃO ======\n\n");

    // Le e valida o telefone do responsavel
    do
    {
        valido = 1;

        printf("Telefone do responsavel (11 digitos): ");
        scanf(" %99[^\n]", telefoneDigitado);

        while(getchar() != '\n');

        if(strlen(telefoneDigitado) != 11)
        {
            valido = 0;
        }
        else
        {
            for(i = 0; i < 11; i++)
            {
                if(!isdigit((unsigned char)telefoneDigitado[i]))
                {
                    valido = 0;
                    break;
                }
            }
        }

        if(!valido)
        {
            printf("\nERRO: O telefone deve possuir 11 digitos numericos!\n");
        }

    }
    while(!valido);

    strcpy(telefone, telefoneDigitado);

    // Busca a familia cadastrada
    if(!buscarFamilia(telefone, &distribuicao.familia))
    {
        printf("\nFamilia não encontrada!\n");
        system("pause");
        return;
    }

    // Exibe os dados da familia encontrada
    printf("\n====== FAMILIA ENCONTRADA ======\n");
    printf("Responsavel: %s\n", distribuicao.familia.nome);
    printf("Telefone: %s\n", distribuicao.familia.telefone);
    printf("Endereço: %s\n", distribuicao.familia.endereco);
    printf("Quantidade de pessoas: %d\n", distribuicao.familia.pessoas);

    // Le e valida a quantidade de cestas entregues
    do
    {
        printf("\nQuantidade de cestas entregues: ");
        resultado = scanf("%d", &distribuicao.quantidadeCestas);
        while(getchar() != '\n');

        if(resultado != 1 || !validarQuantidade(distribuicao.quantidadeCestas))
        {
            printf("\nQuantidade inválida! Informe um valor maior que zero.\n");
        }

    }
    while(resultado != 1 || !validarQuantidade(distribuicao.quantidadeCestas));

    // Captura a data atual
    agora = time(NULL);
    dataAtual = localtime(&agora);

    if(dataAtual == NULL)
    {
        printf("\nErro ao obter a data!\n");
        system("pause");
        return;
    }

    strftime(distribuicao.data, 20, "%d/%m/%Y", dataAtual);

    // Abre o arquivo para adicionar a distribuicao
    arquivo = fopen("distribuicoes.txt", "a");

    if(arquivo == NULL)
    {
        printf("\nErro ao salvar distribuição!\n");
        system("pause");
        return;
    }

    // Grava os dados da distribuicao no arquivo
    fprintf(arquivo, "Responsavel: %s\n", distribuicao.familia.nome);
    fprintf(arquivo, "Telefone: %s\n", distribuicao.familia.telefone);
    fprintf(arquivo, "Endereço: %s\n", distribuicao.familia.endereco);
    fprintf(arquivo, "Pessoas: %d\n", distribuicao.familia.pessoas);
    fprintf(arquivo, "Quantidade de cestas: %d\n", distribuicao.quantidadeCestas);
    fprintf(arquivo, "Data: %s\n", distribuicao.data);
    fprintf(arquivo, "================================\n");

    fclose(arquivo);

    printf("\nDistribuição registrada com sucesso!\n");
    printf("Data: %s\n", distribuicao.data);

    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// CONSULTAR HISTORICO GERAL
//---------------------------------------------------------------------------------------------------------------

void consultarHistorico()
{
    char linha[150];
    int encontrou = 0;

    FILE *arquivo;

    system("cls");

    printf("====== HISTÓRICO DE DISTRIBUIÇÕES ======\n\n");

    arquivo = fopen("distribuicoes.txt", "r");

    if(arquivo == NULL)
    {
        printf("Nenhuma distribuição registrada!\n");
    }
    else
    {
        while(fgets(linha, sizeof(linha), arquivo) != NULL)
        {
            printf("%s", linha);
            encontrou = 1;
        }

        if(!encontrou)
        {
            printf("Nenhum registro encontrado!\n");
        }

        fclose(arquivo);
    }

    printf("\n");
    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// HISTORICO POR FAMILIA
//---------------------------------------------------------------------------------------------------------------

void historicoFamilia()
{
    char telefone[12];
    char telefoneDigitado[100];
    char linha[150];
    char telefoneArquivo[12];
    char registro[700];

    Familia familia;

    int encontrou = 0;
    int corresponde = 0;
    int valido;
    int i;

    FILE *arquivo;

    system("cls");

    printf("====== HISTÓRICO POR FAMÍLIA ======\n\n");

    // Le e valida o telefone do responsavel
    do
    {
        valido = 1;

        printf("Telefone do responsável (11 digitos): ");
        scanf(" %99[^\n]", telefoneDigitado);
        while(getchar() != '\n');

        if(strlen(telefoneDigitado) != 11)
        {
            valido = 0;
        }
        else
        {
            for(i = 0; i < 11; i++)
            {
                if(!isdigit((unsigned char)telefoneDigitado[i]))
                {
                    valido = 0;
                    break;
                }
            }
        }

        if(!valido)
        {
            printf("\nERRO: O telefone deve possuir 11 digitos numericos!\n");
        }

    }
    while(!valido);

    strcpy(telefone, telefoneDigitado);

    // Verifica se a familia esta cadastrada
    if(!buscarFamilia(telefone, &familia))
    {
        printf("\nFamilia não encontrada!\n");
        system("pause");
        return;
    }

    // Abre o arquivo de distribuicoes
    arquivo = fopen("distribuicoes.txt", "r");

    if(arquivo == NULL)
    {
        printf("\nNenhuma distribuição registrada!\n");
        system("pause");
        return;
    }

    printf("\nResponsavel: %s\n", familia.nome);
    printf("====== DISTRIBUIÇÕES REALIZADAS ======\n\n");

    registro[0] = '\0';

    // Percorre os registros do historico
    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        // Verifica o telefone do registro atual
        if(sscanf(linha, "Telefone: %11s", telefoneArquivo) == 1)
        {
            if(strcmp(telefone, telefoneArquivo) == 0)
            {
                corresponde = 1;
            }
        }

        // Guarda as informacoes do registro
        if(linha[0] != '=')
        {
            strncat(registro, linha, sizeof(registro) - strlen(registro) - 1);
        }

        // Identifica o final do registro
        if(linha[0] == '=')
        {
            if(corresponde)
            {
                printf("%s", registro);
                printf("================================\n\n");

                encontrou = 1;
            }

            registro[0] = '\0';
            corresponde = 0;
        }
    }

    fclose(arquivo);

    if(!encontrou)
    {
        printf("Essa familia ainda nao possui distribuições!\n");
    }

    printf("\n");
    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// MENU DE ESTOQUE
//---------------------------------------------------------------------------------------------------------------

void menuEstoque()
{
    int opcao;
    int resultado;

    do
    {
        system("cls");

        printf("====== CONTROLE DE ESTOQUE ======\n");
        printf("1 - Adicionar Cestas ao Estoque\n");
        printf("2 - Retirar Cestas do Estoque\n");
        printf("3 - Mostrar Estoque Atual\n");
        printf("0 - Voltar ao Menu Principal\n");

        printf("\nEscolha uma Opção: ");
        resultado = scanf("%d", &opcao);
        while(getchar() != '\n');

        if(resultado != 1)
        {
            opcao = -1;
        }

        switch(opcao)
        {
        case 1:
            adicionarEstoque();
            break;

        case 2:
            removerEstoque();
            break;

        case 3:
            mostrarEstoque();
            break;

        case 0:
            break;

        default:
            printf("\nOpcao invalida!\n");
            system("pause");
            break;
        }

    }
    while(opcao != 0);
}


//---------------------------------------------------------------------------------------------------------------
// ADICIONAR CESTAS AO ESTOQUE
//---------------------------------------------------------------------------------------------------------------

void adicionarEstoque()
{
    int estoque;
    int quantidade;
    int resultado;

    system("cls");

    printf("====== ADICIONAR AO ESTOQUE ======\n\n");

    estoque = carregarEstoque();

    printf("Estoque atual: %d cesta(s)\n", estoque);

    do
    {
        printf("Quantidade de cestas para adicionar: ");
        resultado = scanf("%d", &quantidade);
        while(getchar() != '\n');

        if(resultado != 1 || !validarQuantidade(quantidade))
        {
            printf("\nQuantidade invalida! Informe um valor maior que zero.\n");
        }

    }
    while(resultado != 1 || !validarQuantidade(quantidade));

    estoque = estoque + quantidade;

    if(salvarEstoque(estoque))
    {
        printf("\nEstoque atualizado com sucesso!\n");
        printf("Estoque atual: %d cesta(s)\n", estoque);
    }
    else
    {
        printf("\nErro ao salvar o estoque!\n");
    }

    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// RETIRAR CESTAS DO ESTOQUE
//---------------------------------------------------------------------------------------------------------------

void removerEstoque()
{
    int estoque;
    int quantidade;
    int resultado;

    system("cls");

    printf("====== RETIRAR DO ESTOQUE ======\n\n");

    estoque = carregarEstoque();

    printf("Estoque atual: %d cesta(s)\n", estoque);

    if(estoque == 0)
    {
        printf("\nNao ha cestas disponiveis no estoque!\n");
        system("pause");
        return;
    }

    do
    {
        printf("Quantidade de cestas para retirar: ");
        resultado = scanf("%d", &quantidade);
        while(getchar() != '\n');

        if(resultado != 1 || !validarQuantidade(quantidade))
        {
            printf("\nQuantidade invalida! Informe um valor maior que zero.\n");
        }
        else if(quantidade > estoque)
        {
            printf("\nQuantidade maior que o estoque disponivel!\n");
        }

    }
    while(resultado != 1 || !validarQuantidade(quantidade) || quantidade > estoque);

    estoque = estoque - quantidade;

    if(salvarEstoque(estoque))
    {
        printf("\nRetirada realizada com sucesso!\n");
        printf("Estoque atual: %d cesta(s)\n", estoque);
    }
    else
    {
        printf("\nErro ao salvar o estoque!\n");
    }

    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// MOSTRAR ESTOQUE ATUAL
//---------------------------------------------------------------------------------------------------------------

void mostrarEstoque()
{
    int estoque;

    system("cls");

    printf("====== ESTOQUE ATUAL ======\n\n");

    estoque = carregarEstoque();

    printf("Quantidade de cestas disponiveis: %d\n", estoque);

    system("pause");
}


//---------------------------------------------------------------------------------------------------------------
// CARREGAR ESTOQUE DO ARQUIVO
//---------------------------------------------------------------------------------------------------------------

int carregarEstoque(void)
{
    FILE *arquivo;
    int estoque = 0;

    arquivo = fopen("estoque.txt", "r");

    if(arquivo == NULL)
    {
        return 0;
    }

    if(fscanf(arquivo, "%d", &estoque) != 1 || estoque < 0)
    {
        estoque = 0;
    }

    fclose(arquivo);

    return estoque;
}


//---------------------------------------------------------------------------------------------------------------
// SALVAR ESTOQUE NO ARQUIVO
//---------------------------------------------------------------------------------------------------------------

int salvarEstoque(int quantidade)
{
    FILE *arquivo;

    arquivo = fopen("estoque.txt", "w");

    if(arquivo == NULL)
    {
        return 0;
    }

    fprintf(arquivo, "%d\n", quantidade);

    fclose(arquivo);

    return 1;
}


//---------------------------------------------------------------------------------------------------------------
// VALIDAR QUANTIDADE
//---------------------------------------------------------------------------------------------------------------

// Recebe um inteiro por valor e retorna 1 se for valido ou 0 se for invalido.
int validarQuantidade(int quantidade)
{
    if(quantidade > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//---------------------------------------------------------------------------------------------------------------
// VALIDAR TELEFONE
//---------------------------------------------------------------------------------------------------------------

// Recebe um telefone com 11 digitos numericos e retorna 1 se for um celular valido ou 0 se for invalido.
// Regras: DDD existente, terceiro digito igual a 9 e nao pode ter todos os digitos iguais.
int telefoneValido(char telefone[])
{
    int i;
    int ddd;
    int todosIguais = 1;

    // Transforma os dois primeiros caracteres em numero (ex.: '1' e '1' viram 11)
    ddd = (telefone[0] - '0') * 10 + (telefone[1] - '0');

    if(!dddValido(ddd))
    {
        return 0;
    }

    // Celular tem o digito 9 logo depois do DDD
    if(telefone[2] != '9')
    {
        return 0;
    }

    // Se algum digito for diferente do primeiro, os digitos nao sao todos iguais
    for(i = 1; i < 11; i++)
    {
        if(telefone[i] != telefone[0])
        {
            todosIguais = 0;
        }
    }

    if(todosIguais)
    {
        return 0;
    }

    return 1;
}


// Recebe um DDD e retorna 1 se ele existe no Brasil ou 0 se nao existe.
int dddValido(int ddd)
{
    int dddsValidos[] = {11, 12, 13, 14, 15, 16, 17, 18, 19,
                         21, 22, 24, 27, 28,
                         31, 32, 33, 34, 35, 37, 38,
                         41, 42, 43, 44, 45, 46, 47, 48, 49,
                         51, 53, 54, 55,
                         61, 62, 63, 64, 65, 66, 67, 68, 69,
                         71, 73, 74, 75, 77, 79,
                         81, 82, 83, 84, 85, 86, 87, 88, 89,
                         91, 92, 93, 94, 95, 96, 97, 98, 99};

    int quantidade = sizeof(dddsValidos) / sizeof(dddsValidos[0]);
    int i;

    for(i = 0; i < quantidade; i++)
    {
        if(dddsValidos[i] == ddd)
        {
            return 1;
        }
    }

    return 0;
}
