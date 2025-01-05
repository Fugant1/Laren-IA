#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tam_treino 6
#define rate 1e-3

typedef struct Neuron
{
    float result;
    float peso;
    float bias;
} neuro;

float respostas_espera[][2] = {
    {1, 5},
    {2, 10},
    {3, 15},
    {4, 20},
    {5, 25},
    {6, 30},
};

float rand_float(void)
{
    return (float)rand() / (float)RAND_MAX;
}

float cost(float w, float b)
{
    float controle = 0.0f;
    for (int i = 0; i < tam_treino; i++)
    {
        float x = respostas_espera[i][0];
        float y = x * w + b;
        float z = y - respostas_espera[i][1];
        controle += z * z;
    }
    controle = controle / tam_treino;
    return controle;
}

float ajustar(float ajuste, float *p, float *b)
{
    for (int i = 0; i < 5000; i++)
    {
        float x = cost(*p, *b);
        float dpeso = (cost(*p + ajuste, *b) - x) / ajuste;
        float dbias = (cost(*p, *b + ajuste) - x) / ajuste;
        *p -= rate * dpeso;
        *b -= rate * dbias;
    }
}

int main()
{
    float resposta;
    neuro neuronio1;
    srand(time(0));
    neuronio1.peso = rand_float() * 10.0f;
    neuronio1.bias = rand_float() * 2.0f;

    float ajuste = 1e-3;
    ajustar(ajuste, &neuronio1.peso, &neuronio1.bias);
    printf("peso: %f, bias: %f\n", neuronio1.peso, neuronio1.bias);
    for (int i = 0; i < tam_treino; i++)
    {
        neuronio1.result = respostas_espera[i][0] * neuronio1.peso + neuronio1.bias;
        printf("temos: %.4f queriamos: %.4f\n", neuronio1.result, respostas_espera[i][1]);
    }
}