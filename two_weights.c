#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam_treino 6
#define rate 1e-3

typedef struct Neuron
{
    float result;
    float peso1, peso2;
    float bias;
} neuro;

float respostas_espera[][3] = {
    {1, 7, 7},
    {2, 7, 14},
    {3, 7, 21},
    {4, 7, 28},
    {5, 7, 35},
    {6, 7, 42},
};

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

float cost(float w1, float w2)
{
    float controle = 0.0f;
    for (int i = 0; i < tam_treino; i++)
    {
        float x1 = respostas_espera[i][0];
        float x2 = respostas_espera[i][1];
        float y = x1 * w1 + x2 * w2;
        float z = y - respostas_espera[i][2];
        controle += z * z;
    }
    controle = controle / tam_treino;
    return controle;
}

float ajustar(float ajuste, float *p1, float *p2)
{
    for (int i = 0; i < 10000; i++)
    {
        float x = cost(*p1, *p2);
        float dpeso1 = (cost((*p1) + ajuste, *p2) - x) / ajuste;
        float dpeso2 = (cost(*p1, (*p2) + ajuste) - x) / ajuste;
        *p1 -= rate * dpeso1;
        *p2 -= rate * dpeso2;
    }
}

int main()
{
    float resposta;
    neuro neuronio1;
    srand(time(0));
    neuronio1.peso1 = rand_float() * 10.0f;
    neuronio1.peso2 = rand_float() * 10.0f;

    float ajuste = 1e-3;
    ajustar(ajuste, &neuronio1.peso1, &neuronio1.peso2);
    printf("peso1: %f, peso2: %f\n", neuronio1.peso1, neuronio1.peso2);

    /*
    for (int i = 0; i < tam_treino; i++)
    {
        neuronio1.result = respostas_espera[i][0] * neuronio1.peso + neuronio1.bias;
        printf("temos: %.4f queriamos: %.4f\n", neuronio1.result, respostas_espera[i][1]);
    }
    */

    printf("%f ", (neuronio1.peso1 * 2) + (neuronio1.peso2 * 7));
}