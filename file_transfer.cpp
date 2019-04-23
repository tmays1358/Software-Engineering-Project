#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void save_to_file(string read_in)
{
	int a = read_in.length();
	string token1 = "!@!";
	string token2 = ":";
	string final,temp;
string check = read_in.substr(read_in.find(token1)+3,read_in.find(token2)-3);
string msg = read_in.substr(read_in.find(token2)+1,a);
if (check == "file_content"){
ofstream myfile;
myfile.open("newfile.txt");
myfile << msg;
myfile.close();
}
}


std::string send_as_msg(string filename){
 std::string final;
 std::string token1 = "!@!";
 std::string token2 = ":";
 int a = filename.length();
	std::string check = filename.substr(filename.find(token1)+3,filename.find(token2)-3);
	std::string file = filename.substr(filename.find(token2)+1,a);
	cout << check << "\n"  << file << endl;
if (check == "send_file")
{
	string temp = "!@!file_content:";
	string line;
	string output;
	ifstream theirfile (file);
	if(theirfile.is_open())
	{
		while(!theirfile.eof()){
		getline (theirfile,line);
		output = output + line;}
	}
	theirfile.close();
final = temp + output;
cout << final << endl;
}
return final;
}

int main(){
 string the_message = send_as_msg("!@!send_file:test.txt");
 save_to_file(the_message);
return 0;
}
