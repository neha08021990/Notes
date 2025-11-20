/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <utility>   // for std::move

using namespace std;

// Demonstrate const member functions + mutable
class Dummy {
    mutable int x{20};   // Can be modified even inside const member functions
    int y{50};           // Normal member, cannot be modified in const functions

public:
    // Const function: treats object as read-only, except mutable members
    void foo() const {
        x = 10;          // OK: x is mutable
        // y = 30;       // ❌ Not allowed: y is not mutable
    }

    void show() const {
        cout << "[Dummy] x = " << x << ", y = " << y << endl;
    }
};

int main() {
    cout << "=== Pointer + const variations ===" << endl;

    int value = 10;
    int newValue = 20;

    // 1) Pointer to const data (data is const, pointer can change)
    const int* p = &value;
    cout << "p points to value, *p = " << *p << endl;

    p = &newValue;   // OK: pointer can point somewhere else
    cout << "p now points to newValue, *p = " << *p << endl;
    // *p = 30;      // ❌ Not allowed: data is const through p

    // 2) Const pointer to non-const data (pointer is fixed, data can change)
    int* const ptr = &value;
    cout << "ptr points to value, *ptr = " << *ptr << endl;

    *ptr = 25;       // OK: modify data via pointer
    cout << "after *ptr = 25, value = " << value << endl;
    // ptr = &newValue; // ❌ Not allowed: ptr is const, cannot point elsewhere

    // 3) Const pointer to const data (neither pointer nor data can change)
    const int* const pconst = &newValue;
    cout << "pconst points to newValue, *pconst = " << *pconst << endl;
    // *pconst = 50;    // ❌ Not allowed
    // pconst = &value; // ❌ Not allowed

    cout << "\n=== Const pointer to const value ===" << endl;
    const int cvalue = 100;
    const int* ptrConst = &cvalue;   // pointer to const int
    cout << "cvalue = " << cvalue << ", *ptrConst = " << *ptrConst << endl;
    // *ptrConst = 200; // ❌ Not allowed

    cout << "\n=== Const references (lvalue & temporary binding) ===" << endl;

    string xr = "Reference to string";
    const string& ref = xr;   // binds to lvalue
    cout << "ref (bound to xr) = " << ref << endl;

    // const reference can bind to temporary (rvalue)
    const string& tref = "Temporary Binds"; // lifetime extended to end of scope
    cout << "tref (bound to temporary) = " << tref << endl;

    // Another example: binding to temporary std::string
    const string& life = string("Neha Verma");
    cout << "life (temporary lifetime extended) = " << life << endl;

    // This would be illegal:
    // int& bad = 10; // ❌ cannot bind non-const lvalue reference to rvalue

    cout << "\n=== std::move does NOT remove const ===" << endl;

    const int cx = 50;
    auto&& rr = std::move(cx);   // rr has type: const int&&
    cout << "cx = " << cx << ", rr (const int&&, but lvalue expression) = " << rr << endl;
    // rr = 60;                  // ❌ Not allowed: rr is a reference to const int

    cout << "\n=== Pointer constness vs data constness recap ===" << endl;

    int a = 10;
    int b = 20;

    const int* p1 = &a;  // pointer to const data
    // *p1 = 5;          // ❌ data const
    p1 = &b;             // ✔ pointer can change
    cout << "p1 points to b, *p1 = " << *p1 << endl;

    int* const p2 = &a;  // const pointer to non-const data
    *p2 = 5;             // ✔ data can change
    cout << "after *p2 = 5, a = " << a << endl;
    // p2 = &b;          // ❌ pointer cannot change

    cout << "\n=== Class example: const member function + mutable ===" << endl;

    Dummy dobj;
    dobj.show();
    dobj.foo();   // allowed, modifies mutable x
    dobj.show();

    return 0;
}
