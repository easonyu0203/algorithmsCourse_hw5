#include <iostream>
#include <string>
#include <iomanip>

#define lps_DEBUG 0
#define KMP_DEBUG 0
#define KMP_MAIN_DEBUG 0

// KMP pattern search function
// output the number of occurence
int KMP(std::string_view txt, std::string_view pat){

	// set up LPS array
	int lps[pat.length()];
	int len = 0; // length of the previous longest prefix suffix 
	lps[0] = 0; // lps[0] is always 0 
	int i = 1;
	while (i < pat.length()){
		if(pat[i] == pat[len]){
			len++;
			lps[i] = len;
			i++;
		}
		else{ // (pat[i] != pat[len]) 
			if(len == 0){
				lps[i] = 0;
				i++;
			}
			else{
				len = lps[len - 1];
			}
		}
	}
	
	#if lps_DEBUG == 1
	std::cout << "pattern & lps array\n";
	for(int i = 0; i < pat.length(); i++){
		std::cout << std::setw(3) << pat[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < pat.length(); i++){
		std::cout << std::setw(3) << lps[i];
	}
	std::cout << std::endl;
	#endif
	
	int count = 0; // total occurence
	i = 0; // index for txt
    int j = 0; // index for pat

	while(i < txt.length()){
		if(pat[j] == txt[i]){
			i++;
			j++;
		}

		if(j == pat.length()){
			#if KMP_DEBUG == 1
			std::cout << "find match at index " << i - j << std::endl;
			#endif
			count++;
			j = lps[j - 1];
		}

		// mismatch after j matches 
        else if (i < txt.length() && pat[j] != txt[i]) { 
            // Do not match lps[0..lps[j-1]] characters, 
            // they will match anyway 
            if (j != 0) 
                j = lps[j - 1]; 
            else
                i++; 
        } 
	}

	return count;
}

#if KMP_MAIN_DEBUG == 1
int main(){

	std::string txt("abcabdabc");
	std::string pat("abc");

	std::cout << KMP(txt, pat) << std::endl;

	return 0;
}
#endif