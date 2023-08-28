#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
#include"user.cpp"
using namespace std;

class Grid{                                                                    //The class used to control making grids of a suduko. Its implemented as an Abstract class.
    public:
    int lvl=0;
    int N = 9;
    static int grid[9][9];                                                     

    ~Grid(){                                                                    //Used to initialize a 9*9 suduko grid with 0s.
        for(int i =0;i<9;i++){
            for(int j =0;j<9;j++){
                grid[i][j] = 0;
            }
        }                                                                       
    }
    //vector<vector<int>> grid;

    //virtual void takeInput();

    void printGrid(){                                                          //PrintGrid function is used to print the changed grid                       
            for (int row = 0; row < N; row++){                                 //In a formatted fashion with.
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
    virtual void Griding(vector<int> k)=0;                                     //Implemented a Pure Virtual Function Griding that later takes an input vector
                                                                               //of 81 numbers implementation of which is given in the derived classe.
};

int Grid::grid[9][9];

class Checker : public Grid{                                                  //Checker Class is used to decide whether the given solved suduko by the user is correct or not.
                                                                              //Also inherited by the solver class.
    protected:
       bool isPresentInCol(int col, int num){                                 //check whether num is present in col or not
       for (int row = 0; row < 9; row++)
          if (grid[row][col] == num)
             return true;
       return false;
    }
    bool isPresentInRow(int row, int num){                                   //check whether num is present in row or not
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
    public:

   void Griding(int val, int i, int j){                                     //Function used to add val in the (i,j)th point in the suduko grid.
        grid[i][j] = val;
    }
    void Griding(vector<int> k){                                            //Since Abstract class is inherited, the implementation of the pure virtual function 
        for(int i=0;i<9;i++)
          {
              for(int j=0;j<9;j++)
              {
                grid[i][j] = (k[9*i+j]);
              }
          }                                                    //Hence, this is done.
    }
    bool findEmptyPlace()                                                   //Method to find empty spaces to fill in the suduko grid. 
       {                                                                    //Any point in suduko as 0 is considered empty. 
           for(int i=0;i<9;i++)                                             //Traverses the whole 9*9 grid and searches for 0s if any.
           {
               for(int j=0;j<9;j++)
               {
                   if(grid[i][j]==0)
                     return true;
               }
           }
           return false;
       }
       bool isValidPlace()                                                  //Method to find if the count of each number in the solved suduko is 9.
       {
          unordered_map<int,int> validation;                                //An unordered map is used to keep a track of each number and its frequency. 
          for(int i=1;i<10;i++)
          {
                validation[i]=9;
          } 
          for(int i=0;i<9;i++)                                             //On traversing the whole suduko grid, Each occurence of a number (1-9) is noted and its
          {                                                                //frequency in the validation map is reduced.
              for(int j=0;j<9;j++)
              {
                  validation[grid[i][j]]--;
              }
          }
          for(int i=1;i<=9;i++)
          {
              if(validation[i]!=0)                                         //If the validation map has frequency of all numbers as 0 then only it is valid as that would 
                return false;                                              //mean that we dont have repeated numbers in any block,row or column.
          }
        return true;   
       }
    bool findEmptyPlace(int &row, int &col){                              //get empty location and update row and column
       for (row = 0; row < 9; row++)                                      //This is used when the suduko is solved to find empty places to fill. 
          for (col = 0; col < 9; col++)
             if (grid[row][col] == 0)                                     //marked with 0 is empty
                return true;
       return false;
    }
    bool isValidPlace(int row, int col, int num){                         //We pass a number to this function and corresponding (row,col) to find out if its in the right place. 
       //when item not found in col, row and current 3x3 box              //Implemented Compile Time Polymorphism in this case. 
       return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,
    col - col%3, num);
    }

};
 
 char checks(Checker *E)                                                                //Decision function based out of the observations made from the 
                                                                                        //above checker class functions.
       {                                                                             
           bool flag_1= E->findEmptyPlace();
           bool flag_2= E->isValidPlace();

           if(flag_1==false && flag_2==true)
           {
               return 'T';
           }
           else if(flag_1==true && flag_2==false)
           {
              cout<<"You still have Empty Spaces";
              return 'F';       
           }
           else if(flag_1==false && flag_2==false)
           {
              cout<<"Some values may be Repeated or Misplaced";
              return 'F';
           }
    return 'F';
}



class Solver : public Checker{                                                   //Solver Class is used to solve the grid given by user. 
    public:
    void Griding(int val, int i, int j){
        grid[i][j] = val;
    }
     void Griding(int a)                                                        //this function is used to solve default grids based on level passed by user. 
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
    void Griding(vector<int> k){               
        for(int i=0;i<9;i++)
          {
              for(int j=0;j<9;j++)
              {
                grid[i][j] = (k[9*i+j]);
              }
          }
    }
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


class User{     //class for user details
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

    ~User(){
        cout<<"Thank you! See you again!!"<<endl;
    }
    
};

class Game : public Checker{
    private:
    int c = 0;
    int count(){
        for(int i = 0;i<9;i++){
            for(int j =0;j<9;j++){
                c++;
            }
        }
        return c;
    }

    public:
    
     void Griding(int a)
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
    void solve(){
        int a = count();
        int k[3];
        
        while(a!=0){
            cout<<"Enter ROW COL VALUE in sequence"<<endl;
            for(int i =0;i<3;i++){
                cin>>k[i];
            }   
            if(grid[k[0]][k[1]]==0){
                if(isValidPlace(k[0],k[1],k[2])){
                    grid[k[0]][k[1]]= k[2];
                    a--;
                    cout<<"Success"<<endl;
                    cout<<endl;
                    printGrid();
                }
                else{
                    cout<<endl;
                    cout<<"InValid! Value not allowed"<<endl;
                    cout<<endl;
                    printGrid();
                }
            }
            else{
                cout<<endl;
                cout<<"Invalid! Node already present!"<<endl;
                cout<<endl;
                printGrid();
            }   
        }
        
    }
};

int main(){
    
    string n;
    int i;
    //Grid* g = new Grid();
    //Solver h;
    vector<int> res;
    /*cout<< "Welcome To Sudoko Mania"<<endl;
    cout<<"Please Enter Your Name: ";
    getline(cin,n);
    cout<<"Please Enter your ID: ";
    cin>>i;

    User* U = new User(n,i);*/

    int choice;
       loginmanager l;
       graphicsdata g;
       g.welcomeScreen();
       do{
 
       cout<<"1.LOGIN"<<endl;
       cout<<"2.REGISTER"<<endl;
       cout<<"3.FORGOT PASSWORD (or) USERNAME"<<endl;
       cout<<"4.Exit"<<endl;
       cout<<"\nEnter your choice :";
       cin>>choice;
       cout<<endl;
       switch(choice)
       {
               case 1:  {
                   try{
                       bool status = l.login();
                       if(status == true){
                            cout<<"\nLOGIN SUCESSs\nWe're glad that you're here.\nThanks for logging in";
                             while(1){  
        cout<<endl<<"Please Enter any of the following Option : \n 1. Solver \n 2. Checker \n 3. Game \n 4. Exit \n"<<endl;
    int opt=0;
    cin>>opt;

    if(opt==1)
    {   Solver* g = new Solver();
        cout<<"Do you want to use your own grid?(y/n)"<<endl;
        char stat;
        cin>>stat;
        
        if(stat=='y')
        {   
            cout<<"Enter in Matrix form(y/n)\n";
            char d;
            cin>>d;
            
            if(d=='y'){
                int val;
                for(i=0;i<9;++i){
                    for(int j=0;j<9;j++){
                        cout<<"hello enter your sudoku one by one. The grid will be updated as you enter the sudoku\n\nEnter 0 for the unfilled places:\n";
                        
                        g->printGrid();//function to print the 9*9 matrix h.grid
                        cin>>val;
                        
                        g->Griding(val,i,j);
                        // function to updathe 9*9 array h.grid with the value val at position pos
                        //clrscr();
                        system("cls");
                    }
                }
                

            }
            else{
                cout<<"Please enter your grid:";
                for(int i=0;i<81;i++)
                {   int num;
                    cin>>num;
                    res.push_back(num);
                }
                g->Griding(res);
            }
            cout<<"Your Entered Matrix:\n";
            g->printGrid();
            g->solveSudoku();
            cout<<"Solved"<<endl;
            g->printGrid();
            
            
        }
        else{
            cout<<"Displaying a Sample Sudoko, Pick a number between [1-3]"<<endl;
            int a;
            cin>>a;
            g->Griding(a);
            cout<<"sample"<<endl;
            g->printGrid();
            Solver* g = new Solver();
            g->solveSudoku();
            cout<<"Solved"<<endl;
            g->printGrid();
        }
        delete g;
        
    }
    if(opt==2)
    {   
       
        Checker* c= new Checker();
        cout<<"Please Enter your Sudoko: \n";
        int val;
        for(i=0;i<9;++i){
            for(int j=0;j<9;j++){
            cout<<"hello enter your sudoku one by one. The grid will be updated as you enter the sudoku\n\nEnter 0 for the unfilled places:\n";
            //Checker* c= new Checker();
            c->printGrid();//function to print the 9*9 matrix h.grid
            cin>>val;
            
            c->Griding(val,i,j);
            // function to updathe 9*9 array h.grid with the value val at position pos
            //clrscr();
            system("cls");
            }
        }
        
        int status = checks(c);
        if(status=='T')
          cout<<endl<<"Correct!!!";
        else
          cout<<endl<<"Incorrect! Please solve Again";  
         
          //delete C;
          delete c;
    }

    if(opt==3){
        Game* g = new Game();
        cout<<"Displaying a Sample Sudoko, Pick a number between [1-3]"<<endl;
        int a;
        cin>>a;
        g->Griding(a);
        cout<<"Unsolved Sudoku"<<endl;
        g->printGrid();
        Game* game = new Game();
        game->solve();
        delete game;
        delete g;
    }

    if(opt==4)
    {
        cout<<"Thankyou!See You Again";
        return 0;
    }
                             }}
                       else{
                           throw status;
                       }
                   }
                   catch(bool myStatus){
                       cout<<"\nLOGIN ERROR\nPlease check your username and password\n"<<myStatus;
                   }
                    
                        }
                       break;
               
               case 2:
                       l.registr();
                       break;
               case 3:
                       l.forgot();
                       break;
               case 4:
 
                       cout<<"Thanks for using this program\n\n\n";
                       break;
               default:
                       system("cls");
                       cout<<"You've made a mistake , give it a try again\n"<<endl;
       }
       
       }while(choice!=4);

  
    //delete g;
    //delete U;
    return 0;
}
 // 3 0 6 5 0 8 4 0 0 5 2 0 0 0 0 0 0 0 0 8 7 0 0 0 0 3 1 0 0 3 0 1 0 0 8 0 9 0 0 8 6 3 0 0 5 0 5 0 0 9 0 6 0 0 1 3 0 0 0 0 2 5 0 0 0 0 0 0 0 0 7 4 0 0 5 2 0 6 3 0 0
 // 0 1 0 0 2 0 3 0 0 0 0 2 0 0 3 0 4 0 0 8 0 0 0 0 0 0 6 0 0 4 7 0 0 0 3 0 0 0 0 6 0 0 0 0 8 0 7 0 0 9 8 0 0 0 3 0 0 0 0 4 0 9 0 0 0 0 8 0 0 1 0 4 0 0 6 0 0 0 0 0 0
 // 0 0 0 2 0 4 8 1 0 0 4 0 0 0 8 2 6 3 3 0 0 1 6 0 0 0 4 1 0 0 0 4 0 5 8 0 6 3 5 8 2 0 0 0 7 2 0 0 5 9 0 1 0 0 9 1 0 7 0 0 0 4 0 0 0 0 6 8 0 7 0 1 8 0 0 4 0 3 0 5 0



 // 4 3 5 2 6 9 7 8 1 6 8 2 5 7 1 4 9 3 1 9 7 8 3 4 5 6 2 8 2 6 1 9 5 3 4 7 3 7 4 6 8 2 9 1 5 9 5 1 7 4 3 6 2 8 5 1 9 3 2 6 8 7 4 2 4 8 9 5 7 1 3 6 7 6 3 4 1 8 2 5 9
