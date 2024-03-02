/* sailboat.h */

#pragma once

#include <cmath>
#include <string>
using namespace std;

class Sailboat
{
// setting attributes private to avoid overwriting in main program
private: 
  string Name;
  double LengthOverall;
  double LengthWaterline;

public:
  //
  // constructor
  //

  Sailboat(string name, double len_overall, double len_wl);

  //
  // accessors
  //

  string getName();
  double getLengthOverall();
  double getLengthWaterline();

  //
  // max speed calculator functions
  //
  
  double MaxSpeedKts();
  double MaxSpeedMPH(); 
};
