# Template and Generic Programming

所謂泛型編程 (generic programming)，意味以 "獨立於任何特定目標型別" 的方式撰寫程式。使用這種程式時用戶必須提供欲操作的目標型會目標值。

泛型編程 (GP)，一如物件導向編程 (OOP)，亦倚賴某種形式的多型。OOP 的多型乃是在執行期施行 "以繼承關係相連的 classes"。泛型編程則是讓我們所寫的 classes 和 functions 在編譯期於彼此不相干的目標型別之間展現多型。單一 class 或 function 可用來操控各型物件。C++ 標準庫的容器，疊代器和演算法都是泛型編程的極佳例子。

Template (模板) 是泛型編程的基石。所謂 template 是 "建立 class 或 function 的藍圖或方程式"。

例如 C++ 標準庫定義了一個 class template 表現出 `vector` 意義，這個 template 可被用來產生任意數量的 "某目標型別專屬" 的 `vector` classes，像是 `vector<int>` 或 `vector<string>`。

## Template 參數列

```cpp
template <typename T>
int compare(const T &v1, const T &v2) {
    if (v1 < v2)
        return -1;
    if (v2 < v1)
        return 1;
    return 0;
}
```

Template 參數代表 "可在 class 或 function 定義式中使用的型別或是數值"。例如我們的 `compare` 函式宣告了一個 `T` 的型別參數。`compare` 定義式內可以使用 `T`指稱某個型別。至於 `T` 所代表的實際型別由編譯器根據用戶指定而定。

Template 參數可以是代表型別的所謂 **type 參數**，或是代表常數算式的所謂 **nontype 參數**。

## 使用 Function Template
使用 function template 時，編譯器會推導將尚未確定的 **template 引數**綁定於 template 參數上。一旦判別出 template 引數，編譯器就為我們將 **function template 具現 (instantiate)** 出一份實體。

推導出實際的 templates 引數後，編譯器就將那些引數至於對應的 template 參數位置然後產出該函式的一個版本並編譯之。換句話說編譯器接管了 "為所用的每一個目標型別 (再一次) 撰寫函式" 這樣的乏味工作。

```cpp
int main()
{
    // T 是 int
    // 編譯器具現出 int compare(const int&, const int&)
    cout << compare(1, 0) << endl;

    string str_1("hi");
    string str_2("world");

    // T 是 string
    // 編譯器具現出 int compare(const string&, const string&)
    cout << compare(str_1, str_2) << endl;

    return 0;
}
```

## 使用 Class Template
和呼叫 function template 不同，使用 class template 時我們必須明確指出 template 參數的引數:

```cpp
Queue<int> q1;
Queue<vector<double>> qc;
Queue<string> qs;
```

## Template 參數
就像是函式參數一樣，程式員為 template 參數所選的名稱並無本質上的意義。先前例子中我們將 `compare()` 的 template *type* 參數命名為 `T`，但也可以取其他任何命名:

```cpp
template <typename Glorp>
int compare(const Glorp &v1, const Glorp &v2) {
    if (v1 < v2)
        return -1;
    if (v2 < v1)
        return 1;
    return 0;
}
```

這段程式碼定義的 `compare` template 與先前完全相同。

## Template 參數的作用域 (scope)
Template 參數遵循一般名稱的遮蔽規則。如果它與 global 作用域內的物件，函式，或型別的名稱相同，會遮蔽 global 作用域內的名稱:

```cpp
typedef double T;
template <class T> T clac(const T &a, const T &b) 
{
    // tmp 的型別是 template 參數 T
    // 而非 global 作用域內的那個 typedef
    T tmp = a;
    // ...
    return tmp;
}
```

## Template 宣告式
如同其他 class 或函式，我們可以宣告一個 template，而不定義它。

Template 參數的名稱再同一個 template 的 (多個) 宣告式和定義式之間不需相同。

```cpp
template <class T> T calc(const T&, const T&);
template <class U> U calc(const U&, const U&);

template <class Type> 
Type calc(const Type &a, const Type &b) {
    /*...*/
}
```

## 關鍵字 `typename` 和 `class` 之間區別
關鍵字 `typename` 和 `class` 的意義相同，可互換使用。

`typename` 的意義可能比 `class` 更直覺一些，不過這個關鍵字直到標準 C++ 才加入，舊程式可能只會使用關鍵字 `class`。 