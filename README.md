Many programs in this repo are modified from (or even exactly the same as) those appearing in [CS 211: Fundamentals of Computer Programming II](https://www.mccormick.northwestern.edu/computer-science/academics/courses/descriptions/211.html). Some notes are from [Learn C++](https://www.learncpp.com/) and MIT OCW's [6.096 Introduction To C++](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/).

# Notes on C++

- One reason to **separate the definition of a class into `.h` and `.cpp` files** may be to avoid sharing `.cpp` code. According to [slides from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec03/), "[l]ibraries are generally distributed as the header file containing the prototypes, and a binary `.dll`/`.so` file containing the (compiled) implementation".  
- According to [Learn C++]([url](https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/)https://www.learncpp.com/cpp-tutorial/introduction-to-the-copy-constructor/), C++ defines an ***implicit* copy constructor** which creates a deep copy. For example, if a `Fraction` is initialized as `Fraction f { 5, 3 };` then `Fraction fCopy { f };` creates a deep copy.
- The reason an **argument must be passed by reference into a copy constructor** is [that](https://stackoverflow.com/a/2685871) "if it's not by reference, it's by value. To do that you make a copy, and to do that you call the copy constructor. But to do that, we need to make a new value, so we call the copy constructor, and so on…"
- From this [StackOverflow answer](https://stackoverflow.com/a/117557): even when an argument is passed by value, a **`const` keyword helps *self-document* your assumptions**. This makes your code more readable to your coworkers (and to a future you). Sometimes, `const` might even "help the compiler optimize things a bit (though it's a long shot)".
- A **class' members are private by default**. In other words, these two class definitions are equivalent:
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
- **`struct`s** are a carry-over from the C language and are not generally used; classes are preferred. `struct`s are essentially the same as classes, except that their **default access modifier is public**.
- From the [notes from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec07/): the `private` access modifier prevents even derived classes from accessing data members and member functions. "To allow derived classes but not outside code to access data members and member functions, we must declare them as **`protected`**."
- According [notes from this MIT lecture](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/resources/mit6_096iap11_lec07/), C++ allows **multiple inheritance** unlike many other programming languages (ie, a class can have many base classes and inherit all members of all bases classes). However, multiple inheritance can get tricky:
  - However, if multiple base classes have a member `x`, we must disambiguate the member being referred to, eg `Vehicle::x` versus `InsuredItem::x`.
  - If multiple base classes of class `C` inherit from the same base class `BaseC`, you'd end up with multiple instances of `BaseC` within each `C`. This is called a "dreaded diamond" class hierarchy and can get messy to resolve.
  - "In general, avoid multiple inheritance unless you know exactly what you’re doing."
- `cin` only reads up the first whitespace. Thus, if the user enters `Mudd Library`, only `Mudd` gets read. To read multiple words, use the **`getline` function** instead. It reads everything until the user presses enter.
- This [Learn C++ article](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/) explains a **use case for dynamic memory allocation** I had never considered: “The amount of stack memory for a program is generally quite small -- Visual Studio defaults the stack size to 1MB. If you exceed this number, stack overflow will result, and the operating system will probably close down the program. … Being limited to just 1MB of memory would be problematic for many programs, especially those that deal with graphics.”
Of course, other reasons apply too:
  - “it leads to wasted memory if the variables aren’t actually used”,
  - there is no easy way to “tell which bits of memory are actually used”, and
  - static allocation “can lead to artificial limitations and/or array overflows. What happens when the user tries to read in 600 records from disk, but we’ve only allocated memory for a maximum of 500 records? Either we have to give the user an error, only read the 500 records, or (in the worst case where we don’t handle this case at all) overflow the record array and watch something bad happen.”
- According to [this article](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/), "**accessing heap-allocated objects is generally slower than accessing stack-allocated objects**. Because the compiler knows the address of stack-allocated objects, it can go directly to that address to get a value. Heap allocated objects are typically accessed via pointer. This requires two steps: one to get the address of the object (from the pointer), and another to get the value." For this reason, Prof Hummel mentions in CS 211 that C++ developers avoid creating pointers if they can.  
- As [this article](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/) explains, "when you delete a pointer, if that pointer is not going out of scope immediately afterward, set the pointer to `nullptr`". Otherwise, it become a **"dangling pointer"**: it is pointing at the same memory address in the heap as before, except that the address has been returned to the operating system. Trying to access the memory location can cause unpredictable behavior: "the value … that was previously assigned to the allocated memory will probably still be there, but it’s possible that the value at that memory address could have changed. It’s also possible the memory could be allocated to another application (or for the operating system’s own usage), and trying to access that memory will cause the operating system to shut the program down."
- **Deleting a null pointer** has no effect. So, you can just write `delete ptr;` [instead of](https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/):
```
if (ptr) // if ptr is not a null pointer
    delete ptr; // delete it
// otherwise do nothing
```
- According to [this GeeksforGeeks article](https://www.geeksforgeeks.org/delete-in-c/), you `delete` a non-array pointer but must `delete[]` an array. The square brackets indicate that each cell of the array must be destroyed individually.
```
#include <iostream>

using namespace std;

int main() {
  int* ptr1 = new int;
  int* ptr2 = new int(10);
  int a = 0; // trying to cout without initializing will throw error
  int arr_len = 10;
  int* arr = new int[arr_len];

  cout << "ptr1 = " << *ptr1 << endl; // random value because uninitialized
  cout << "ptr2 = " << *ptr2 << endl; // 10
  cout << "a = " << a << endl;        // 0

  for (int i = 0; i < arr_len; i++) {
    cout << "arr[" << i << "] = " << arr[i] << endl; // random values
  }

  delete ptr1;
  delete ptr2;
  delete[] arr;
  // no need to delete a because it is statically allocated
}
```
- According to Prof Hummel in CS 211 Lecture 11 (Northwestern-only on Panopto), the destructor is called as soon as an object is out of scope, even if an `if` block `return`s out of scope before the closing braces. Also, though you can write the destructor, you cannot call it yourself anywhere you like; only the _system_ calls it, and only when the the resource goes out of scope. This is [**deterministic resource management**](https://learn.microsoft.com/en-us/cpp/cpp/object-lifetime-and-resource-management-modern-cpp?view=msvc-170) and makes memory leaks much less common in C++ than in C. In the latter, you have to remember to free the object before `return`ing out of scope. (Though memory leaks are still _possible_ in C++ if you write the destructor incorrectly.)
- This [Learn C++ discussion](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/) of **`std::endl` versus `\n`** concludes that because `std::endl` outputs a newline *and* flushes the buffer, it is generally slower than `\n`. So, "\[i\]f we output multiple lines of text ending with `std::endl`, we will get multiple flushes, which is slow and probably unnecessary. When outputting text to the console, we typically don’t need to explicitly flush the buffer ourselves. C++’s output system is designed to self-flush periodically, and it’s both simpler and more efficient to let it flush itself."
- From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/): "When `\n` is not being embedded into an existing line of double-quoted text (e.g. `"hello\n"`), it is **conventionally single quoted (`'\n'`)**." This makes sense because `\n` is a newline *character*. But the authors still recommend using double quoted `"n"` becaue "\[i\]t’s simpler to double-quote all outputted text" and "it helps avoid inadvertent multicharacter literals".
- Replit doesn't let me compile the first program below because `x` is uninitialized, but the second program compiles and prints a garbage uninitialized value because the compiler is tricked into thinking that `x` is used in the function. The compiler will not always save you, so it's **best practice to initialize your variables**.
```
#include <iostream>

int main()
{
    int x;
    std::cout << x << '\n';
    return 0;
}
```
```
#include <iostream>

void doNothing(int&) // using & to trick the compiler into thinking variable x is used
{
}

int main()
{
    int x; // this variable is uninitialized
    doNothing(x); // make the compiler think we're assigning a value to this variable
    // print the garbage uninitialized value
    std::cout << x << '\n';
    return 0;
}
```
- From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/): "If the variable or function name is multi-word, there are two common conventions: words separated by underscores (sometimes called **snake_case**), or intercapped (sometimes called **camelCase**, since the capital letters stick up like the humps on a camel)." Either is fine, but the authors "typically use the intercapped approach because it’s easier to read (it’s easy to mistake an underscore for a space in dense blocks of code)".
