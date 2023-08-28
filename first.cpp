#include <iostream>

using namespace std;

//#define N 9

class sudoku
{
    int N;
    int grid[9][9] = {
       {3, 0, 6, 5, 0, 8, 4, 0, 0},
       {5, 2, 0, 0, 0, 0, 0, 0, 0},
       {0, 8, 7, 0, 0, 0, 0, 3, 1},
       {0, 0, 3, 0, 1, 0, 0, 8, 0},
       {9, 0, 0, 8, 6, 3, 0, 0, 5},
       {0, 5, 0, 0, 9, 0, 6, 0, 0},
       {1, 3, 0, 0, 0, 0, 2, 5, 0},
       {0, 0, 0, 0, 0, 0, 0, 7, 4},
       {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };
    
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

       
    public:
    sudoku(int Num){
        N = Num*Num;
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
    
    void printGrid(){ //print the sudoku grid after solve
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
    
    void getGrid(){ //get grid from user
       cout<<"enter all the nine numbers of the grid:\n";
       for (int row = 0; row < N; row++){
          for (int col = 0; col < N; col++){
              int val;
              cin>>val;
              grid[row][col] = val;
              
          }
       }
    }
/*
//input values:
grid1:
306508400520000000087000031003010080900863005050090600130000250000000074005206300

grid2:
010020300002003040080000006004700030000600008070098000300004090000800104006000000  

grid3:
010020300002003040050000006004200050000100007020087000300004080000600105006000000
.
.
.
link: http://forum.enjoysudoku.com/patterns-game-results-t6291.html
*/


};


int main(){
    sudoku s1(3);
    
    //s1.getGrid();
    //s1.printGrid();
    cout<<endl;
   if (s1.solveSudoku() == true)
      s1.printGrid();
   else
      cout << "No solution exists";
}
