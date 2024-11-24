#include <iostream>
#include <fstream>
#include <random>

using namespace std;


void read_from_file(void);
void test_random(void);
int main(void){}

void read_from_file(void){
  string text;
  ifstream MyFile("file.txt");
  while(getline(MyFile, text)){
    cout << text;
  }
  MyFile.close();
}

void test_random(){

  int lower = 0;
  int upper = 2;
  std::default_random_engine rnd{std::random_device{}()};//permetter di generare i numeri random 
  std::uniform_real_distribution<double> dist(lower, upper);//per far si che ogni numero abbia la stessa probabilità di uscire

  for(int i = 0; i < 10; i++)std::cout << dist(rnd) << std::endl; ;//genera un numero random compreso nella distribuzione uniforme ,
                                                                   // quindi tra upper e lower
}
