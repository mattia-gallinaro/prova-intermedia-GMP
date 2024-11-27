#include <fstream>
#include <random>
#include "../include/LidarDriver.h"

//funzione che genera distanze e le restituisce com std::vector<double>
std::vector<double> generate_distances(void);

//funzione che stampa std::vector<double>
void print_vector(const std::vector<double>& v);

//funzione che stampa la distanza relativa ad un dato angolo (usato come verifica di get_distance())
void print_angle(const std::vector<double>& v,int position);

int main(void){
  
  LidarDriver driver_test{};//test costruttore vuoto -> commentare / decommentare i costruttori per usare un costruttore diverso
  //LidarDriver driver_test{0.3}

  //test di get_scan() con buffer vuoto
    try{
      driver_test.get_scan();
    }catch(std::invalid_argument e) {
      std::cout << "il buffer e' vuoto" << std::endl;
    }


  //test di new_scan()
    std::vector<double> distances = generate_distances();
    for(int i = 0 ; i<LidarDriver::BUFFER_DIM+5; i++)
    {
      driver_test.new_scan(distances);//inserisco una nuova scansione nel buffer
      distances = generate_distances();
    }


  //test di get_scan()
  for(int i = 0 ; i < LidarDriver::BUFFER_DIM; i++)
  {
    std::vector<double> v = driver_test.get_scan();
    print_vector(v);
  }


  //test di clear_buffer(), verifico poi con get_scan() che sia effettivamente vuoto il buffer
  for(int i = 0 ; i<LidarDriver::BUFFER_DIM+5; i++)
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


  //test di get_distance()
  driver_test.new_scan(distances);
  double angle = 104;//angolo cercato in [0,180]
  std::cout<<"distance at angle "<< angle<<"° : "<<driver_test.get_distance(angle)<<std::endl;
  int position = (int) std::round(angle/driver_test.get_res());
  print_angle(distances,position);//verifico che l'angolo dato da get_distance() sia corretto 

  //test di overload << per oggetti LidarDriver
  std::cout<<driver_test<<std::endl;
  print_vector(distances);//verifico 

  return 0;
}

//vedi commento dichiarazione
std::vector<double> generate_distances(void){
  int lower = 0;
  int upper = 2;
  std::default_random_engine rnd{std::random_device{}()};//permette di generare i numeri random 
  std::uniform_real_distribution<double> dist(lower, upper);//per far si che ogni numero abbia la stessa probabilità di uscire
  std::vector<double> buff(181);//scansioni da inserire di 181 elementi, dunque saranno meno di quelli richiesti dalle scansioni del buffer in caso la risoluzione angolare sia <1
  for(int i = 0; i < 181; i++) buff[i] = dist(rnd);
  return buff;
}

//vedi commento dichiarazione
void print_vector(const std::vector<double>& v)
{
  for(double i : v) std::cout << i << " ";
  std::cout<< std::endl;
}

//vedi commento dichiarazione
void print_angle(const std::vector<double>& v,int position)
{
  std::cout<<v[position]<<std::endl; 
}