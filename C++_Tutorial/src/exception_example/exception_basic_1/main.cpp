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

    try {
        mightGoWrong();
    } catch (int e) {
        cout << "Error code:" << e << endl;
    }

    cout << "still running" << endl;
    return 0;
}
