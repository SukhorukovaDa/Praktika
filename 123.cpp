#include <iostream>

int main() {
    int time = 6788;

    int* p;

    p=&time;
    //int mins = 0;
    //int secs = 0;

    //convert(time, &mins, &secs);

    std::cout << time << " addrerss " << &time << " pointer  "<<p<<" time value via pointer "<<*p<<std::endl;

    return 0;
}
