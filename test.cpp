#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <Windows.h>

int main() {

    SetConsoleCP(1251);       // Устанавливаем кодировку Windows-1251 на ввод
    SetConsoleOutputCP(1251); // Устанавливаем кодировку Windows-1251 на вывод

    int length = 0;
    std::cout << "Введите желаемую длину строки: ";
    std::cin >> length;

   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


//    if (length <= 0) {
//        std::cout << "Длина должна быть больше 0!" << std::endl;
//        return 1;
//    }

    std::cout << "Введите текст (программа прочитает только первые " << length << " симв.):\n";


    std::string userInput;
    userInput.resize(length);

    std::cin.read(&userInput[0], length);


    std::reverse(userInput.begin(), userInput.end());


    std::cout << "\nРезультат реверса:\n";
    std::cout << userInput << std::endl;

    return 0;
}
