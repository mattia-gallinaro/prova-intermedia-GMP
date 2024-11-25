#include <fstream>
#include <random>
#include "../include/LidarDriver.h"

std::vector<double> generate_distances(void);
void print_vector(const std::vector<double>& v);
void print_angle(const std::vector<double>& v,int position);

int main(void){
  
  LidarDriver driver_test{};//test costruttore vuoto

  //testing di get_scan con buffer vuoto
    try{
      driver_test.get_scan();
    }catch(std::invalid_argument e) {
      std::cout << "il buffer e' vuoto" << std::endl;
    }
  //testing di new_scan
    std::vector<double> distances = generate_distances();
    for(int i = 0 ; i<LidarDriver.BUFFER_DIM+5; i++)
    {
      driver_test.new_scan(distances);//inserisco una nuova scansione nel buffer
      distances = generate_distances();
    }
  //testing di get_scan
  for(int i = 0 ; i < LidarDriver.BUFFER_DIM; i++)
  {
    std::vector<double> v = driver_test.get_scan();
    print_vector(v);
  }
  //testing di clear buffer
  for(int i = 0 ; i<LidarDriver.BUFFER_DIM+5; i++)
    {
      driver_test.new_scan(distances);
      distances = generate_distances();
    }
  driver_test.clear_buffer();
  try{
      driver_test.get_scan();
    }catch(std::invalid_argument e) {
      std::cout << "il buffer e' vuoto" << std::endl;
    }

  //test get_distance
  driver_test.new_scan(distances);
  double angle = 104;
  std::cout<<"distance at angle "<< angle<<"° : "<<driver_test.get_distance(angle)<<std::endl;
  int position = (int) std::round(angle/driver_test.get_res());
  print_angle(distances,position);

  //test di overload <<
  std::cout<<driver_test<<std::endl;
  print_vector(distances);

  return 0;
}


std::vector<double> generate_distances(void){
  int lower = 0;
  int upper = 2;
  std::default_random_engine rnd{std::random_device{}()};//permetter di generare i numeri random 
  std::uniform_real_distribution<double> dist(lower, upper);//per far si che ogni numero abbia la stessa probabilità di uscire
  std::vector<double> buff(181);
  for(int i = 0; i < 181; i++) buff[i] = dist(rnd);
  return buff;
}

void print_vector(const std::vector<double>& v)
{
  for(double i : v) std::cout << i << " ";
  std::cout<< std::endl;
}

void print_angle(const std::vector<double>& v,int position)
{
  std::cout<<v[position]<<std::endl; 
}