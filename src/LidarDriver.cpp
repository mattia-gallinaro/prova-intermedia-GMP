#include "../include/LidarDriver.h"
class LidarDriver{

public:

//constructors
LidarDriver(void)
buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / res) + 1))
{}
LidarDriver(double ang_res)
{
    if(ang_res>=0.1 && ang_res<=1) res = ang_res;
    else throw std::invalid_argument("angular resolution not valid, must be [0.1,1]");
    buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / res) + 1));
}
//member functions
void new_scan(std::vector<double> scan)
{
    if(increment(newest_scan)==oldest_scan && newest_scan!=-1) oldest_scan = increment(oldest_scan);
    newest_scan = increment(newest_scan);
    buffer[newest_scan] = scan;
}

std::vector<double> get_scan(void)
{
    /*
    std::vector<double> container(181, 0);//sto inizializzando un nuovo vettore double con 181 valori a 0 che conterra' le letture da restituire
    std::copy( buffer[oldest_scan].begin(), buffer[oldest_scan].end(), container);
    for(int i = 0; i < buffer[oldest_scan].size() ; i++){
        buffer[oldest_scan][i] = 0;
    }
    oldest_scan = increment(oldest_scan);
    return container;
    */
};
//sono due foreach,  li devo testare
void clear_buffer(void)
{
    /*for(auto i: buffer) auto può essere sostituito con std::vector<double>,
    fa si che sia il compilatore ad assegnare automaticamente il tipo di dato , è il T
    {
        for(double j : i)
            j=0;//setto i valori a 0
    }*/
}

double get_distance(double angle) const;

private:

int increment(int index)
{
    if(index==BUFFER_DIM-1) index = 0;
    else index++;
    return index;
}

};


std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);
