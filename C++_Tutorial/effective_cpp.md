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