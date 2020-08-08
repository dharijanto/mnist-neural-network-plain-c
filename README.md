# README

I had an idea of prototyping a game like NDS' Lost Magic, where it would use touch-drawn pattern to summon a magic. In order to do that,
I needed a way to do pattern recognition. Since I wanted the game to run on mobile devices and other light-weight platform, this
needs to be a light-weight and portable code. What immediately came to mind was SVM. I tried using libsvm to train MNIST, but it turned out
very slow. Hence I'm trying out DL-based technique for MNIST.

## Attribution
Modified version of basic MNIST shallow neural network implementation in C by [Andrew Carter](https://github.com/AndrewCarterUK/mnist-neural-network-plain-c.git).

