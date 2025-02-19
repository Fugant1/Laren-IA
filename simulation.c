#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define tam_treino 2
#define e 2.71
#define number_layers 2
#define number_inputs 2
#define number_outputs 1

typedef struct neuro
{
    float value;
    float *weights;
} neuron;

typedef struct layer
{
    neuron *neurons;
    int size;
    int num_weights;
} layer;

void get_rweights(layer *layers);

float get_result(layer *layers, float *inputs);

float activate(float result); // Activation funciontion using sigmoid

int main(void)
{
    /*
    ----------------------------DEFINITION OF BASICS--------------------------------------------------------------
    */
    float inputs[number_inputs] = {0, 1};
    float output[number_outputs] = {1};
    float result;
    float error;

    int layer_sizes[number_layers] = {2, 3};

    layer layers[number_layers];

    layers[0].num_weights = 3;

    layers[1].num_weights = 1;
    /*
    -----------------------------------END OF IT------------------------------------------------------------------
    */
    for (int i = 0; i < number_layers; i++)
    {
        layers[i].size = layer_sizes[i];
        layers[i].neurons = (neuron *)malloc(layer_sizes[i] * sizeof(neuron));
        for (int j = 0; j < layer_sizes[i]; j++)
        {
            layers[i].neurons[j].weights = (float *)malloc(layers[i].num_weights * sizeof(float));
        }
    }

    get_rweights(layers);

    result = get_result(layers, inputs);
    // printf("%f", get_result(layers, inputs));
    error = output[0] - result;
    printf("We had : %.2f,\nWe wanted: %.2f,\nThe error was: %f\n", result, output[0], error);
}

void get_rweights(layer *layers)
{
    srand(time(0));
    for (int i = 0; i < number_layers; i++)
    {
        for (int j = 0; j < layers[i].size; j++)
        {
            for (int k = 0; k < layers[i].num_weights; k++)
            {
                layers[i].neurons[j].weights[k] = rand() % 10;
                // printf("%f\n", layers[i].neurons[j].weights[k]);
            }
        }
    }
}

float get_result(layer *layers, float *inputs)
{
    // Initialize the values
    for (int i = 0; i < layers[0].size; i++)
    {
        layers[0].neurons[i].value = inputs[i];
    }

    // Propagates the values att with the weights
    for (int i = 0; i < number_layers - 1; i++)
    {
        int num_neurons_current = layers[i].size;
        int num_neurons_next = layers[i + 1].size;

        // Initialize the values of the next layer
        for (int j = 0; j < num_neurons_next; j++)
        {
            layers[i + 1].neurons[j].value = 0.0;
        }

        for (int j = 0; j < num_neurons_current; j++)
        {
            for (int k = 0; k < num_neurons_next; k++)
            {
                layers[i + 1].neurons[k].value += layers[i].neurons[j].value * layers[i].neurons[j].weights[k];
            }
        }

        for (int j = 0; j < num_neurons_next; j++)
        {
            // activation of each value after the somatory
            layers[i + 1].neurons[j].value = activate(layers[i + 1].neurons[j].value);
        }
    }

    // final answer
    float final_answer = 0.0;
    for (int j = 0; j < layers[number_layers - 1].size; j++)
    {
        final_answer += layers[number_layers - 1].neurons[j].value;
    }
    return activate(final_answer);
}

float activate(float result)
{
    float one = 1;
    result *= -1;
    return (one / (one + (pow(e, result))));
}