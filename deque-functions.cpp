/* main.cpp
This program shows how to work with deques */

#include <deque>
#include <iostream>

using namespace std;

int main() {
  // push_back and push_front
  deque<int> dq1; // implicit constructor call
  dq1.push_back(10);
  dq1.push_back(20);
  dq1.push_back(30);
  dq1.push_front(0);

  // foreach
  for (int i : dq1)
    cout << i << " "; // 0 10 20 30
  cout << endl;

  // [] notation
  for (int i = 0, n = dq1.size(); i < n; i++)
    cout << dq1[i] << " "; // 0 10 20 30
  cout << endl;

  // assignment using {}
  deque<int> dq2 = {40, 50, 60}; // implicit constructor call

  // auto
  for (auto x : dq2)
    cout << x << " "; // 40 50 60
  cout << endl;

  return 0;
} // implicit destructor calls
