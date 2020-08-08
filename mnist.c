#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "include/mnist_file.h"
#include "include/neural_network.h"

#define STEPS 1000
#define BATCH_SIZE 100

/**
 * Downloaded from: http://yann.lecun.com/exdb/mnist/
 */
const char * train_images_file = "data/train-images-idx3-ubyte";
const char * train_labels_file = "data/train-labels-idx1-ubyte";
const char * test_images_file = "data/t10k-images-idx3-ubyte";
const char * test_labels_file = "data/t10k-labels-idx1-ubyte";

const char * network_save_path = "output/network-ubyte";

/**
 * Calculate the accuracy of the predictions of a neural network on a dataset.
 */
float calculate_accuracy(mnist_dataset_t * dataset, neural_network_t * network)
{
    float activations[MNIST_LABELS], max_activation;
    int i, j, correct, predict;

    // Loop through the dataset
    for (i = 0, correct = 0; i < dataset->size; i++) {
        // Calculate the activations for each image using the neural network
        neural_network_hypothesis(&dataset->images[i], network, activations);

        // Set predict to the index of the greatest activation
        for (j = 0, predict = 0, max_activation = activations[0]; j < MNIST_LABELS; j++) {
            if (max_activation < activations[j]) {
                max_activation = activations[j];
                predict = j;
            }
        }

        // Increment the correct count if we predicted the right label
        if (predict == dataset->labels[i]) {
            correct++;
        }
    }

    // Return the percentage we predicted correctly as the accuracy
    return ((float) correct) / ((float) dataset->size);
}

int main(int argc, char *argv[])
{
    mnist_dataset_t * train_dataset, * test_dataset;
    mnist_dataset_t batch;
    neural_network_t network;
    float loss, accuracy;
    int i, batches;

    // Read the datasets from the files
    train_dataset = mnist_get_dataset(train_images_file, train_labels_file);
    test_dataset = mnist_get_dataset(test_images_file, test_labels_file);

    // Initialise weights and biases with random values
    neural_network_random_weights(&network);

    // Calculate how many batches (so we know when to wrap around)
    //        60k / 100 = 600
    batches = train_dataset->size / BATCH_SIZE;

    //   min i = 0
    //   max i = 999
    for (i = 0; i < STEPS; i++) {
        // printf("mnist_batch()...\n");
        // Initialise a new batch
        // min                            size, number ( 0 % 600 ) - 0
        // max                            size, number ( 999 % 600 ) - 599
        mnist_batch(train_dataset, &batch, 100, i % batches);

        // batch: {
        //     images: &dataset->images[0 - 59,900],
        //     labels: &dataset->labels[0 - 59,900],
        //     size: 100
        // }

       // printf("neural_network_training_step()...\n");
       // Run one step of gradient descent and calculate the loss
       loss = neural_network_training_step(&batch, &network, 0.5);

       // printf("calculate_accuracy()...\n");
       // Calculate the accuracy using the whole test dataset
       accuracy = calculate_accuracy(test_dataset, &network);
       printf("Step %04d\tAverage Loss: %.2f\tAccuracy: %.3f\n", i, loss / batch.size, accuracy);
    }

    // Save weight into file
    if (neural_network_save_network(&network, network_save_path) == 0) {
        printf("Successfully saved trained network to: %s\n", network_save_path);
    }


    // Cleanup
    mnist_free_dataset(train_dataset);
    mnist_free_dataset(test_dataset);
    // printf("exiting...\n");
    return 0;
}
