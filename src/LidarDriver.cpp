#include "../include/LidarDriver.h"



//constructors
LidarDriver::LidarDriver(void) 
    : buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / res) + 1))
{}

LidarDriver::LidarDriver(double ang_res)
    : res{ang_res}, buffer(BUFFER_DIM, std::vector<double>((MAX_RANGE / res) + 1))
{
    if(ang_res<0.1 || ang_res>1)throw std::invalid_argument("angular resolution not valid, must be [0.1,1]");
}
//member functions
void LidarDriver::new_scan(const std::vector<double>& scan)
{
    for(double i : scan)//controlla la presenza di eventuali valori negativi
    {
        if(i< 0) throw std::invalid_argument("negative values not allowed");
    }
    int size_to_copy = (MAX_RANGE / res) + 1;
    if(increment(newest_scan)== oldest_scan && !is_buffer_empty()) oldest_scan = increment(oldest_scan);//controlli necessari garantire la circolarità del buffer
    newest_scan = increment(newest_scan);
    buffer[newest_scan].resize(size_to_copy,0);//settiamo a 0 i valori della scansione riportando la dimensione logica delle scansioni del buffer al valore giusto
    if(size_to_copy > scan.size()) size_to_copy = scan.size();//verifica se le scansioni esterne sono più piccole (se sono  troppo grandi le tronca automaticamente)
    std::copy(scan.begin(), scan.begin() + size_to_copy, buffer[newest_scan].begin());
}

std::vector<double> LidarDriver::get_scan(void)
{
    if(is_buffer_empty())throw std::invalid_argument("Il buffer e' vuoto");
    std::vector<double> container((MAX_RANGE / res) + 1, 0);//container usato per restituire la scansione che viene rimossa dal buffer
    std::copy(buffer[oldest_scan].begin(), buffer[oldest_scan].end(), container.begin());//copia della scansione da rimuovere su container
    buffer[oldest_scan].clear();//rimozione della scansione più vecchia dal buffer
    if(oldest_scan == newest_scan){//setto gli indici in caso abbia rimosso l'ultimo elemento
        oldest_scan = 0;
        newest_scan = -1;
    }
    else{//la scansione più vecchia ora è cambiata
        oldest_scan = increment(oldest_scan);
    }
    return container;
}

void LidarDriver::clear_buffer(void)
{
    if(!is_buffer_empty()){
    for(auto i: buffer) //rimuovo ogni scansione dal buffer                    
    {
        i.clear();//clear() funzione di std::vector
    }
    oldest_scan = 0;
    newest_scan = -1; 
}
}

double LidarDriver::get_distance(double angle) const 
{
    if (angle < 0 || angle > MAX_RANGE)throw std::invalid_argument("angle not valid must be between 0 and 180"); 
    
    if (is_buffer_empty())throw std::invalid_argument("Il buffer e' vuoto");

    double num_lettura = angle / res; //necessario per trovare l'indice da andare a leggere nell'ultima scansione fatta
    int index = (int) std::round(num_lettura);
    return buffer[newest_scan][index];
}

std::vector<double> LidarDriver::get_newest_scan(void) const
{
    if(is_buffer_empty())throw std::invalid_argument("Il buffer è vuoto");
    return buffer[newest_scan];
}

double LidarDriver::get_res(void) const
{
    return res;
}


int LidarDriver::increment(int index)
{
    if(index==BUFFER_DIM-1) index = 0;//incremento circolare -> se sono alla fine ricomincio da posizione 0 
    else index++;
    return index;
}

bool LidarDriver::is_buffer_empty(void) const
{
return newest_scan == -1;
}


std::ostream &operator<<(std::ostream &out, const LidarDriver &lid)
{
    try{
    std::vector<double> scan = lid.get_newest_scan();
    double ang_res = lid.get_res();   
    std::string measures = "";
    double current_angle = 0;

    for(double i : scan)//creo una stringa contenente angoli e reltive misurazioni dell'ultima scansione fatta presente nel buffer
    {
        measures += std::to_string(current_angle) + "° : "+ std::to_string(i) + "\n";
        if((current_angle+ang_res)<LidarDriver::MAX_RANGE)current_angle += ang_res;
        else current_angle = LidarDriver::MAX_RANGE;
    } 
    return out << measures;
    } 
    catch(std::invalid_argument e)
    {
        return out <<" il buffer è vuoto "<< "\n";
    }
}
