/* sailboat.cpp */
#include <iostream>

#include "sailboat.h"
using namespace std;

//
// constructor
//

Sailboat::Sailboat(string name, double len_overall, double len_wl)
{
  this->Name = name;
  this->LengthOverall = len_overall;
  this->LengthWaterline = len_wl;
}

//
// accessors
//
string Sailboat::getName()
{
  return this->Name;
}
double Sailboat::getLengthOverall()
{
  return this->LengthOverall;
}
double Sailboat::getLengthWaterline()
{
  return this->LengthWaterline;
}

//
// max speed calculator functions
//

double Sailboat::MaxSpeedKts()
{
  return 1.34 * sqrt(this->LengthWaterline);
}

double Sailboat::MaxSpeedMPH()
{
  return 1.1 * this->MaxSpeedKts();
}
