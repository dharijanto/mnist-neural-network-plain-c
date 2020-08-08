# README

I had an idea of prototyping a game like NDS' Lost Magic, where it would use touch-drawn pattern to summon a magic. In order to do that,
I needed a way to do pattern recognition. Since I wanted the game to run on mobile devices and other light-weight platform, this
needs to be a light-weight and portable code. What immediately came to mind was SVM. I tried using libsvm to train MNIST, but it turned out
very slow. Hence I'm trying out DL-based technique for MNIST. My plan is:
- To see if this NN would be good enough to recognize a pattern that's drawn using touch on typical mobile devices.
- To see if CPU-based inference of this NN is quick enough to be used for an RTS game

# Usage
- `train_neural_network` this trains a shallow NN for MNIST and output it to ./output/network-ubyte

## Attribution
This repo is a fork off Andrew Carter's [implementation of shallow neural network for MNIST](https://github.com/AndrewCarterUK/mnist-neural-network-plain-c.git)
in plain C. Thanks to him for uploading such a clean C code that's easy to understand.

