#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
using namespace std;


string tab_completion(string str)
{
	string line;
	string potential;
	vector<string> word;
	int j = 0;
	int truth = 0; // bool conditioner to check if sorted word is potentially what user is typing out.
	
    ifstream myfile ("sorted_words.txt"); //for the file containing list of sorted words
    if(myfile.is_open())
    {
        while (myfile >> line) //if myfile.good()
        {
            word.push_back(line);
        }
        if (myfile.bad())
        {
            throw runtime_error ("bad");
        }
    }
    else
        cout << "Unable to open file";
    
    for (int i = 0; i < word.size(); i++)
    {
    	if((word[i][0] == str[0]) && (word[i].size() > str.size())) // finds to fit first char
    																// and weeds out any sorted
    																// words shorter than user's
    																// input string.
    																
    	{
    		for (j = 0; j < word[i].size(); j++)
    		{
    			if (word[i][j] != str[j]) //if the sorted word does not have any matching 
    										//chars, set to false.
    			{
    				truth = 1;    					
    			}
    		}
    		
    		if(truth == 0) // prints out potential words.
    		{
				cout << word[i] << "\n";
    		}
    		
    		truth = 0; //resets the boolean conditioner for the next word.
    	}
    }

}

int main()
{
	string einput;
	
	cin >> einput;
	
	tab_completion(einput);
	
	return 0;
}

