#include <iostream>
#include <cmath>
#include <string>
#include <random>
#include <cstdlib>
#include <math.h>
#include <fstream>
using namespace std;
struct particle{
  double x[3];
  std::string type;
};

int np;
double L;
double k = 0.00138;
double T;
double steps;
vector<particle> particles;
ofstream data;
//random number between min and max
double get_random_number(double min, double max)
{
  return min + (random() / ((double)RAND_MAX)*(max-min));
}

double get_distance(int a, int b, const vector<particle> & v);
void gib_data_bls();
double get_pe();
void create_matter();
bool evaluate_pe();

//finds potential energy 
double get_pe()
{
  double sigma = 3.345,
         s = sigma,
         s2 = s*s,
         s6 = s2*s2*s2,
         s12 = s6*s6;

  double epsilon = 1.73e-21,
         e = epsilon;
  double pe = 0;
  for (int a = 0; a < np; a++){
    for (int b = a + 1; b < np; b++){
      double r = get_distance(a, b, particles),
             r2 = r*r,
             r6 = r2*r2*r2,
             r12 = r6*r6;
      pe += 4*e*((s12/r12) - (s6/r6));
    }
  }
  return pe;
}

//takes change in potential energy after a move to evaluate if the move
//is good or not
bool evaluate_pe(double old_pe, double new_pe)
{
  bool good;
  double change_pe = new_pe - old_pe;
  double prob = exp(-1*change_pe*(1/(k*T)));
  if (prob > ((double)random()/(double)RAND_MAX)){
    good = true;
  }
  else {
    good = false;
  }
  return good;
}

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
  gib_data_bls();
}

void no_leave_box(int n)
{
  if (particles[n].x[0] > L){
    particles[n].x[0] -= L;
  } 
  if (particles[n].x[1] > L){
    particles[n].x[1] -= L;
  }
  if (particles[n].x[2] > L){
    particles[n].x[2] -= L;
  }
  if (particles[n].x[0] <= 0){
    particles[n].x[0] += L;
  }
  if (particles[n].x[1] <= 0){
    particles[n].x[1] += L;
  }
  if (particles[n].x[2] <= 0){
    particles[n].x[2] += L;
  }
}

//computes distance for each individual coordinate and then finds the total
//distance
double get_distance(int a, int b, const vector<particle> & v)
{
  double d;
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

  d = sqrt(change2_x + change2_y + change2_z);
  return d;
}

void move_particle()
{
  double old_pe = get_pe();

  double dx = get_random_number(0, 0.5*L);
  double dy = get_random_number(0, 0.5*L);
  double dz = get_random_number(0, 0.5*L);

  int n = rand() % particles.size();

  particles[n].x[0] += dx;
  particles[n].x[1] += dy;
  particles[n].x[2] += dz;

  double new_pe = get_pe();

  no_leave_box(n);

  if (!(evaluate_pe(old_pe, new_pe)) == true) {
    particles[n].x[0] -= dx;
    particles[n].x[1] -= dy;
    particles[n].x[2] -= dz;
  }
  gib_data_bls();
}

void gib_data_bls()
{
  data << np << "\n\n";

  for (int n = 0; n < np; n++){
    data << "Ar " << particles[n].x[0] << " " <<
      particles[n].x[1] << " " << particles[n].x[2] << "\n";
  }
}
