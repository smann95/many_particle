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

  srandom(time(NULL));
  create_matter();

 // double old_pe = get_pe();
  return 0;
}
