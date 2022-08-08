
//               adec.cpp
#include <iostream>
#include <fstream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main()
{
  tFSM Adec;
///////////////////////
//������� ���� ��� � �������� �����
  addrange(Adec, 0, '0', '9', 1);
  addstr(Adec, 0, "+-", 6);
  addrange(Adec, 1, '0', '9', 1);
  addstr(Adec, 1, ".", 2);
  addrange(Adec, 2, '0', '9', 3);
  addrange(Adec, 3, '0', '9', 3);
  addstr(Adec, 3, "eE", 4);
  addrange(Adec, 4, '0', '9', 5);
  addstr(Adec, 4,"+-",7);
  addrange(Adec, 5, '0', '9', 5);
  addrange(Adec, 6, '0', '9', 1);
  addrange(Adec, 7, '0','9',5);
 Adec.final(5);
///////////////////////
  cout << "Number of states = " << Adec.size()
       << "\n";

  char buf[1000];
  do{
   char* name="dec.ss";
    ifstream file(name);
    if(!file){
 cout<<"Can't open file "<< name << " !\n";
 continue;
            }
    while(file){
     *buf=0;
     file.getline(buf,1000);
     cout<< ">"<<buf<<endl;
  int res = Adec.apply(buf);
  cout << setw(res?res+1:0) << "^"
       << endl;
     }//whil
 } while(false);
 return 0;
}

