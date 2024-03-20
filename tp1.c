/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */

int main (){

 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct racional {
    unsigned short int valido;
    int num;
    int den;
};

int aleat(int min, int max, int iteracao) {
    // Gerar números pseudoaleatórios determinísticos com base na iteração
    srand(iteracao);
    return min + rand() % (max - min + 1);
}

int mdc(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mmc(int a, int b) {
    return (a * b) / mdc(a, b);
}

struct racional simplifica_r(struct racional r) {
    if (r.den == 0) {
        r.valido = 0;
        return r;
    }

    int divisor = mdc(abs(r.num), abs(r.den));
    r.num /= divisor;
    r.den /= divisor;

    if (r.num < 0 && r.den < 0) {
        r.num = abs(r.num);
        r.den = abs(r.den);
    } else if (r.den < 0) {
        r.num *= -1;
        r.den = abs(r.den);
    }

    return r;
}

struct racional cria_r(int numerador, int denominador) {
    struct racional r;
    r.valido = 1;
    r.num = numerador;
    r.den = denominador;
    return simplifica_r(r);
}

struct racional sorteia_r(int n, int iteracao) {
    struct racional r;
    r.valido = 1;
    r.num = aleat(0, n, iteracao);
    r.den = aleat(1, n, iteracao);
    return simplifica_r(r);
}

void imprime_r(struct racional r) {
    if (!r.valido) {
        printf("INVALIDO");
        return;
    }

    if (r.num == 0) {
        printf("0");
    } else if (r.den == 1) {
        printf("%d", r.num);
    } else if (abs(r.num) == abs(r.den)) {
        printf("1");
    } else {
        if (r.num < 0 || r.den < 0) {
            printf("-");
        }
        printf("%d/%d", abs(r.num), abs(r.den));
    }
}

int valido_r(struct racional r) {
    return r.den != 0;
}

struct racional soma_r(struct racional r1, struct racional r2) {
    struct racional resultado;
    resultado.valido = 1;
    resultado.num = r1.num * r2.den + r2.num * r1.den;
    resultado.den = r1.den * r2.den;
    return simplifica_r(resultado);
}

struct racional subtrai_r(struct racional r1, struct racional r2) {
    struct racional resultado;
    resultado.valido = 1;
    resultado.num = r1.num * r2.den - r2.num * r1.den;
    resultado.den = r1.den * r2.den;
    return simplifica_r(resultado);
}

struct racional multiplica_r(struct racional r1, struct racional r2) {
    struct racional resultado;
    resultado.valido = 1;
    resultado.num = r1.num * r2.num;
    resultado.den = r1.den * r2.den;
    return simplifica_r(resultado);
}

struct racional divide_r(struct racional r1, struct racional r2) {
    struct racional resultado;
    resultado.valido = 1;
    resultado.num = r1.num * r2.den;
    resultado.den = r1.den * r2.num;

    if (r2.num == 0 || r1.den == 0 || r2.den == 0 || resultado.den == 0) {
        resultado.valido = 0;
    }

    return simplifica_r(resultado);
}

int main() {
    int n = 10;
    int max = 17;

    for (int i = 1; i <= n; i++) {
        printf("%d: ", i);

        struct racional r1 = sorteia_r(max, i);
        struct racional r2 = sorteia_r(max, i);

        imprime_r(r1);
        printf(" ");
        imprime_r(r2);
        printf(" ");

        if (!r1.valido || !r2.valido) {
            printf("NUMERO INVALIDO\n");
            continue;
        }

        struct racional soma = soma_r(r1, r2);
        struct racional subtracao = subtrai_r(r1, r2);
        struct racional multiplicacao = multiplica_r(r1, r2);
        struct racional divisao = divide_r(r1, r2);

        if (!divisao.valido) {
            printf("DIVISAO INVALIDA\n");
            continue;
        }

        imprime_r(soma);
        printf(" ");
        imprime_r(subtracao);
        printf(" ");
        imprime_r(multiplicacao);
        printf(" ");
        imprime_r(divisao);
        printf("\n");
    }

    return 0;
}


