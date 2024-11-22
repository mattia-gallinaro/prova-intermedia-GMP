#include <iostream>
#include <fstream>
using namespace std;


void read_from_file(void);

int main(void){}

void read_from_file(void){
  string text;
  ifstream MyFile("file.txt");
  while(getline(MyFile, text)){
    cout << text;
  }
  MyFile.close();
}
