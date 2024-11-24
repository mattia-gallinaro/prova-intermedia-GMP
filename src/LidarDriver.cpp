#include "LidarDriver.h"
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
    
    std::vector<double> container(181, 0);//sto inizializzando un nuovo vettore double con 181 valori a 0 che conterra' le letture da restituire
    std::copy( buffer[oldest_scan].begin(), buffer[oldest_scan].end(), container);
    for(int i = 0; i < buffer[oldest_scan].size() ; i++){
        buffer[oldest_scan][i] = 0;
    }
    if(oldest_scan == newest_scan){
        oldest_scan = 0;
        newest_scan = -1;
    }//lo faccio perchè ho "eliminato" l'ultima scansione presente
    return container;
}
//sono due foreach,  li devo testare
void clear_buffer(void)
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

double get_distance(double angle) const 
{
    if (angle < 0 || angle > 180)throw std::invalid_argument("angle not valid must be between 0 and 180"); //così siamo sicuri che si possa cercare un'angolo 
    // buffer vuoto
    if (newest_scan == - 1)throw std::invalid_argument("angle not valid must be between 0 and 180");// per ora ho messo invalid_argument , bisogna modificarlo con uno più specifico per indicare che il buffer non contiene scansioni

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

std::vector<double> get_newest_scan(void) const
{
    if(newest_scan==-1)throw std::invalid_argument("il buffer è vuoto");
    return buffer[newest_scan];
}

double get_res(void) const
{
    return res;
}

private:

int increment(int index)
{
    if(index==BUFFER_DIM-1) index = 0;
    else index++;
    return index;
}

};


std::ostream &operator<<(std::ostream &out, const LidarDriver &lid)
{
    try{
    std::vector<double> scan = lid.get_newest_scan();
    double ang_res = lid.get_res();   
    string measures = "";
    double current_angle = 0;

    for(double i : scan)
    {
        measures += current_angle + "° : "+ i + "\n";
        if((current_angle+ang_res)<LidarDriver.MAX_RANGE)current_angle += ang_res;
        else current_angle = LidarDriver.MAX_RANGE;
    } 
    return out << measures;
    } 
    catch(invalid_argument e)
    {
        return out << e << "\n";
    }
}
