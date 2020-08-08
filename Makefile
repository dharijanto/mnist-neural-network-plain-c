all:
	gcc -g mnist.c mnist_file.c train_neural_network.c -lm -o train_neural_network

clean:
	rm train_neural_network