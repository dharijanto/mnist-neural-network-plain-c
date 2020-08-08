#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "include/mnist_file.h"
#include "include/neural_network.h"

const char * train_images_file = "data/train-images-idx3-ubyte";
const char * train_labels_file = "data/train-labels-idx1-ubyte";

const char * network_file_path = "output/network-ubyte";

int main(int argc, char *argv[])
{
    mnist_dataset_t * train_dataset, * test_dataset;
    mnist_dataset_t batch;
    neural_network_t network;
    float loss, accuracy;
    int i, batches;
    const int idx = 123;

    // Read the datasets from the files
    train_dataset = mnist_get_dataset(train_images_file, train_labels_file);

    float activations[MNIST_LABELS];
    float b_grad, W_grad;

    if (neural_network_load_network(&network, network_file_path) != 0) {
      fprintf(stderr, "Failed to load neural network from file!\n");
      return 1;
    }

    // First forward propagate through the network to calculate activations
    neural_network_hypothesis(&train_dataset->images[idx], &network, activations);
    for (int i = 0; i < MNIST_LABELS; i++) {
      printf("Prediction for \t%d = %.3f\n", i, activations[i]);
    }
    printf("Real label: %d\n", train_dataset->labels[idx]);

    return 0;
}