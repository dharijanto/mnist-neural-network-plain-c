# README

I had an idea of prototyping a game like NDS' Lost Magic, where it would use touch-drawn pattern to summon a magic. In order to do that,
I needed a way to do pattern recognition. Since I wanted the game to run on mobile devices and other light-weight platform, this
needs to be a light-weight and portable code. What immediately came to mind was SVM. I tried using libsvm to train MNIST, but it turned out
very slow. Hence I'm trying out DL-based technique for MNIST. My plan is:
- To see if this NN would be good enough to recognize a pattern that's drawn using touch on typical mobile devices.
- To see if CPU-based inference of this NN is quick enough to be used for an RTS game

## Usage
- `train` this trains a shallow NN for MNIST and output it to ./output/network-ubyte
- `predict` this predicts the image from train dataset and then compare it with the actual label
- `predict-ppm` this takes a PPM image (specifically PGM format), convert it into MNIST format, and finally predicts it label

## Improvement

It works okay, but no the best. There are some cases where a digit is easily recognize by human, but
the trained NN failed to recognize it. The following are some efforts that can be done to improve the result:

- Normalize MNIST input
- Normalize bounding box, by stretching the content of the images into their bounding box
- Create custom test set to measure improvement

## Attribution
- Neural-network related code originally is a forked out off Andrew Carter's [implementation of shallow neural network for MNIST](https://github.com/AndrewCarterUK/mnist-neural-network-plain-c.git)
in plain C. Thanks to him for uploading such a clean C code that's easy to understand.
- PPM-related code is copied from [Frederico Menozzi's repo](https://github.com/fmenozzi/easyppm)

