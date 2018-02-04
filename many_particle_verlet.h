#include <iostream>
#include <cmath>
#include <string>
#include <random>
struct particle{
  double x[3],
  v[3],
  a[3];
  double mass;
  double w;
  std::string type;
};

typedef std::mt19937 rng_type;
std::uniform_int_distribution<rng_type::result_type> udist(0, 7);
rng_type rng;

double get_random_number (){
  rng_type::result_type const seedval = get_seed();
  rng.seed(seedval);

  rng_type::result_type random_number = udist(rng);

  return random_number;
}
