Many programs in this repo are modified from (or even exactly the same as) those appearing in [CS 211: Fundamentals of Computer Programming II](https://www.mccormick.northwestern.edu/computer-science/academics/courses/descriptions/211.html).

# Notes on C++

- According to [Learn C++]([url](https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/)https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/), C++ defines an *implicit* copy constructor which creates a deep copy. For example, if a `Fraction` is initialized as `Fraction f { 5, 3 };` then `Fraction fCopy { f };` creates a deep copy.
- The reason an argument must be passed by reference into a copy constructor is [that](https://stackoverflow.com/a/2685871) "if it's not by reference, it's by value. To do that you make a copy, and to do that you call the copy constructor. But to do that, we need to make a new value, so we call the copy constructor, and so on…"
- From this [StackOverflow answer](https://stackoverflow.com/a/117557): even when an argument is passed by value, a `const` keyword might be useful as a way of *self-documenting* your assumptions. This makes your code more readable to your coworkers (and to a future you). Sometimes, `const` might even "help the compiler optimize things a bit (though it's a long shot)".
- In a class, attributes are private by default. In other words, these two class definitions are equivalent:
```
class Point {
  double x, y;
  void print()
  {
    cout << "(" << this->x << ", " << this->y << ")" << endl;  
  }
};
```
```
class Point {
private:
  double x, y;

  void print()
  {
    cout << "(" << this->x << ", " << this->y << ")" << endl;  
  }
};
```
