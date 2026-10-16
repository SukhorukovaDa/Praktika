#include <iostream>

void convert(int time, int* minutes, int* seconds) {
    if (minutes != 0) {
        *minutes = time / 60;
    }
    if (seconds != 0) {
        *seconds = time % 60;
    }
}

int main() {
    int time = 2007;
    int mins = 0;
    int secs = 0;

    convert(time, &mins, &secs);

    std::cout << time << " sec " << mins << " min. and " << secs << " sec." << std::endl;

    return 0;
}
