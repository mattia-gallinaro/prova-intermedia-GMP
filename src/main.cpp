#include <fstream>
#include <random>
#include "../include/LidarDriver.h"

void test_random(void);
std::vector<double> generate_distances(void);

int main(void){
  test_random();
  std::vector<double> distances = generate_distances();
  LidarDriver driver_test{};
  try{
    driver_test.get_scan();
  }catch(std::invalid_argument e) {
    std::cout << e << std::
}

void test_random(){

  int lower = 0;
  int upper = 2;
  std::default_random_engine rnd{std::random_device{}()};//permetter di generare i numeri random 
  std::uniform_real_distribution<double> dist(lower, upper);//per far si che ogni numero abbia la stessa probabilità di uscire

  for(int i = 0; i < 10; i++)std::cout << dist(rnd) << std::endl; ;//genera un numero random compreso nella distribuzione uniforme ,
                                                                   // quindi tra upper e lower
}

std::vector<double> generate_distances(void){
  int lower = 0;
  int upper = 2;
  std::default_random_engine rnd{std::random_device{}()};//permetter di generare i numeri random 
  std::uniform_real_distribution<double> dist(lower, upper);//per far si che ogni numero abbia la stessa probabilità di uscire

  for(int i = 0; i < 10; i++)std::cout << dist(rnd) << std::endl; ;//genera un numero random compreso nella distribuzione uniforme ,
                                                                   // quindi tra upper e lower
}
