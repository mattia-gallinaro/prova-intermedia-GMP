#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
class LidarDriver{

public:
static const int BUFFER_DIM{10};
static const int MAX_RANGE{180};

//CONSTRUCTORS


LidarDriver(void);
LidarDriver(double ang_res);

//MEMBER FUNCTIONS

/* 
new_scan() inserisce una nuova scansione nel buffer eventualmente sovrascrivendo
la scansione più vecchia, se le scansioni da inserire hanno dimensione diversa da quella delle
scansioni del buffer vengono aggiunti degli 0 nella scansione corrente (del buffer). Le scansioni da inserire
 vengono troncate in caso abbiamo dim_scansione > buffer[0].dim (vengono inseriti solo i primi n valori)
  */ 
void new_scan(const std::vector<double>& scan);

/*
get_scan() ritorna la più vecchia scansione presente nel buffer e poi la rimuove dal buffer. Se non è presente 
alcuna scansione nel buffer (buffer vuoto) lancia un'eccezione indicando che il buffer è vuoto
*/
std::vector<double> get_scan(void);

/*
clear_buffer() rimuove tutte le scansioni dal buffer
*/
void clear_buffer(void);

/*
get_distance() ritorna il valore misurato all'angolo più vicino a quello indicato come parametro nella scansione
più recente. Se tale valore si trova fuori da range [0,180] o il buffer è vuoto lancia un'eccezione
*/
double get_distance(double angle) const;

/*
get_newest_scan() è una getter function che consente di visualizzare (ritorna) la scansione 
più recente ->  usato nell'overload di << (helper function) 
*/
std::vector<double> get_newest_scan(void) const;

/*
get_res() è una getter function che consente di visualizzare (ritorna) la risoluzione angolare
 ->  usato nell'overload di << (helper function) 
*/
double get_res(void) const;

private:
double res{1};//risoluzione angolare
std::vector<std::vector<double>> buffer;//buffer contenente 10 scansioni
int oldest_scan{0};//indice della più vecchia scansione inserita (non ancora sovrascritta)
int newest_scan{-1};//indice dell'ultima scansione inserita
int increment(int index);//funzione di utilità usata per incrementare circolarmente -> rende il buffer un array circolare
bool is_buffer_empty(void) const;//funzione che indica se il buffer è vuoto
};

/*
overload dell'operatore << ,  (helper function) che consente di stampare un oggetto
di tipo LidarDriver tramite std::cout<< OGGETTO_DI_TIPO_LIDARDRIVER;
*/
std::ostream &operator<<(std::ostream &out,  const LidarDriver &lid);

#endif // LIDARDRIVER_H