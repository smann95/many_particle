#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <cstdlib>
struct particle{
  double x[3],
  v[3],
  a[3],
  mass,
  w;
  std::string type;
};

double get_random_number(double min, double max)
{
  return min + (random() / ((double)RAND_MAX)*(max-min));
}

