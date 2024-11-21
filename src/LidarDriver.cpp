#include "LidarDriver.h"
class LidarDriver{
private:

int increment(int index)
{
    if(index==BUFFER_DIM-1) index = 0;
    else index++;
    return index;
}

public:

const int BUFFER_DIM = 10;
const int MAX_RANGE = 180;
//constructors
LidarDriver(void){};
LidarDriver(double ang_res)
{
    if(ang_res>=0.1 && ang_res<=1) res = ang_res;
    else throw invalid_argument("angular resolution not valid, must be [0.1,1]");
}
//member functions
void new_scan(std::vector<double> scan)
{
    if(increment(newest_scan)==oldest_scan) oldest_scan = increment(oldest_scan);
    newest_scan = increment(newest_scan);
    buffer[newest_scan] = scan;
}

std::vector<double> get_scan(void)
{

}
void clear_buffer(void);
double get_distance(double angle) const;
void operator<<(std::vector<double> scan) const;
};
