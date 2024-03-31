// assignment is to practice recursion, implementeing a path finding algorithm 
#include <iostream> 
#include <string> 
#include <fstream> 

using namespace std; 

int startX = 0;
int startY = 0;
int endX = 0; 
int endY = 0; 
int vacantSpots = 0; 
const int ROWS = 7;
const int COLUMNS = 7; 
//char grid[ROWS][COLUMNS]; 


void printArray(char grid[][COLUMNS]){ // for debugging 
    for(int i = 0; i < ROWS; i++){
        for(int j= 0; j < COLUMNS; j++){
            cout << grid[i][j] << " "; 
        }
        cout << endl; 
    }
}

char charGenerator(int stepCounter){ // returns the appropriate character based on the value from stepCounter
    stepCounter = stepCounter - 1; // put back to desired indexing style 
    if(stepCounter >= 0 && stepCounter <= 9){
        int tempIndex = stepCounter - 0; 
        return '0' + tempIndex; 
    }
    else {
        int tempIndex = stepCounter - 10; // see how for away it is from 10 
        return 'A' + tempIndex; // subtract that 'a' to see what char to output 
    }
}

bool recursiveFoo(char grid[][COLUMNS], int x, int y, int stepCounter){
    if(x == endX && y == endY && stepCounter == vacantSpots){
        grid[y][x] = charGenerator(stepCounter); 
        return true;
    }

    if(grid[y][x] == '_'){
        return false; 
    }

    if(grid[y][x] == ' '){
        
        if(y+1<ROWS){
            if(grid[y+1][x]!='*'){ // make sure area has not already been read 
                grid[y][x] = '*'; 
                if(recursiveFoo(grid, x, y + 1, stepCounter + 1)){
                    grid[y][x] = charGenerator(stepCounter); 
                    return true; 
                }
                grid[y][x] = ' '; 
            }
        }

        if(y-1>=0){
            if(grid[y-1][x] != '*'){
                grid[y][x] = '*'; 
                if(recursiveFoo(grid, x, y - 1, stepCounter + 1)){
                    grid[y][x] = charGenerator(stepCounter); 
                    return true; 
                }
                grid[y][x] = ' '; 
            }
        }

        if(x+1<COLUMNS){
            if(grid[y][x+1] != '*'){
                grid[y][x] = '*';
                if(recursiveFoo(grid, x + 1, y, stepCounter + 1)){
                    grid[y][x] = charGenerator(stepCounter); 
                    return true; 
                }
                grid[y][x] = ' '; 
            }
        }
        
        if(x-1>=0){
            if(grid[y][x-1] != '*'){
                grid[y][x] = '*'; 
                if(recursiveFoo(grid, x - 1, y, stepCounter + 1)){
                    grid[y][x] = charGenerator(stepCounter); 
                    return true; 
                }
                grid[y][x] = ' '; 
            }
        }
        
    }
    return false;
    //cout << "end of foo reached" << endl; 

}  

int main(){

    // get user input for input file and open it 
    string inputFile = "no input file"; 
    ifstream fin; 
    while(true){ 
        cout << "Enter config file: "; // prompt user
        getline(cin, inputFile); 
        cin.clear();  // clear input stream just in case
        //cin.ignore(1000, '\n');  
        cin.sync(); 

        fin.open(inputFile); 
        if(fin.is_open()){ // if file is opne, exit loop 
            break; 
        }
        else {
            cout << "Invalid input file" << endl; 
        }
    }

    char grid[ROWS][COLUMNS]; 
    char garbage; // used to discard the new line characters
    //int vacantSpots = 0; 
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS + 1; j++){ // columns plus one to account for \n
            if(j == COLUMNS){ 
                fin.get(garbage); 
            }else{
                fin.get(grid[i][j]); 
                if(grid[i][j] == ' '){
                    vacantSpots++;
                }
            }
            
        }
    }

    fin.close(); 

    string coordinateInput; 
    //int startX, startY, endX, endY; 
    
    while(true){ // have user input for starting coordinates 
        cout << "Please enter starting coordinates: " ; //prompt user for input 
        getline(cin, coordinateInput);

        if(coordinateInput.length() < 3 || coordinateInput[1] != ' '){
            cout << "Please re enter starting coordinates" << endl; 
            cin.clear(); 
            cin.sync();
            continue; 
        }
        startY = coordinateInput[0] - '0'; 
        startX = coordinateInput[2] - '0'; 
        if(startX > COLUMNS - 1 || startX < 0 || startY > ROWS - 1 || startY < 0){
            cout << "Please re enter starting coordinates" << endl; 
            cin.clear(); 
            cin.sync();
            continue; 
        }
        
        cin.clear(); 
        cin.sync();
        break; 

    }    


    coordinateInput = " "; // reset string 
    while(true){ // have user input for starting coordinates 
        cout << "Please enter end coordinates: " ; //prompt user for input 
        getline(cin, coordinateInput);

        if(coordinateInput.length() < 3 || coordinateInput[1] != ' '){
            cout << "Please re enter end coordinates" << endl; 
            cin.clear(); 
            cin.sync();
            continue; 
        }
        endY = coordinateInput[0] - '0'; 
        endX = coordinateInput[2] - '0'; 
        if(endX > COLUMNS - 1 || endX < 0 || endY > ROWS - 1 || endY < 0){
            cout << "Please re enter end coordinates" << endl; 
            cin.clear(); 
            cin.sync();
            continue; 
        }
        
        cin.clear(); 
        cin.sync();
        break; 

    }    

    recursiveFoo(grid, startX, startY, 1); 
    printArray(grid); 


   /* cout << endl << "startX coord " << startX << endl 
    << "startY coord " << startY << endl; */ 
    


    return 0; 
    
}


