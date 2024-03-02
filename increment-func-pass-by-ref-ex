/* main.cpp
The purpose of this program is to illustrate how to pass arguments into functions by reference */

#include <iostream>
#include <string>

using namespace std;

void increment(int& a);

int main() 
{
  int a = 10;
  cout << a << endl;
  increment(a);
  cout << a << endl;
}

//
// increment: increase the value passed in by reference by 1
//
void increment(int& a)
{
  a++;
}
