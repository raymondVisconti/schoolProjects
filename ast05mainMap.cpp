// build a spell checker using hash maps 


#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <string> 
#include <fstream> 
#include <unordered_map> 

using namespace std; 


// globals 
unordered_map<string, bool> dictionaryMap; 
unordered_map<string, bool> misspelledWords;

vector<string> genSuggWord(string mispledWrd){
    vector<string> suggestedWords; 
    string suggTemp; //temp variable to store genreated words into 
    for (char i = 'a'; i <= 'z'; i++){
        for(int j = 0; j < mispledWrd.length(); j++){ //replace letters with a - z 
            suggTemp = mispledWrd; 
            suggTemp[j] = i; 
            suggestedWords.push_back(suggTemp); 
        }
        for(int j = 0; j < mispledWrd.length() + 1; j++){
            suggTemp = mispledWrd;
            suggTemp.insert(j, 1, i); 
            suggestedWords.push_back(suggTemp); 
        }
    }

    // now check for matches with dictionary 
    vector<string> suggWrdsMatches; // all the generated words that match with our dictionaryMap 
    for(int i = 0; i < suggestedWords.size(); i++){
        if(dictionaryMap.count(suggestedWords[i]) > 0){
            suggWrdsMatches.push_back(suggestedWords[i]); 
        }
    }
    
    return suggWrdsMatches; 
} 

string toLowerCase(string currentWord){ //converts string to all lowercase letters 
    for(int i = 0; i < currentWord.length(); i++){
            currentWord[i] = tolower(currentWord[i]); 
        }

    return currentWord; 
}

string toUpperCase(string currentWord){ // converts string to all uppercase letters 
    for(int i = 0; i < currentWord.length(); i++){
            currentWord[i] = toupper(currentWord[i]); 
        }

    return currentWord; 
}

void printWords(vector<string> suggestedWords){
    if(suggestedWords.size() > 0){
        cout << "Suggested words" << endl; 
        for(int i = 0; i < suggestedWords.size(); i++){
            suggestedWords[i] = toUpperCase(suggestedWords[i]);
            cout << suggestedWords[i] << endl; 
        }
    }
    else{
        cout << "No suggestions" << endl; 
    }
}


int main(){

    // get user input for input file and open it 
    string dictionaryFile = "usa.txt"; 
    ifstream fin; 
    fin.open(dictionaryFile); 
    
    string dictionaryTemp = ""; 
   
    while(getline(fin, dictionaryTemp)){
        dictionaryMap[dictionaryTemp] = true; 
    }

    fin.close(); 

    string inputFile = "no input file"; 
    while(true){ 
        cout << "Enter filename: "; 
        getline(cin, inputFile); 
        cin.clear();  
        cin.sync(); 

        fin.open(inputFile); 
        if(fin.is_open()){ // exit loop if open file successful 
            break; 
        }
        else {
            cout << "Invalid input file" << endl; 
        }
    }

    string currentWord; 
    vector<string> suggestedWords;  // will contain all the generated words that match with dictionary map 
    while(!fin.eof()){
        fin >> currentWord; 
        //put word in all lower case 
        currentWord = toLowerCase(currentWord); 
        // cout << currentWord << endl; // for debugging 
        if(dictionaryMap.count(currentWord) == 0 && misspelledWords.count(currentWord) == 0){// if word is not in dictionary and hasnt already been processed
            misspelledWords[currentWord] = 1; // add to misspelled words map 
            suggestedWords = genSuggWord(currentWord); // generate suggested words and store in suggestedWords vector 
            // print sorted vector of suggested words 
            cout << toUpperCase(currentWord) << " is misspelled" << endl << endl; 
            printWords(suggestedWords); 
            cout << endl; 
        }
    }
    
    return 0; 

}
