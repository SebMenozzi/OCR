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

/* GLOBAL */

// constants
const int epoch = 10000;
const float learning_rate = 0.7;

const int training_data[4][2] = {
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { 0, 0 }
};
const int anwser_data[4] = { 1, 0, 1, 0 };

// context
int target;

float input_to_hidden_weights[2][3];
float input_to_hidden_bias[2] = {0.0, 0.0};

int input_layer[2];

float hidden_to_output_weights[3];
float hidden_to_output_bias = 0;

float hidden_layer[3];

float output_layer;

float error;
/************************/

/* UTILS */

double random_between_neg_1_pos_1() {
    int randNumber = rand() % 2; // 0 or 1
    double result = rand() / (RAND_MAX + 1.0); // between 0 and 1
    return (randNumber == 1) ? result : -1 * result;
}

void generate_random_input_weights() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
        {
            input_to_hidden_weights[i][j] = random_between_neg_1_pos_1();
        }
    }
}

void generate_random_hidden_weights() {
    for (int i = 0; i < 3; i++)
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
/************************/

/* FORWARD PROPAGATION */

void calc_hidden_layer() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            hidden_layer[j] += input_to_hidden_weights[i][j] * input_layer[i];
        }
    }
    for (int i = 0; i < 3; i ++) {
        hidden_layer[i] = sigmoid(hidden_layer[i] + input_to_hidden_bias[i]);
    }
}

void calc_output_layer() {
    for (int i = 0; i < 3; i++) {
        output_layer += hidden_to_output_weights[i] * hidden_layer[i];
    }
    output_layer = sigmoid(output_layer + hidden_to_output_bias);
}

void forward_propagate() {
    calc_hidden_layer();
    calc_output_layer();
}
/************************/

/* BACKWARD PROPAGATION */

void calc_error() {
    float result = target - output_layer;
    error = 0.5f * result * result ;
}

void back_propagate() {
    calc_error();
    
    for (int i = 0; i < 3; i++) {
        // new input weights
        for (int j = 0; j < 2; j++) {
            float deltaw1 = (output_layer - target) *
                            sigmoid_prime(output_layer) *
                            hidden_to_output_weights[i] *
                            sigmoid_prime(hidden_layer[i]) *
                            input_layer[j];
            
            input_to_hidden_weights[i][j] += - deltaw1 * learning_rate;
        }
        
        // new hidden weights
        float deltaw2 = (output_layer - target) * sigmoid_prime(output_layer) * hidden_layer[i];
        hidden_to_output_weights[i] += - deltaw2 * learning_rate;
        
        // new input bias
        float deltab1 = (output_layer - target) *
                        sigmoid_prime(output_layer) *
                        hidden_to_output_weights[i] *
                        sigmoid_prime(hidden_layer[i]);
        input_to_hidden_bias[i] += - deltab1 * learning_rate;
        
        // new hidden bias
        float deltab2 = (output_layer - target) * sigmoid_prime(output_layer);
        hidden_to_output_bias += - deltab2 * learning_rate;
    }
}

/************************/

void display_result() {
    printf(
        "(%d, %d) : expected: %d => calculated: %f (error: %f)\n\n",
        input_layer[0],
        input_layer[1],
        target,
        output_layer,
        error
    );
}

int main(int argc, const char * argv[]) {
    generate_random_input_weights();
    generate_random_hidden_weights();
    
    // train the network
    for (int i = 0; i < epoch; i++) {
        for (int inputs = 0; inputs < 4; inputs++) {
            input_layer[0] = training_data[inputs][0];
            input_layer[1] = training_data[inputs][1];
            target = anwser_data[inputs];
            
            forward_propagate();
            back_propagate();
            display_result();
        }
    }
    
    return 0;
}
