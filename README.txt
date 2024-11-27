Comandi per testare LidarDriver con g++:   
- Raggiungere la cartella "prova-intermedia-GMP"
- all'interno della cartella "prova-intermedia-GMP" dare i seguenti comandi:
    - "cd src"
    - "g++ LidarDriver.cpp main.cpp -o main"
    - "./main"

Dovrebbe risultare cosi :

~ -> percorso della cartella in cui è presente "prova-intermedia-GMP"

~$ cd prova-intermedia-GMP/
~/prova-intermedia-GMP$ cd src/
~/prova-intermedia-GMP/src$ g++ LidarDriver.cpp main.cpp -o main
~/prova-intermedia-GMP/src$ ./main


Membri del gruppo:
    - Mattia Gallinaro
    - Diego Marchini
    - David Popusoi

Chi ha sviluppato cosa:
    - Mattia Gallinaro:
        - header della clase LidarDriver
        - In LidarDriver.cpp:
            - metodo get_scan()
            - metodo clear_buffer();
            - metodo get_distance();
            - metodo is_buffer_empty();
        - In main.cpp:
            - metodo generate_distances();
            - test per i metodi della classe LidarDriver
    - Diego Marchini:
        - header della clase LidarDriver
        - In LidarDriver.cpp:
            - costruttori di LidarDriver ; 
            - metodo new_scan() ;
            - metodo get_res() ;
            - metodo get_newest_scan() ;
            - overload dell'operatore << ;
        - In main.cpp:
            - metodo print_vector();
            - metodo print_angle() ;
            - test per i metodi della classe LidarDriver
    -David Popusoi: 
        - header della classe LidarDriver;
        - In LidarDriver.cpp:
            - metodo get_scan();
            - metodo clear_buffer();
            - metodo get_distance();
        - in main.cpp:
            - test per le i metodi della classe LidarDriver

Funzione aggiunte rispetto a quelle richieste :
    - in header e LidarDriver.cpp son state aggiunte:
        - "int increment(int index) " : ritorna l'indice aumentato di 1 , oppure 0 nel caso in cui l'indice aveva raggiunto la fine del buffer 
        - "bool is_buffer_empty(void) const" : controlla se il buffer non contenga scansioni verificando se newest_scan ha valore -1 , il -1 indica che non ci sono scansioni presenti nel buffer
        - "double get_res(void) const"  : ritorna il valore della risoluzione angolare
        - "std::vector<double> get_newest_scan(void) const" : ritorna l'ultima scansione aggiunta nel buffer, se non ce ne sono presenti , ritorna un errore
    - in main.cpp
        - " std::vector<double> generate_distances(void) " :  genera un vettore di 361 elementi double generati randomicamente
        - " void print_vector(const std::vector<double>& v) " : funzione per stampare il vettore
        - " void print_angle(const std::vector<double>& v,int position) " : funzione che stampa la distanza relativa ad un dato angolo, serve come verifica del metodo get_distance della classe LidarDriver
