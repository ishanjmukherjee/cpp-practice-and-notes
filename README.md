Many programs in this repo are modified from (or even exactly the same as) those appearing in [CS 211: Fundamentals of Computer Programming II](https://www.mccormick.northwestern.edu/computer-science/academics/courses/descriptions/211.html). Some notes are from [Learn C++](https://www.learncpp.com/) and MIT OCW's [6.096 Introduction To C++](https://ocw.mit.edu/courses/6-096-introduction-to-c-january-iap-2011/). Learn C++ seems great to me (a newbie); it has practical advice on programming in C++, is well-written, and has a quiz at the end of nearly every lesson.

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
    int x;                  // this variable is uninitialized
    doNothing(x);           // make the compiler think we're assigning a value to this variable
    std::cout << x << '\n'; // print the garbage uninitialized value
    return 0;
}
```
- From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/): "If the variable or function name is multi-word, there are two common conventions: words separated by underscores (sometimes called **snake_case**), or intercapped (sometimes called **camelCase**, since the capital letters stick up like the humps on a camel)." Either is fine, but the authors "typically use the intercapped approach because it’s easier to read (it’s easy to mistake an underscore for a space in dense blocks of code)".
- The advice in this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/) seems good: variable names should be descriptive, but overly complex names for trivial variables is bad. "**\[M\]ake the length of an identifier proportional to how widely it is used.**" So, a loop counter used just a couple of times can be `i`, but a function called from many different places in a program should not be `open`, but `openFileOnDisk`.
- More advice from the [Learn C++ article](https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/): **don't use abbreviations while naming identifiers**. If you want to write code faster, use your IDE's auto-complete. "Code is read more often than it is written, the time you saved while writing the code is time that every reader, including the future you, wastes when reading it."
- The number of operands that an operator takes as input is called its **arity**. You'll find the root for "arity" in "unary", "binary", "ternary" and "nullary" operators.
- An operator or function's **side effect** is its observable effect beyond producing a return value. For example, in C++, since assignment changes the value of an object, this is considered a side effect. (Note that contrary to the name, it is the side effect that is key here, and the result value is often incidental.) More in this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/).
- This [Learn C++ article](https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/) explains the **return value of the assignment operator**. The assignment operator `=` returns its left operand so that the operator can be chained. For example, "`x = y = 5` evaluates as `x = (y = 5)`. First `y = 5` assigns `5` to `y`. This operation then returns `y`, which can then be assigned to `x`."
- The [Learn C++ article](https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/) above also explains **the return value of the `<<` operator**. Like the assignment operator, it returns its left operator to allow chaining, i.e., `std::cout << 5` returns `std::cout` for example. "`std::cout << "Hello " << "world!"` evaluates as `(std::cout << "Hello ") << "world!"`. This first prints `"Hello "` to the console. This operation returns `std::cout`, which can then be used to print `"world!"` to the console as well."
- A nice piece of advice from this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/developing-your-first-program/): "You may be thinking, 'C++ has so many rules and concepts. How do I remember all of this stuff?'. Short answer: You don’t. C++ is one part using what you know, and two parts looking up how to do the rest. As you read through this site for the first time, **focus less on memorizing specifics, and more on understanding what’s possible**. Then, when you have a need to implement something in a program you’re writing, you can come back here (or to a reference site) and refresh yourself on how to do so." Knowing what a programming language/library *can* do is powerful (and in many ways enough).
- The advice in this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/forward-declarations/) definitely checks out with my experience: "it is fairly common for a single error to produce many redundant or related errors or warnings. ...  **When addressing compilation errors or warnings in your programs, resolve the first issue listed and then compile again**."
- The function declaration/prototype which lets a compiler know ahead of time about the existence of an identifier before actually defining the identifier is called the **forward declaration**. Here's an [example](https://www.learncpp.com/cpp-tutorial/forward-declarations/) of a forward declaration:
```
int add(int x, int y); // function declaration includes return type, name, parameters, and semicolon.  No function body!
```
- "**[F]unction declarations do not need to specify the names of the parameters** (as they are not considered to be part of the function declaration)." So, the declaration below (from this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/forward-declarations/)) works just fine (but it's still best practice to keep the parameter names in your declarations, to be able to tell what the parameters are by looking at the declaration alone).
```
int add(int, int); // valid function declaration
```
- From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/forward-declarations/): a declaration "tells the compiler about the existence of an identifier and its associated type information" while a definition "is a declaration that actually implements (for functions and types) or instantiates (for variables) the identifier". **All definitions are declarations, but not all declarations are definitions** (for example, the forward declaration above is not a definition). In Bob Nystrom's [words](https://craftinginterpreters.com/the-lox-language.html): "A declaration binds the function’s type to its name so that calls can be type-checked but does not provide a body. A definition declares the function and also fills in the body so that the function can be compiled." Declarations that aren’t definitions are called **pure declarations** (e.g., the forward declaration for a function above).
- `::` is the **scope resolution operator**. From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/): "The identifier to the left of the `::` symbol identifies the namespace that the name to the right of the `::` symbol is contained within. If no identifier to the left of the :: symbol is provided, the global namespace is assumed." But it's best practice to use explicit namespace prefixes.
- It's bad practice to use **`using namespace std`**, since it defeats the whole point of defining namespaces. From this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/naming-collisions-and-an-introduction-to-namespaces/), "any identifier we define may conflict with any identically named identifier in the std namespace. Even worse, while an identifier name may not conflict today, it may conflict with new identifiers added to the std namespace in future language revisions."
- Learn C++ authors [say](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/) that function-like **macros** are unsafe and basically never recommended, but even object-like macros for text substitution should now only be seen in legacy code because constant variables are better. They discuss constant variables in [this article](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/).
- Macros are still useful, though -- not for text substitution, but for **[conditional compilation](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/)** using e.g. `#ifdef`, `#ifndef` and `#endif`.
- You can use **`#if 0`** to exclude a block of code from being compiled. This comes handy in "commenting out" code with multi-line comments (which cannot be nested inside another multi-line comment). (To temporarily re-enable code that has been wrapped in an `#if 0`, you can change the `#if 0` to `#if 1`.) Illustrative program from this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/introduction-to-the-preprocessor/):
```
#include <iostream>

# only "Joe" will be printed
int main()
{
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    /* Some
     * multi-line
     * comment here
     */
    std::cout << "Steve\n";
#endif // until this point

    return 0;
}
```
- According to this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/), the **raison d'etre for header files** is "to put declarations in one location and then import them wherever we need them. This can save a lot of typing in multi-file programs."
- This [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/) recommends that at least for now, **you should not define functions or variables in header files**. "Defining either of these in a header file will likely result in a violation of the one-definition rule (ODR) if that header is then `#include`d into more than one source (.cpp) file." But there are "additional kinds of definitions that can be safely defined in header files (because they are exempt from the ODR). This includes definitions for inline functions, inline variables, types, and templates."
- According to this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/), **source code files should `#include` their paired header file** (if one exists). "This allows the compiler to catch certain kinds of errors at compile time instead of link time. ... Because something.cpp `#include`s something.h, the compiler will notice that function something() has a mismatched return type and give us a compile error. If something.cpp did not `#include` something.h, we’d have to wait until the linker discovered the discrepancy, which wastes time."
- According to this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/), **you shouldn't `#include` .cpp files** because this "can cause naming collisions between source files", but more subtly, "\[a\]ny change to such a .cpp file will cause both the .cpp file and any other .cpp file that includes it to recompile, which can take a long time. Headers tend to change less often than source files."
- According to this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/), it's best practice that **"\[e\]ach file should explicitly #include all of the header files it needs to compile."** It's true that if you `#include` a header file, you also get all the header files included in the first header file (this is called **transitive includes**). But the implementation of header files may change over time. So, you should never rely on implicit `#include`s.
- Sage advice in this [Learn C++ article](https://www.learncpp.com/cpp-tutorial/header-files/) about the **order of inclusion of header files**: "To maximize the chance that missing includes will be flagged by compiler, order your `#include`s as follows: 1) The paired header file, 2) Other headers from your project, 3) 3rd party library headers, 4) Standard library headers. The headers for each grouping should be sorted alphabetically (unless the documentation for a 3rd party library instructs you to do otherwise). That way, if one of your user-defined headers is missing an `#include` for a 3rd party library or standard library header, it’s more likely to cause a compile error so you can fix it." But if header files are written properly (i.e., the `#include` everything they need), the order of inclusion shouldn't matter.
