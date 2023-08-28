#include<bits/stdc++.h>
using namespace std;

class Sudokobase{
    public:
        int N;
        int grid[9][9];
        //Grid g1;
        void printGrid(){
            for (int row = 0; row < N; row++){
                for (int col = 0; col < N; col++){
                    if(col == 3 || col == 6)
                        cout << " | ";
                    cout << grid[row][col] <<" ";
          }
          if(row == 2 || row == 5){
             cout << endl;
             for(int i = 0; i<N; i++)
                cout << "---";
          }
          cout << endl;
       }
        }
        //void getGridElements(){}
};



class Game : Sudokobase{
    char levels;

};

class Checker : Sudokobase{

    public:
    bool isPresentInCol(int col, int num){ //check whether num is present in col or not
       for (int row = 0; row < N; row++)
          if (grid[row][col] == num)
             return true;
       return false;
    }
    bool isPresentInRow(int row, int num){ //check whether num is present in row or not
       for (int col = 0; col < N; col++)
          if (grid[row][col] == num)
             return true;
       return false;
    }
    bool isPresentInBox(int boxStartRow, int boxStartCol, int num){
    //check whether num is present in 3x3 box or not
       for (int row = 0; row < 3; row++)
          for (int col = 0; col < 3; col++)
             if (grid[row+boxStartRow][col+boxStartCol] == num)
                return true;
       return false;
    }
    bool findEmptyPlace(int &row, int &col){ //get empty location and update row and column
       for (row = 0; row < N; row++)
          for (col = 0; col < N; col++)
             if (grid[row][col] == 0) //marked with 0 is empty
                return true;
       return false;
    }
    bool isValidPlace(int row, int col, int num){
       //when item not found in col, row and current 3x3 box
       return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
    col - col%3, num);
    }
}; //friend functions - isValid and findEmptyPlace

class Solver : Sudokobase,Checker{
    bool solveSudoku(){
       int row,col;
       if (!findEmptyPlace(row, col))
          return true; //when all places are filled
        cout<<row<<" "<<col<<endl;
       for (int num = 1; num <= 9; num++){ //valid numbers are 1 - 9
          if (isValidPlace(row, col, num)){ //check validation, if yes, put the number in the grid
             grid[row][col] = num;
             if (solveSudoku()) //recursively go for other rooms in the grid
                return true;
             grid[row][col] = 0; //turn to unassigned space when conditions are not satisfied
          }
       }
       return false;
    }
};

class Grid : Checker{
    int row, col;
    grid[1][1] = 1;

};

class User{
    string name;
    string displayMessage;

    User(string n, string d){
        name = n;
        displayMessage = d;
    }
    
};