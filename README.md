Many programs in this repo are modified from (or even exactly the same as) those appearing in [CS 211: Fundamentals of Computer Programming II](https://www.mccormick.northwestern.edu/computer-science/academics/courses/descriptions/211.html). Some notes are from MIT OCW's [6.096 Introduction To C++](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/).

# Notes on C++

- One reason to separate the definition of a class into `.h` and `.cpp` files may be to avoid sharing `.cpp` code. According to [slides from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec03/): "[l]ibraries are generally distributed as the header file containing the prototypes, and a binary `.dll`/`.so` file containing the (compiled) implementation".  
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
- `struct`s are a carry-over from the C language and are not generally used; classes are preferred. `struct`s are essentially the same as classes, except that their default access modifier is public.
- From the [notes from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec07/): the `private` access modifier prevents even derived classes from accessing data members and member functions. "To allow derived classes but not outside code to access data members and member functions, we must declare them as `protected`."
- According [notes from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec07/), C++ allows multiple inheritance unlike many other programming languages (ie, a class can have many base classes and inherit all members of all bases classes), a la:
```
class Car : public Vehicle, public InsuredIteam {
  ...
};
```
  - However, if multiple base classes have a member `x`, we must disambiguate the member being referred to, eg `Vehicle::x` versus `InsuredItem::x`.
  - If multiple base classes of class `C` inherit from the same base class `BaseC`, you'd end up with multiple instances of `BaseC` within each `C`. This is called a "dreaded diamond" class hierarchy and can get tricky to resolve.
  - "In general, avoid multiple inheritance unless you know exactly what you’re doing."
