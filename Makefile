all:
	gcc -g train.c mnist_file.c neural_network.c -lm -o train

clean:
	rm train
