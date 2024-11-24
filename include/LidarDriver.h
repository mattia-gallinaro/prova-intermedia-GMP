#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H
#include <iostream>
#include <stdexcept>
class LidarDriver{

public:
static const int BUFFER_DIM{10};
static const int MAX_RANGE{180};

//constructors
LidarDriver(void){};
LidarDriver(double ang_res);

//member functions
void new_scan(std::vector<double> scan);
std::vector<double> get_scan(void);
void clear_buffer(void);
double get_distance(double angle) const;
std::vector<double> get_newest_scan(void) const;
double get_res(void) const;

private:
double res{1};
std::vector<std::vector<double>> buffer;
int oldest_scan{0};
int newest_scan{-1};
void increment(int index);
};

std::ostream &operator<<(std::ostream &out,  const LidarDriver &lid);

#endif // LIDARDRIVER_H