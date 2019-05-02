#include <iostream>

using namespace std;

class CanGoWrong {
public:
    CanGoWrong() {
        char *str = new char[999999999999999999];
        delete [] str;
    }
};

int main()
{
    try {
        CanGoWrong can_go_wrong;
    } catch (bad_alloc& e) {
        cout << "Catch exception: " << e.what() << endl;
    }

    cout << "still running" << endl;
    return 0;
}
