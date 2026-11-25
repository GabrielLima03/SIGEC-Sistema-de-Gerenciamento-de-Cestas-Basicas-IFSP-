# SIGEC

**Sistema de Gerenciamento de Cestas Básicas**

SIGEC é uma aplicação de console desenvolvida em linguagem C para
auxiliar no cadastro de famílias, no registro de distribuição de cestas
básicas e no controle de estoque. O projeto utiliza arquivos de texto
(`.txt`) para armazenar os dados.

## Objetivo

Organizar informações de famílias atendidas e manter registros das
distribuições realizadas, permitindo consultar cadastros, acompanhar o
histórico e controlar a quantidade de cestas disponíveis.

## Funcionalidades

### 1. Cadastro de famílias

-   Cadastrar nome do responsável, endereço, telefone e quantidade de
    pessoas da família.
-   Utilizar o telefone como identificador da família.
-   Validar o telefone informado.
-   Impedir o cadastro de telefones duplicados.
-   Consultar os cadastros armazenados.

### 2. Registro de distribuição

-   Localizar uma família pelo telefone cadastrado.
-   Registrar a quantidade de cestas entregues.
-   Registrar automaticamente a data atual.
-   Salvar os dados da distribuição.
-   Consultar o histórico geral de distribuições.
-   Consultar o histórico de uma família específica.

### 3. Controle de estoque

-   Adicionar cestas ao estoque.
-   Retirar cestas do estoque, verificando se há quantidade suficiente.
-   Consultar a quantidade atual disponível.
-   Salvar o estoque para manter o valor entre execuções.

## Arquivos de dados

O programa cria ou utiliza os seguintes arquivos de texto na pasta de
execução:

  Arquivo               Conteúdo
  --------------------- ---------------------------------------
  `familias.txt`        Cadastros das famílias
  `distribuicoes.txt`   Registros de distribuição
  `estoque.txt`         Quantidade atual de cestas no estoque

Os arquivos são utilizados pelo próprio programa. Não é necessário
configurar um banco de dados.

## Tecnologias e conceitos utilizados

-   Linguagem C
-   Code::Blocks
-   Aplicação de console
-   Estruturas (`struct`)
-   Vetores
-   Funções e protótipos
-   Estruturas condicionais (`if`, `else`, `switch`)
-   Estruturas de repetição (`do...while`, `for`, `while`)
-   Manipulação de arquivos (`fopen`, `fprintf`, `fscanf`, `fgets`,
    `fclose`)
-   Manipulação de strings
-   Validação de dados
-   Data e hora (`time`, `localtime`, `strftime`)

## Organização do programa

O código é dividido em módulos de funções:

-   **Menu principal:** direciona o usuário para os módulos do sistema.
-   **Cadastro de famílias:** cadastra e consulta famílias.
-   **Busca de família:** localiza um cadastro pelo telefone.
-   **Distribuição:** registra e consulta entregas de cestas.
-   **Estoque:** adiciona, retira e exibe a quantidade de cestas.
-   **Funções auxiliares:** validam quantidade, telefone e DDD.

## Como executar

1.  Abra o projeto no Code::Blocks.
2.  Crie ou abra o arquivo de código-fonte C do SIGEC.
3.  Compile o programa.
4.  Execute a aplicação.
5.  Utilize as opções exibidas no menu principal.

> O programa utiliza os comandos `system("cls")` e `system("pause")`,
> destinados ao ambiente Windows.

## Observação sobre o estoque

O módulo de estoque permite adicionar e retirar cestas e salva a
quantidade em `estoque.txt`. No código atual, o registro de uma
distribuição e a retirada de cestas do estoque são operações separadas.
Portanto, registrar uma distribuição não reduz automaticamente o
estoque.

## Projeto acadêmico

Projeto de Extensão / Interdisciplinar 

O SIGEC foi desenvolvido como protótipo acadêmico para demonstrar
conceitos fundamentais de programação em C aplicados a uma necessidade
comunitária.
