#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H
#include <stdexcept>
class LidarDriver{

public:
const int BUFFER_DIM = 10;
const int MAX_RANGE = 180;
//constructors
LidarDriver(void){};
LidarDriver(double ang_res);
//member functions
void new_scan(std::vector<double> scan);
std::vector<double> get_scan(void);
void clear_buffer(void);
double get_distance(double angle) const;
void operator<<(std::vector<double> scan) const;

private:
double res = 1;
std::vector<std::vector<double>> buffer(BUFFER_DIM, std::vector<double>(max_range/res+1));
int oldest_scan = 0;
int newest_scan = 0;
void increment(int index);
};

#endif // LIDARDRIVER_H