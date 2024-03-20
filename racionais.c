#include "racionais.h"
/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/

#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

// Função para gerar um número aleatório entre min e max
int aleat(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Função para calcular o Máximo Divisor Comum entre dois números usando o algoritmo de Euclides
int mdc(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Função para calcular o Mínimo Múltiplo Comum entre dois números
int mmc(int a, int b) {
    return (a * b) / mdc(a, b);
}

// Função para simplificar um número racional
struct racional simplifica_r(struct racional r) {
    // Calcula o MDC entre o numerador e o denominador
    int m = mdc(abs(r.num), abs(r.den));
    // Simplifica dividindo o numerador e o denominador pelo MDC
    r.num /= m;
    r.den /= m;
    // Se o denominador for negativo, transfere o sinal para o numerador
    if (r.den < 0) {
        r.num *= -1;
        r.den *= -1;
    }
    return r;
}

// Função para criar um número racional com base no numerador e denominador fornecidos
struct racional cria_r(int numerador, int denominador) {
    struct racional r;
    // Define se o número racional é válido ou inválido (quando o denominador é zero)
    r.valido = (denominador != 0);
    r.num = numerador;
    r.den = denominador;
    return simplifica_r(r); // Chama a função para simplificar o número racional
}

// Função para sortear um número racional na forma simplificada
struct racional sorteia_r(int n) {
    // Gera um numerador aleatório entre 0 e n
    int num = aleat(0, n);
    // Gera um denominador aleatório entre 1 e n (evita denominador zero)
    int den = aleat(1, n);
    return cria_r(num, den); // Chama a função para criar o número racional
}

// Função para imprimir um número racional
void imprime_r(struct racional r) {
    if (!valido_r(r)) { // Verifica se o número racional é inválido
        printf("INVALIDO");
        return;
    }
    // Imprime o número racional de acordo com as especificações fornecidas no cabeçalho
    if (r.num == 0) {
        printf("0");
    } else if (r.den == 1) {
        printf("%d", r.num);
    } else if (abs(r.num) == abs(r.den)) {
        printf("1");
    } else {
        printf("%d/%d", r.num, r.den);
    }
}

// Função para verificar se um número racional é válido
int valido_r(struct racional r) {
    return r.valido; // Retorna 1 se o número racional é válido e 0 caso contrário
}

// Função para calcular a soma de dois números racionais
struct racional soma_r(struct racional r1, struct racional r2) {
    return cria_r(r1.num * r2.den + r2.num * r1.den, r1.den * r2.den); // Chama a função para criar o número racional resultante
}

// Função para calcular a subtração de dois números racionais
struct racional subtrai_r(struct racional r1, struct racional r2) {
    return cria_r(r1.num * r2.den - r2.num * r1.den, r1.den * r2.den); // Chama a função para criar o número racional resultante
}

// Função para calcular a multiplicação de dois números racionais
struct racional multiplica_r(struct racional r1, struct racional r2) {
    return cria_r(r1.num * r2.num, r1.den * r2.den); // Chama a função para criar o número racional resultante
}

// Função para calcular a divisão de dois números racionais
struct racional divide_r(struct racional r1, struct racional r2) {
    if (r2.num == 0) { // Verifica se o denominador do segundo número racional é zero
        struct racional invalido = {0, 0, 0}; // Cria um número racional inválido
        return invalido; // Retorna o número racional inválido
    }
    return cria_r(r1.num * r2.den, r1.den * r2.num); // Chama a função para criar o número racional resultante
}

