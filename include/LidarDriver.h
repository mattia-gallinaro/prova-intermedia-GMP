#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H
#include <iostream>
#include <stdexcept>
class LidarDriver{

public:
const int BUFFER_DIM{10};
const int MAX_RANGE{180};

//constructors
LidarDriver(void){};
LidarDriver(double ang_res);

//member functions
void new_scan(std::vector<double> scan);
std::vector<double> get_scan(void);
void clear_buffer(void);
double get_distance(double angle) const;

private:
double res{1};
std::vector<std::vector<double>> buffer;
int oldest_scan{0};
int newest_scan{-1};
void increment(int index);
};

std::ostream &operator<<(std::ostream &out, const std::vector<double> &last_scan);

#endif // LIDARDRIVER_H