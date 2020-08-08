all:
	gcc -g mnist.c mnist_file.c neural_network.c -lm -o mnist
