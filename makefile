hw5: main.cpp KMP.h Fibo.h
	g++ main.cpp -std=c++17 -O3 -o hw5

run: hw5
	./hw5

time:
	time ./hw5 input > output

clean:
	rm hw5 output