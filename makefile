hw5: main.cpp KMP.h Fibo.h
	g++ main.cpp -std=c++17 -o hw5

run: hw5
	./hw5

clean:
	rm hw5