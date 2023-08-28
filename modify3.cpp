#include<iostream>
#include<bits/stdc++.h>

int grid[9][9]; 

using namespace std;
void printGrid(int b[][9])
{
for (int row = 0; row < 9; row++){
    for (int col = 0; col < 9; col++){
        if(col == 3 || col == 6)
            cout << " | ";
        cout << b[row][col]<<" ";
    }
    if(row == 2 || row == 5){
             cout << endl;
          for(int i = 0; i<9; i++)
                cout << "---";
          }
          cout << endl;
       }
}

class Grid{
    public:
    int lvl=0;

    //vector<vector<int>> grid;
    
    void Griding(vector<int> k)
       {
          for(int i=0;i<9;i++)
          {
              for(int j=0;j<9;j++)
              {
                grid[i][j] = (k[9*i+j]);
              }
          }
        }
    void Gridgenerate(int a)
    {
        lvl= a;

        if(lvl==1)
        {
            //cout<<"In level 1"<<endl;
            int g[100]={
            3,0,6,5,0,8,4,0,0,5,2,0,0,0,0,0,0,0,0,8,7,0,0,0,0,3,1,0,0,3,0,1,0,0,8,0,9,0,0,8,6,3,0,0,5,0,5,0,0,9,0,6,0,0,1,3,0,0,0,0,2,5,0,0,0,0,0,0,0,0,7,4,0,0,5,2,0,6,3,0,0};
            //cout<<"In level 1"<<endl;
            for(int i=0;i<9;i++)
            {   //cout<<"In level 1 "<<i<<endl;
                for(int j=0;j<9;j++)
                {   //cout<<"In level 1 "<<i<<endl;
                    //grid[i].push_back(g[9*i+j]);
                    grid[i][j] = g[9*i+j];
                    //cout<<"In level 1 "<<i<<endl;
                }
            }
        }
        else if(lvl==2)
        {
        int g[100]={
        0,1,0,0,2,0,3,0,0,0,0,2,0,0,3,0,4,0,0,8,0,0,0,0,0,0,6,0,0,4,7,0,0,0,3,0,0,0,0,6,0,0,0,0,8,0,7,0,0,9,8,0,0,0,3,0,0,0,0,4,0,9,0,0,0,0,8,0,0,1,0,4,0,0,6,0,0,0,0,0,0};  
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                //grid[i].push_back(g[9*i+j]);
                grid[i][j]=g[9*i+j];
            }
        }
        }
        else if(lvl==3)
        {
            int g[100]={
        0,1,0,0,2,0,3,0,0,0,0,2,0,0,3,0,4,0,0,5,0,0,0,0,0,0,6,0,0,4,2,0,0,0,5,0,0,0,0,1,0,0,0,0,7,0,2,0,0,8,7,0,0,0,3,0,0,0,0,4,0,8,0,0,0,0,6,0,0,1,0,5,0,0,6,0,0,0,0,0,0};
        for(int i=0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
               // grid[i].push_back(g[9*i+j]);
               grid[i][j]=g[9*i+j];
            }
        }
        }

        else{
            cout<<"Please Enter a Valid Level";
        }

       
    }
};


class Sudokobase : public Grid{
    public:
        int N;
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

class Checker : public Grid{

    public:
       bool isPresentInCol(int col, int num){ //check whether num is present in col or not
       for (int row = 0; row < 9; row++)
          if (grid[row][col] == num)
             return true;
       return false;
    }
    bool isPresentInRow(int row, int num){ //check whether num is present in row or not
       for (int col = 0; col < 9; col++)
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
       for (row = 0; row < 9; row++)
          for (col = 0; col < 9; col++)
             if (grid[row][col] == 0) //marked with 0 is empty
                return true;
       return false;
    }
    bool isValidPlace(int row, int col, int num){
       //when item not found in col, row and current 3x3 box
       return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
    col - col%3, num);
    }
};
 

//friend functions - isValid and findEmptyPlace

class Solver : public Checker,public Grid{
    public:
    bool solveSudoku(){
       int row,col;
       if (!findEmptyPlace(row, col))
          return true; //when all places are filled
        //cout<<row<<" "<<col<<endl;
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


class User{
    public:
    string name;
    string displayMessage;
    int id;

    User(string name)
    {
        this->name= name;
        this->id= INT_MIN;
        cout<<"Welcome: "<<name<<endl<<"Id: "<<id;
    }

    User(string n,int d){
       this->name= n;
       this->id= d;
       cout<<"Welcome: "<<n<<endl<<"Id: "<<id;
    }
    
};

int main(){
    
    string n;
    int i;
    Grid h;
    vector<int> res;
    cout<< "Welcome To Sudoko Mania"<<endl;
    cout<<"Please Enter Your Name: ";
    getline(cin,n);
    cout<<"Please Enter your ID: ";
    cin>>i;
    if(i<0){
      User U(n);
      cout<<"Cannot participate"; 
    }
    else{
      User U(n,i);  
    }

    cout<<endl<<"Please Enter any of the following Option : \n 1. Solver \n 2. Checker \n 3. Exit"<<endl;
    
    int opt=0;
    cin>>opt;

    if(opt==1)
    {
        cout<<"Do you want to use your own grid?(y/n)"<<endl;
        char stat;
        cin>>stat;
        
        if(stat=='y')
        {
            cout<<"Please enter your grid:";
            for(int i=0;i<81;i++)
            { int num;
                cin>>num;
                res.push_back(num);
            }
            h.Griding(res);
        }
        else{
            cout<<"Displaying a Sample Sudoko, Pick a number between [1-3]"<<endl;
            int a;
            cin>>a;
            h.Gridgenerate(a);
            cout<<"sample"<<endl;
            printGrid(grid);
            Solver sol;
            sol.solveSudoku();
            cout<<"Solved"<<endl;
            printGrid(grid);
        }
        
    }
       return 0;
}
