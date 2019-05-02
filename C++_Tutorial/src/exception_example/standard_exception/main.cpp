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
    CanGoWrong can_go_wrong;
    return 0;
}
