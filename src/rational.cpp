class LinearDriver{

public:
const int BUFFER_DIM = 10;
const int max_range = 180;
//constructors
LinearDriver(void){};
LinearDriver(double ang_res)
{
    if(ang_res>=0.1 && ang_res<=1) res = ang_res;
    else throw invalid_argument("angular resolution not valid, must be [0.1,1]");
}
//member functions
void new_scan(std::vector<double> scan)
{
    if(newest_scan == BUFFER_DIM-1) 
    {
        newest_scan = 0;
        buffer[newest_scan] = scan;
    }
    else buffer[++newest_scan] = scan;
}//ricordare di modificare eventualmente oldest_scan(sennò portq problemi in get_scan())

std::vector<double> get_scan(void)
{

}
void clear_buffer(void);
double get_distance(double angle) const;
void operator<<(std::vector<double> scan) const;
};