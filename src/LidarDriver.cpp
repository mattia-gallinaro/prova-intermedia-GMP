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
    for(double i : scan)
    {
        if(i< 0) throw std::invalid_argument("negative values not allowed");
    }
    int size_to_copy = (MAX_RANGE / res) + 1;
    if(increment(newest_scan)== oldest_scan && newest_scan!=-1) oldest_scan = increment(oldest_scan);
    newest_scan = increment(newest_scan);
    if(size_to_copy > scan.size()) {
        size_to_copy = scan.size();
        std::fill(buffer[newest_scan].begin() + size_to_copy, buffer[newest_scan].end(), 0);
    }
    std::copy(scan.begin(), scan.begin() + size_to_copy, buffer[newest_scan].begin());// permette di copiare tutti i valori possibili da scan in buffer
}

std::vector<double> LidarDriver::get_scan(void)
{
    if(newest_scan==-1)throw std::invalid_argument("Il buffer e' vuoto");
    std::vector<double> container((MAX_RANGE / res) + 1, 0);//sto inizializzando un nuovo vettore double con 181 valori a 0 che conterra' le letture da restituire
    std::copy(buffer[oldest_scan].begin(), buffer[oldest_scan].end(), container.begin());
    std::fill(buffer[oldest_scan].begin(), buffer[oldest_scan].end(), 0);//resetto l'array che contiene le misurazioni meno recenti a 0
    if(oldest_scan == newest_scan){
        oldest_scan = 0;
        newest_scan = -1;
    }//lo faccio perchè ho "eliminato" l'ultima scansione presente
    else{
        oldest_scan = increment(oldest_scan);
    }
    return container;
}
//sono due foreach,  li devo testare
void LidarDriver::clear_buffer(void)
{
    for(auto i: buffer) //auto può essere sostituito con std::vector<double>,
                        //fa si che sia il compilatore ad assegnare automaticamente il tipo di dato , è il T
    {
        for(double j : i)
            j=0;//setto i valori a 0
    }
    oldest_scan = 0;
    newest_scan = -1; //per indicare che ora il buffer non contiene più nessuna lettura
}

double LidarDriver::get_distance(double angle) const 
{
    if (angle < 0 || angle > MAX_RANGE)throw std::invalid_argument("angle not valid must be between 0 and 180"); //così siamo sicuri che si possa cercare un'angolo 
    // buffer vuoto
    if (newest_scan == - 1)throw std::invalid_argument("Il buffer e' vuoto");// per ora ho messo invalid_argument , bisogna modificarlo con uno più specifico per indicare che il buffer non contiene scansioni

    // calcola la posizione della teoretica lettura in base alla risoluzione
    // per accomodare che la risoluzione e' fornita dall'utente, arrotondo per trovare l'indice
    double num_lettura = angle / res; 
    int index = (int) std::round(num_lettura);

    //if(index < 0) return buffer[newest_scan][0]; non serve perchè non dovremmo accettare valori negativi siccome sono sempre al di fuori dell'array

    // lunghezza della scansione piu' recente, la uso per controllare che l'angolo fornito in input non sbordi
    // int newest_size = buffer[newest_scan].size();
    // angolo fornito va oltre le letture fatte, restituisci l'ultima lettura fatta
    // else if(index > newest_size) return buffer[newest_scan][newest_size - 1];  <- non dovrebbe servire perchè l'angolo che dovrebbe passare deve essere compreso tra 0 e 180 così l'utente non può leggere valori al di fuori dell'array

    return buffer[newest_scan][index];
}

std::vector<double> LidarDriver::get_newest_scan(void) const
{
    if(newest_scan==-1)throw std::invalid_argument("il buffer è vuoto");
    return buffer[newest_scan];
}

double LidarDriver::get_res(void) const
{
    return res;
}


int LidarDriver::increment(int index)
{
    if(index==BUFFER_DIM-1) index = 0;
    else index++;
    return index;
}




std::ostream &operator<<(std::ostream &out, const LidarDriver &lid)
{
    try{
    std::vector<double> scan = lid.get_newest_scan();
    double ang_res = lid.get_res();   
    std::string measures = "";
    double current_angle = 0;

    for(double i : scan)
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
