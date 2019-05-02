#include <iostream>

using namespace std;

void mightGoWrong() {
    bool error = true;

    if (error) {
        throw 8;
    }
}

int main()
{
    cout << "Hello World!" << endl;

    mightGoWrong();

    cout << "still running" << endl;
    return 0;
}
