#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <cstdlib>
#include <math.h>
#include <fstream>
using namespace std;
struct particle{
  double x[3],
  v[3],
  a[3],
  mass,
  w;
  std::string type;
};

int np = 2;
int L = 100;
vector<particle> particles;
double get_random_number(double min, double max)
{
  return min + (random() / ((double)RAND_MAX)*(max-min));
}

double get_distance(int a, int b, const vector<particle> & v);
void gib_data_pls();


// Sets first particle at (0, 0, 0) and the rest at random positions
void create_matter()
{
  for(int n = 0; n < np; n++){
    for (int i = 1; i <= np; i++){
      particle temp;
      particles.push_back(temp);
    }
    if(n == 0){
      particles[n].x[0] = 0;
      particles[n].x[1] = 0;
      particles[n].x[2] = 0;
    }
    else {
      particles[n].x[0] = get_random_number(0, L);
      particles[n].x[1] = get_random_number(0, L);
      particles[n].x[2] = get_random_number(0, L);
    }
    for (int n = 0; n < np; n++){ //whole thing checks to make sure the particles aren't generated too near each other
      for (int a = n + 1; a < np; a++){
        if (get_distance(n, a, particles) > 0.71){
          continue;
        }
        else {
          particles[n].x[0] = get_random_number(0, L);
          particles[n].x[1] = get_random_number(0, L);
          particles[n].x[2] = get_random_number(0, L);
          n--;
        }
      }
    }
  }
  gib_data_pls();
}

//computes distance for each individual coordinate and then finds the total
//distance
double get_distance(int a, int b, const vector<particle> & v)
{
  double r;
  double change_x;
  double change_y;
  double change_z;

  change_x = fabs(&v[a].x[0] - &v[b].x[0]);
  if (change_x > 0.5*L) {
    change_x -= 0.5*L;
  }
  change_y = fabs(&v[a].x[1] - &v[b].x[1]);
  if (change_y > 0.5*L) {
    change_y -= 0.5*L;
  }
  change_z = fabs(&v[a].x[2] - &v[b].x[2]); 
  if (change_z > 0.5*L) {
    change_z -= 0.5*L;
  }

  double change2_x = change_x * change_x;
  double change2_y = change_y * change_y;
  double change2_z = change_z * change_z;

  r = sqrt(change2_x + change2_y + change2_z);
  return r;
}

void gib_data_pls()
{
ofstream data;
data.open("data.xyz");
data << np << "\n\n";

for (int n = 0; n < np; n++){
  data << "Ar " << particles[n].x[0] << " " <<
    particles[n].x[1] << " " << particles[n].x[2] << endl;
}
data.close();
}
