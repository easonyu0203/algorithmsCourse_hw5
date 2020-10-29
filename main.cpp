#include<string_view>
#include<string>
#include<iomanip>
#include<fstream>
#include<iostream>
#include"KMP.cpp" //KMP()
#include"Fibo.cpp" //class Fibo28

unsigned long long int occur_counter(int n, std::string_view p);

Fibo28 fibos;

int main(){

	int caseCnt = 1;
	//input
	std::string p;
	int n;
	
	while(std::cin >> n >> p){

		unsigned long long int count = occur_counter(n, p);

		std::cout << "Case " << caseCnt << ": " << count << std::endl;

		caseCnt++;

	}

	

	return 0;
}

unsigned long long int occur_counter(int n, std::string_view p){

	// find m
	int m;
	for(int i = 2;;i++){
		if(p.length() < fibos.length(i)){
			m = i + 3;
			break;
		}
	}

	// std::cout << "m: " << m << std::endl;

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
	std::string tmp; tmp.reserve(fibos.length(m-1));
	tmp += fibos.n(m-3);
	tmp += fibos.n(m-2);
	unsigned long long int _w = occurences[m-1] + KMP(tmp, p) - 2*(occurences[m-2] + occurences[m-3]);

	// induction step
	for(int i = m; i <= n; i++){
		occurences[i] = 2 * occurences[i-2] + occurences[i - 3] + _w;
	}

	return occurences[n];
}