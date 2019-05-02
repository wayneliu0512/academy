#include <iostream>

using namespace std;

void mightGoWrong() {
    bool error_1 = false;
    bool error_2 = false;
    bool error_3 = true;

    if (error_1) {
        throw "error string";
    }

    if (error_2) {
        throw 8;
    }

    if (error_3) {
        throw string("error std string");
    }
}

//void usesMightGoWrong() {
//    mightGoWrong();
//}

int main()
{
    cout << "Hello World!" << endl;

    try {
        mightGoWrong();
    } catch (int e) {
        cout << "Error code:" << e << endl;
    } catch (const char *str) {
        cout << str << endl;
    } catch (string& str) {
        cout << str << endl;
    }

    cout << "still running" << endl;
    return 0;
}
