/* main.cpp */

#include <iostream>
#include <string>
#include <vector>

#include "sailboat.h"

using namespace std;

int main() 
{
  // create array of boats
  vector<Sailboat> boats;
  boats.push_back(Sailboat("Titan", 15, 20));
  boats.push_back(Sailboat("Saturn", 20, 25));
  boats.push_back(Sailboat("GoldLine", 8, 30));

  // print boats with their max speeds
  for (Sailboat b : boats)
    cout << b.Name << ": " << b.MaxSpeedKts() << " knots" << endl;
}
