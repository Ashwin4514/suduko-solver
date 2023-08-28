#include<iostream>
#include<istream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;
 
class loginmanager{
//this class contains the functions for the login manager

public:
bool login()
    {
       int count;
       string user,pass,u,p;
       system("cls");
       cout<<"please enter the following details"<<endl;
       cout<<"USERNAME :";
       cin>>user;
       cout<<"PASSWORD :";
       cin>>pass;
      
       ifstream input("database.txt");
       while(input>>u>>p)
       {
               if(u==user && p==pass)
      
               {
                       count=1;
                       
               }
       }
       input.close();
       
               if(count==1)
        {        
               cout<<"\nHello "<<user;
               
               return true;
        }
       else
       {
              
               return false;
       }
        return false;
    }
 
void registr()
    {
       string reguser,regpass,ru,rp;
       system("cls");
       cout<<"Enter the username :";
       cin>>reguser;
       cout<<"\nEnter the password :";
       cin>>regpass;
      
       ofstream reg("database.txt",ios::app);
       reg<<reguser<<' '<<regpass<<endl;
       system("cls");
       cout<<"\nRegistration Sucessful\n";
      
      
    }
 
void forgot()
    {
       int ch;
       system("cls");
       cout<<"Forgotten ? We're here for help\n";
       cout<<"1.Search your id by username"<<endl;
       cout<<"2.Search your id by password"<<endl;
       cout<<"3.Main menu"<<endl;
       cout<<"Enter your choice :";
       cin>>ch;
       switch(ch)
       {
               case 1:
               {
                       int count=0;
                       string searchuser,su,sp;
                       cout<<"\nEnter your remembered username :";
                       cin>>searchuser;
                      
                       ifstream searchu("database.txt");
                       while(searchu>>su>>sp)
                       {
                               if(su==searchuser)
                               {
                                       count=1;
                               }
                       }
                       searchu.close();
                       if(count==1)
                       {
                               cout<<"\n\nHurray, account found\n";
                               cout<<"\nYour password is "<<sp;
                               cin.get();
                               cin.get();
                               system("cls");
                       }
                       else
                       {
                               cout<<"\nSorry, Your userID is not found in our database\n";
                               cout<<"\nPlease kindly contact your system administrator for more details \n";
                               cin.get();
                               cin.get();
                       }
                       break;
               }
               case 2:
               {
                       int count=0;
                       string searchpass,su2,sp2;
                       cout<<"\nEnter the remembered password :";
                       cin>>searchpass;
                      
                       ifstream searchp("database.txt");
                       while(searchp>>su2>>sp2)
                       {
                               if(sp2==searchpass)
                               {
                                       count=1;
                               }      
                       }
                       searchp.close();
                       if(count==1)
                       {
                               cout<<"\nYour password is found in the database \n";
                               cout<<"\nYour Id is : "<<su2;
                               cin.get();
                               cin.get();
                               system("cls");
                       }
                       else
                       {
                               cout<<"Sorry, We cannot found your password in our database \n";
                               cout<<"\nkindly contact your administrator for more information\n";
                               cin.get();
                               cin.get();
                       }
              
                       break;
               }
              
               case 3:
               {
                       cin.get();
               }
               default:
                       cout<<"Sorry, You entered wrong choice. Kindly try again"<<endl;
                       forgot();
       }
    }
};
 
class graphicsdata
{
 public:
 void welcomeScreen(){
 cout<<"***********************************************************************\n\n\n";
 cout<<"                      Welcome to login page                              \n\n";
 cout<<"*******************           MENU        *******************************\n\n";
}
};
/*int main()
{
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
               case 1:
                       l.login();
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
  return(0);
       
}*/
 
 
