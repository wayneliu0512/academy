# Effective C++

## 1. View C++ as a federation of languages.

In the beginning, C++ was just C with some object-oriented features tacked on. Even C++'s original name, "C with Classes", reflected this simple heritage.

As the language matured, it grew bolder and more adventurous. Today C++ is a *multiparadigm programming language*, one supporting a combination of procedural, object-oriented, functional, generic, and metaprogramming features. This is power and flexibility make C++ a tool without equal, but can also cause some confusion.

The easiest way is to view C++ not as a single language but as a federation of related languages. To make sense of C++, you have to recognize its primary sub-languages.

- **C**

    Blocks, statements, the preprocessor, build-in data types, arrays, pointers, etc...

- **Object-Oriented C++**

    Classes, encapsulation, inheritance, polymorphism, virtual functions, etc...

- **Template C++**

    This is the generic programming part of C++.

- **The STL**

    The STL is a template library. Its conventions regarding containers, iterators, algorithm, and function objects, etc...

**Things to Remember**

- Rules for effective C++ programming vary, depending on the part of C++ you are using.

## 2. Prefer `const` , `enum` , and `inline` to `#define` .

This item might better be called "prefer the compiler to the preprocessor", because `#define` may be treated as if it's not part of the language. For example:

    #define ASPECT_RATIO 1.653

The symbolic name `ASPECT_RATIO` may never be seen by compiler; This can be confusing if you get an error during compilation involving the use of the constant, because the error message may refer to `1.653`, not `ASPECT_RATIO` .

The solution is to replace the macro with a constant:

    const double kAspectRatio = 1.653;

The second special case concerns class-specific constants. To limit the scope of a constant to a class, you must make it a member, and to ensure there's at most one copy of the constant, you must make it a `static` member:

```cpp
class CostEstimate{
private:
    static const double FudgeFactor; // declaration; goes in header file
    ...
};
    
const double CostEstimate::FudgeFactor = 1.35; //definition; goes in impl. file
```

There is a exception when you need the value of a class constant during compilation of the class, you can use `enum` defined like this:

```cpp
class GamePlayer {
private:
    enum {NumTurns = 5}; // enum class is better.

    int scores[NumTurns];
    ...
};
``` 

Getting back to preprocessor, another common (mis)use of the `#define` directive is using it to implement macros that look like functions but that don't incur the overhead of a function call.

```cpp
#define CALL_WITH_MAX(a, b) f((a) > (b) ? (a) : (b))
```

Look at the weird things that can happen:

```cpp
int a = 5, b = 0;
CALL_WITH_MAX(++a, b);    // a is incremented twice
CALL_WITH_MAX(++a, b+10); // a is incremented once
```

The solution is:

```cpp
template<typename T>   // template <class T>
inline void CallWithMax(const T &a, const T &b)
{
    f(a > b ? a : b);
}
```

**Things to Remember**

- For simple constants, prefer `const` objects or `enum` to `#define`.
- For function-like macros, prefer inline functions to `#define`.

## 3. Use `const` whenever possible.

The wonderful thing about `const` is that it allows you to specify a semantic constraint - a particular object should not be modified - and compilers will enforce that constraint.

這個章節希望大家盡可能的使用 `const`, 所以前半部很多內容是在複習 `const` 的作用, 這部分我就只用 sample code 帶過, 大家也順便複習一下, 看是不是知道這些 `const` 的用法以及差異, 如果有不懂的地方可以提出來.

```cpp
char greeting[] = "Hello";
char *p = greeting;              // non-const pointer,
    							 // non-const data
const char *p = greeting;        // non-const pointer,
								 // const data
char * const p = greeting;       // const pointer,
                                 // non-const data
const char * const p = greeting; // const pointer, 
    							 // const data
```

```cpp
void f1(const Widget *pw); // f1 takes a pointer to a constant Widget object
void f2(Widget const *pw); // so does f2
```

```cpp
std::vector<int> vec;
...
const std::vector<int>::iterator iter = vec.begin(); // iter acts like a T* const
*iter = 10;                                          // OK, changes what iter points to
++iter;                                              // error! iter is const
    
std::vector<int>::const_iterator c_iter = vec.begin(); // c_iter acts like a const T*
*c_iter = 10;                                          // error! *c_iter is const
++c_iter;                                              // fine, changes c_iter
```

### `const` Member Functions

The purpose of `const` on member functions is to identify which member functions may be invoked on `const` objects. Such member functions are important for two reasons. First, they make the interface of a class easier to understand. It's important to know which functions may modify an object and which may not. Seconds, they make it possible to work with `const` objects. That's a critical aspect of writing efficient code, because, as Item 20 explains, one of the fundamental ways to improve a C++ program's performance is to pass objects by reference-to-const.

```cpp
class TextBlock {
public:
    ...
    const char& operator[](const std::size_t position) const // operator[] for
    { return text[position]; }                               // const objects
    char& operator[](const std::size_t position)             // operator[] for
    { return text[position]; }                               // non-const objects
    
private:
    std::string text;
};
```

`TextBlock` 's `operator[]` s can be used like this:

```cpp
TextBlock tb("Hello");
std::cout << tb[0];           // calls non-const TextBlock::operator[]
    
const TextBlock ctb("World");
std::cout << ctb[0];          // calls const TextBlock::operator[]
```

Incidentally, `const` objects most often arise in real programs as a result of being passed by pointer- or reference-to-const.

```cpp
void print(const TextBlock& ctb)  // in this function, ctb is const
{
    std::cout << ctb[0];            // call const TextBlock::operator[]
    ...
}
```

By overloading `operator[]` and giving the different versions different return types, you can have `const` and non- `const` `TextBlock` s handled differently:

```cpp
std::cout << tb[0];  // fine - reading a non-const TextBlock
tb[0] = 'x';         // fine - writing a non-const TextBlock
std::cout << ctb[0]; // fine - reading a const TextBlock
ctb[0] = 'x';        // error! - writing a const TextBlock
```