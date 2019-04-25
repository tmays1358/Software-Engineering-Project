#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;
int main(){
string line = "";
char data[370099][20];
int q = 0;
ifstream myfile;
myfile.open("sorted_words.txt");
while(getline(myfile, line)){
		strncpy(data[q], line.c_str(), 20);
		q++;
}

//sort(data[0], data[370099]);
//char data2[200][20];
//char data3[200][20];
vector<string> data2;
vector<string> data3;
vector<string> data4;
string word2 = "testings out the spell check spamlewq function add.txt don't try without regttte transfer.txt";
//string word2 = "what is passed through";


istringstream ss(word2);
string token;
char backup[20];
int sc = 0; //word count
int kc = 0;
int i = 0;
int k = 0;
int l = 0;
int o = 0;
int s = 0;
int y = 0;
while(getline(ss, token, ' ')){	
	char x = token.at(0); //get one word at a time based on space
	if(x == 'a'){l = 0;o = 25416;}	//set indexs
	if(x == 'b'){l = 25417;o = 43289;}
	if(x == 'c'){l = 43290;o = 75935;}
	if(x == 'd'){l = 75936;o = 94667;}
	if(x == 'e'){l = 94668;o = 108864;}
	if(x == 'f'){l = 108865;o = 120757;}
	if(x == 'g'){l = 120758;o = 131710;}
	if(x == 'h'){l = 131711;o = 145453;}
	if(x == 'i'){l = 145454;o = 158652;}
	if(x == 'j'){l = 158653;o = 161492;}
	if(x == 'k'){l = 161493;o = 165444;}
	if(x == 'l'){l = 165445;o = 175446;}
	if(x == 'm'){l = 175447;o = 195252;}
	if(x == 'n'){l = 195253;o = 208709;}
	if(x == 'o'){l = 208710;o = 221390;}
	if(x == 'p'){l = 221391;o = 256250;}
	if(x == 'q'){l = 256251;o = 258043;}
	if(x == 'r'){l = 258044;o = 274826;}
	if(x == 's'){l = 274827;o = 332404;}
	if(x == 't'){l = 313588;o = 332405;}
	if(x == 'u'){l = 332486;o = 355172;}
	if(x == 'v'){l = 355173;o = 360501;}
	if(x == 'w'){l = 360502;o = 367060;}
	if(x == 'x'){l = 367061;o = 367567;}
	if(x == 'y'){l = 367578;o = 368710;}
	if(x == 'z'){l = 368711;o = 370099;}
	printf("%s, %d, %d\n", token.c_str(), l, o);  //testing
	strncpy(backup, token.c_str(), 20);
	//printf("%s\n", backup);
	string wp = backup;
	//printf("%s\n", wp.c_str());
        for(i=l; i<o;i++){ //check certain indexes
                s=0;  //set count of found chars, resets per word search
                y = token.length();  //for comparison if word found if s's count = y its a match
                string word = "";  //when a char match add to word, if it doesn't reset the matched word
                for(k=0;k<20;k++){ //length of a word is 20
			if(token[k] == '.' && token[k+1] == 't' && token[k+2] == 'x' && token[k+3] == 't'){
                                k = 21;
                                i = o;
                                data4.push_back(wp.c_str());
                                }
			 if(data[i][k] == token[k]){ //compare one char at a time
/*				if(token[k] == '.' && token[k+1] == 't' && token[k+2] == 'x' && token[k+3] == 't'){
				k = 21;
				i = o;
				word += token[k];
				word += token[k+1];
				word += token[k+2];
				word += token[k+3];
				data4.push_back(word.c_str());
				}*/
                                s++;
                                word += token[k];
                        }
                        if((strcmp(wp.c_str(), word.c_str()))==0){
		        //if(s == y){

                               // strncpy(data2[sc], word.c_str(), 20);
			       data2.push_back(word.c_str());
	//			printf("%s", data2[sc]);
				sc++;
				k = 21; //if a match set word to the 2nd array
				i = o;
                        }
			if(i == o-1 and k == 19){
				//strncpy(data3[kc], wp.c_str(), 20);
				data3.push_back(wp.c_str());
				kc++;
				i = o+1;
				k = 21;
			}
                }
        }

}

printf("Words Found\n");
for(auto i=data2.begin(); i!=data2.end();i++){
        cout << *i << " \n";
}

printf("\nWords Not Found\n");
for(auto i=data3.begin(); i!=data3.end();i++){
       // printf("%s ", *i.c_str());
//	a = &i.length();
       cout << *i << " \n";
}

printf("\nFILES Found\n");
for(auto i=data4.begin(); i!=data4.end();i++){
       // printf("%s ", *i.c_str());
       cout << *i << " \n";
}

printf("\n");


/*
printf("Words Found\n");
for(i=0; i<sc;i++){
	printf("%s ", data2[i]);
}

printf("\nWords Not Found\n");
for(i=0; i<kc;i++){
        printf("%s ", data3[i]);
}
printf("\n");

*/

}
