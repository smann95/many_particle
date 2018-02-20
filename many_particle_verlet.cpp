#include "many_particle_verlet.h"
using namespace std;

int main(int argc, char **argv)
{
  if (argc != 2){
    cout << "Please provide a file of conditions." << endl;
    return 1;
  }

  vector<double> conditions;
  double temp;
  ifstream input (argv[1]);
  while (input >> temp){
    conditions.push_back(temp);
  } 

  np = conditions[0];
  L = conditions[1];
  T = conditions[2];
  steps = conditions[3];

  data.open("data.xyz");

  srandom(time(NULL));
  create_matter();

  for(int t = 0; t < steps; t++){
    move_particle();
  }
  data.close();
  // double old_pe = get_pe();
  return 0;
}
