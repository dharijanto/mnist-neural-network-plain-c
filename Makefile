all:
	gcc -g train.c mnist_file.c neural_network.c -lm -o train
	gcc -g predict.c mnist_file.c neural_network.c -lm -o predict

predict-ppm: easyppm
	gcc -g predict_ppm.c mnist_file.c neural_network.c easyppm.o -lm -o predict-ppm

easyppm:
	gcc -g lib/easyppm/easyppm.c -c

clean:
	rm -f train predict
