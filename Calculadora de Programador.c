#include <stdio.h>
#include <stdlib.h> // Para a fun��o exit()
#include <string.h> // Para a fun��o strlen()
#include <ctype.h>  // Para a fun��o tolower()

// Prot�tipos das fun��es (declara��es para que main() saiba que elas existem)
void exibirResultados(long long valor);
long long binarioParaDecimal(const char *strBinario);
void limparBufferEntrada();

int main() {
    int escolha;
    long long valor;
    char entrada[65]; // Buffer para ler a entrada do usu�rio (64 bits + terminador nulo '\0')

    while (1) { // Loop infinito para o menu principal
        printf("\n===== CONVERSOR DE BASES NUMERICAS =====\n");
        printf("Selecione a base do numero de ENTRADA:\n");
        printf("1. Decimal\n");
        printf("2. Binario\n");
        printf("3. Octal\n");
        printf("4. Hexadecimal\n");
        printf("0. Sair\n");
        printf("Sua escolha: ");

        if (scanf("%d", &escolha) != 1) {
            printf("\nERRO: Por favor, digite um numero valido.\n");
            limparBufferEntrada();
            continue; // Volta para o in�cio do loop
        }
        
        limparBufferEntrada(); // Limpa o buffer ap�s ler o n�mero

        switch (escolha) {
            case 1: // Entrada Decimal
                printf("Digite o valor Decimal: ");
                scanf("%lld", &valor);
                limparBufferEntrada();
                exibirResultados(valor);
                break;

            case 2: // Entrada Bin�ria
                printf("Digite o valor Binario: ");
                scanf("%64s", entrada); // L� como uma string com limite de 64 caracteres
                limparBufferEntrada();
                valor = binarioParaDecimal(entrada);
                if (valor != -1) {
                    exibirResultados(valor);
                }
                break;

            case 3: // Entrada Octal
                printf("Digite o valor Octal: ");
                // %llo l� um long long em base octal
                scanf("%llo", &valor);
                limparBufferEntrada();
                exibirResultados(valor);
                break;

            case 4: // Entrada Hexadecimal
                printf("Digite o valor Hexadecimal: ");
                // %llx l� um long long em base hexadecimal
                scanf("%llx", &valor);
                limparBufferEntrada();
                exibirResultados(valor);
                break;

            case 0:
                printf("Encerrando o programa. Ate mais!\n");
                exit(0); // Termina a execu��o

            default:
                printf("\nERRO: Opcao invalida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

/**
 * @brief Exibe um valor em todas as 4 bases (Decimal, Hex, Octal, Bin�rio).
 * @param valor O n�mero a ser convertido (armazenado como um valor decimal).
 */
void exibirResultados(long long valor) {
    printf("\n--- RESULTADOS DA CONVERSAO ---\n");
    
    // 1. Imprime como DECIMAL
    printf("-> Decimal:      %lld\n", valor);

    // 2. Imprime como HEXADECIMAL
    printf("-> Hexadecimal:  %llX\n", valor);

    // 3. Imprime como OCTAL
    printf("-> Octal:        %llo\n", valor);

    // 4. Imprime como BIN�RIO usando nossa fun��o customizada
    printf("-> Binario:      ");
    // L�gica para imprimir em bin�rio
    if (valor == 0) {
        printf("0");
    } else {
        // Itera do bit mais significativo para o menos significativo
        // sizeof(long long) * 8 calcula o total de bits (ex: 8 bytes * 8 = 64 bits)
        int totalBits = sizeof(long long) * 8;
        int encontrouPrimeiroBit = 0; // Para n�o imprimir zeros � esquerda
        int i;
        for (i = totalBits - 1; i >= 0; i--) {
            long long bit = (valor >> i) & 1; // Isola o bit na posi��o 'i'
            if (bit == 1) {
                encontrouPrimeiroBit = 1;
            }
            if (encontrouPrimeiroBit) {
                printf("%lld", bit);
            }
        }
    }
    printf("\n---------------------------------\n");
}

/**
 * @brief Converte uma string contendo um n�mero bin�rio para um valor decimal.
 * @param strBinario A string de '0's e '1's.
 * @return O valor decimal correspondente, ou -1 se a string for inv�lida.
 */
long long binarioParaDecimal(const char *strBinario) {
    long long decimal = 0;
    int tamanho = strlen(strBinario);
    int i;

    for (i = 0; i < tamanho; i++) {
        // Verifica se cada caractere � '0' ou '1'
        if (strBinario[i] != '0' && strBinario[i] != '1') {
            printf("\nERRO: '%s' nao e um numero binario valido.\n", strBinario);
            return -1; // Retorna -1 para indicar um erro
        }
        // L�gica de convers�o
        // decimal = decimal * 2 + (d�gito atual)
        decimal = decimal * 2 + (strBinario[i] - '0');
    }
    return decimal;
}

/**
 * @brief Limpa o buffer de entrada do teclado para evitar erros em leituras futuras.
 * Essencial ap�s ler um n�mero e antes de ler o pr�ximo para remover o '\n' (Enter).
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
