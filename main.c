//
//  main.c
//  OCR
//
//  Created by Sebastien Menozzi on 12/09/2018.
//  Copyright © 2018 Sebastien Menozzi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nb_neurons_hidden_layer 3
#define epoch 10000
#define learning_rate 0.7

/* GLOBAL */

const int training_data[4][2] = {
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { 0, 0 }
};
const int anwser_data[4] = { 1, 0, 1, 0 };

int target;

float input_to_hidden_weights[2][nb_neurons_hidden_layer];
float input_to_hidden_bias[2] = {0.0, 0.0};
float input_layer[2];

float hidden_to_output_weights[nb_neurons_hidden_layer];
float hidden_to_output_bias = 0;
float hidden_layer[nb_neurons_hidden_layer];

float output_layer;

float error_rate; // for debug
/********/

/* UTILS */

double random_between_neg_1_pos_1() {
    return 2.0f * rand() / RAND_MAX - 1;
}

void generate_random_input_to_hidden_weights() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < nb_neurons_hidden_layer; j++)
        {
            input_to_hidden_weights[i][j] = random_between_neg_1_pos_1();
        }
    }
}

void generate_random_hidden_to_output_weights() {
    for (int i = 0; i < nb_neurons_hidden_layer; i++)
    {
        hidden_to_output_weights[i] = random_between_neg_1_pos_1();
    }
}

// activation function
float sigmoid(float x)
{
    return 1.0 / (1.0 + exp(-x));
}

// derivative of activation function
float sigmoid_prime(float x)
{
    return x * (1.0 - x);
}
/********/

/* FORWARD PROPAGATION */

void forward_propagate() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < nb_neurons_hidden_layer; j++) {
            hidden_layer[j] += input_to_hidden_weights[i][j] * input_layer[i];
        }
    }
    for (int i = 0; i < nb_neurons_hidden_layer; i ++) {
        hidden_layer[i] = sigmoid(hidden_layer[i] + input_to_hidden_bias[i]);
        output_layer += hidden_to_output_weights[i] * hidden_layer[i];
    }
    output_layer = sigmoid(output_layer + hidden_to_output_bias);
}
/********/

/* BACKWARD PROPAGATION */

void back_propagate() {
    float error = output_layer - (float) target;
    error_rate = pow(error, 2);

    for (int i = 0; i < nb_neurons_hidden_layer; i++) {
        for (int j = 0; j < 2; j++) {
            float deltaw1 = error *
                            sigmoid_prime(output_layer) *
                            hidden_to_output_weights[i] *
                            sigmoid_prime(hidden_layer[i]) *
                            input_layer[j];
            // new input weights
            input_to_hidden_weights[i][j] -= deltaw1 * learning_rate;
        }

        float deltaw2 = error *
                        sigmoid_prime(output_layer) *
                        hidden_layer[i];
        // new hidden weights
        hidden_to_output_weights[i] -= deltaw2 * learning_rate;

        float deltab1 = error *
                        sigmoid_prime(output_layer) *
                        hidden_to_output_weights[i] *
                        sigmoid_prime(hidden_layer[i]);
        // new input bias
        input_to_hidden_bias[i] -= deltab1 * learning_rate;

        float deltab2 = error *
                        sigmoid_prime(output_layer);
        // new hidden bias
        hidden_to_output_bias -= deltab2 * learning_rate;
    }
}

/********/

void display_result() {
    printf(
        "(%d, %d) : expected: %d => calculated: %f (error: %f)\n",
        (int) input_layer[0],
        (int) input_layer[1],
        target,
        output_layer,
        error_rate
    );
}

int main(void) {
    generate_random_input_to_hidden_weights();
    generate_random_hidden_to_output_weights();

    // train the network
    for (int i = 0; i < epoch; i++) {
        for (int inputs = 0; inputs < 4; inputs++) {
            input_layer[0] = (float) training_data[inputs][0];
            input_layer[1] = (float) training_data[inputs][1];
            target = anwser_data[inputs];

            forward_propagate();
            back_propagate();
            display_result();
        }
    }

    return 0;
}
