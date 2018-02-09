#include "many_particle_verlet.h"
using namespace std;

int main()
{
  srandom(time(NULL));

  int number_of_particles = 2;
  int np = number_of_particles;


  for(int n = 1; n <= np; n++){
    vector<particle> particles(n);
    particle temp;
    particles.push_back(temp);

    particles[n].type = "Ar";
    auto &x = particles[n].x[0];
    auto &y = particles[n].x[1];
    auto &z = particles[n].x[2];

    if(n == 1){
      x = 0;
      y = 0;
      z = 0;
    }
    else {
      x = get_random_number(0, 100);
      y = get_random_number(0, 100);
      z = get_random_number(0, 100);
    }
    double max_time = 3;
    double dt = 1;

    for(double t = 0; t < max_time; t += dt){
      x = x + 1;
      y = y + 1;
      z = z + 1;

      cout << x << " " << y << " " << z << endl;
    }
  }
  return 0;
}
