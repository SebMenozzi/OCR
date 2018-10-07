#include "xor.h"

const float training_data[4][2] = {
    { 1, 0 },
    { 1, 1 },
    { 0, 1 },
    { 0, 0 }
};
const float anwser_data[4] = { 1, 0, 1, 0 };

float target;

float input_weights[2][nb_hidden_layer];
float input_bias[2] = {0.0, 0.0};
float input_layer[2];

float hidden_weights[nb_hidden_layer];
float hidden_bias = 0;
float hidden_layer[nb_hidden_layer];

float output_layer;

float error_rate; // for debug
/********/

/* UTILS */

double random_value() { // between -1 and 1
    return 2.0f * rand() / RAND_MAX - 1;
}

void random_input_weights() {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < nb_hidden_layer; j++)
        {
            input_weights[i][j] = random_value();
        }
    }
}

void random_hidden_weights() {
    for (int i = 0; i < nb_hidden_layer; i++)
    {
        hidden_weights[i] = random_value();
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
        for (int j = 0; j < nb_hidden_layer; j++) {
            hidden_layer[j] += input_weights[i][j] * input_layer[i];
        }
    }
    for (int i = 0; i < nb_hidden_layer; i ++) {
        hidden_layer[i] = sigmoid(hidden_layer[i] + input_bias[i]);
        output_layer += hidden_weights[i] * hidden_layer[i];
    }
    output_layer = sigmoid(output_layer + hidden_bias);
}
/********/

/* BACKWARD PROPAGATION */

void back_propagate() {
    float error = output_layer - target;
    error_rate = pow(error, 2);

    for (int i = 0; i < nb_hidden_layer; i++) {
        for (int j = 0; j < 2; j++) {
            float deltaw1 = error *
                            sigmoid_prime(output_layer) *
                            hidden_weights[i] *
                            sigmoid_prime(hidden_layer[i]) *
                            input_layer[j];
            // new input weights
            input_weights[i][j] -= deltaw1 * learning_rate;
        }

        float deltaw2 = error *
                        sigmoid_prime(output_layer) *
                        hidden_layer[i];
        // new hidden weights
        hidden_weights[i] -= deltaw2 * learning_rate;

        float deltab1 = error *
                        sigmoid_prime(output_layer) *
                        hidden_weights[i] *
                        sigmoid_prime(hidden_layer[i]);
        // new input bias
        input_bias[i] -= deltab1 * learning_rate;

        float deltab2 = error *
                        sigmoid_prime(output_layer);
        // new hidden bias
        hidden_bias -= deltab2 * learning_rate;
    }
}

/********/

void display_result() {
    printf(
        "(%.0f, %.0f) : expected: %.0f => calculated: %f (error: %f)\n",
        input_layer[0],
        input_layer[1],
        target,
        output_layer,
        error_rate
    );
}

void XOR() {
    random_input_weights();
    random_hidden_weights();

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
}
