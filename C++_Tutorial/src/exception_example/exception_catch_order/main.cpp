#include <iostream>

using namespace std;

void goesWrong() {
    bool error1Detected = true;
    bool error2Detected = false;

    if (error1Detected) {
        throw bad_alloc();
    }

    if (error2Detected) {
        throw exception();
    }

}

int main()
{
    try {
        goesWrong();
    } catch (exception &e) {
        cout << "1." << e.what() << endl;
    } catch (bad_alloc &e) {
        cout << "2." << e.what() << endl;
    }
    return 0;
}
