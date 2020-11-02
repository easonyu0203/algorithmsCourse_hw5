
#include<string>
#include<iomanip>  
#include<fstream>
#include<iostream>
#include"KMP.h" //KMP()  
#include"Fibo.h" //class Fibo28

unsigned long long int occur_counter(int n, std::string& p);

Fibo28 fibos;

int main(int argc, char* argv[]){

	int caseCnt = 1;
	//input
	std::string p;
	int n;
	// input file
	if(argc <= 1){return 1;}
	std::ifstream infile(argv[1]);
	
	while(infile >> n >> p){

		unsigned long long int count = occur_counter(n, p);

		std::cout << "Case " << caseCnt << ": " << count << std::endl;

		caseCnt++;

	}

	

	return 0;
}

unsigned long long int occur_counter(int n, std::string& p){

	// find m
	int m;
	for(int i = 2;;i++){
		if(p.length() < fibos.length(i)){
			m = i + 3;
			break;
		}
	}


	// edge cases
	if(p == "0"){
		if(n < 2) return (n == 0)? 1 : 0;
		return fibos.length(n-2);
	}
	if(p == "1"){
		if(n < 2) return (n == 0)? 0 : 1;
		return fibos.length(n-1);
	}
	if(n < m){
		return KMP(fibos.n(n), p);
	}

	// n >= m

	static unsigned long long int occurences[101];

	// base case
	occurences[m-1] = KMP(fibos.n(m-1), p);
	occurences[m-2] = KMP(fibos.n(m-2), p);
	occurences[m-3] = KMP(fibos.n(m-3), p);
	unsigned long long int _w = occurences[m-1] + KMP(fibos.n(m-3) + fibos.n(m-2), p) - 2*(occurences[m-2] + occurences[m-3]);

	// induction step
	for(int i = m; i <= n; i++){
		occurences[i] = 2 * occurences[i-2] + occurences[i - 3] + _w;
	}

	return occurences[n];
}