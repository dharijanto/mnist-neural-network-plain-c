#include <stdio.h>
#include "lib/easyppm/easyppm.h"
#include "include/mnist_file.h"
#include "include/neural_network.h"

const char * ppm_file_path = "input/five.pgm";
const char * network_file_path = "output/network-ubyte";

int main (int argc, char **argv)
{
  PPM ppm = easyppm_create(28, 28, IMAGETYPE_PGM);
  easyppm_read(&ppm, ppm_file_path);

  if (ppm.itype != IMAGETYPE_PGM && ppm.width != MNIST_IMAGE_WIDTH && ppm.height != MNIST_IMAGE_HEIGHT) {
    fprintf(stderr, "Invalid PGM file!");
    return 1;
  }

  neural_network_t network;

  if (neural_network_load_network(&network, network_file_path) != 0) {
    fprintf(stderr, "Failed to load neural network from file!\n");
    return 1;
  }
  mnist_image_t image;

  // Convert PBM into mnist format
  // http://yann.lecun.com/exdb/mnist/
  for (int row = 0; row < ppm.height; row++) {
    for (int col = 0; col < ppm.width; col++) {
      int idx = row * ppm.width + col;
      image.pixels[idx] = 255 - ppm.image[idx];
    }
  }

  float activations[MNIST_LABELS];
  neural_network_hypothesis(&image, &network, activations);
  float accuracy = 0;
  int prediction = -1;

  // First forward propagate through the network to calculate activations
  for (int i = 0; i < MNIST_LABELS; i++) {
    printf("Prediction for \t%d = %.3f\n", i, activations[i]);
    if (activations[i] > accuracy) {
      accuracy = activations[i];
      prediction = i;
    }
  }

  printf("\nYour input is predicted to be %d with %.2f%% confidence\n", prediction, accuracy * 100.0);

  return 0;
}