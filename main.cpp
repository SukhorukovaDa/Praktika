#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int countChar(const std::string& text, char b) {
    int schet = 0;
    for (char x : text) {
        if (x == b) {
            schet++;
        }
    }
    return schet;
}

// Функция для выбора правильного склонения слова "символ"
std::string getSymbolWord(int count) {
    // Исключения для чисел, оканчивающихся на 11-14
    if (count % 100 >= 11 && count % 100 <= 14) {
        return "символов";
    }

    // Проверка последней цифры
    switch (count % 10) {
        case 1:
            return "символ";
        case 2:
        case 3:
        case 4:
            return "символа";
        default:
            return "символов";
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Ввести свое ФИО: ";
    std::string fio;
    std::getline(std::cin, fio);

    std::cout << "Длина данной строки: " << fio.length() << std::endl;
    size_t p1 = fio.find(' ');
    std::cout << "Первый пробел: " << p1 << std::endl;
    size_t p2 = fio.find(' ', p1 + 1);

    std::string surname = fio.substr(0, p1);
    std::string name = fio.substr(p1 + 1, p2 - p1 - 1);
    std::string patronymic = fio.substr(p2 + 1);

    std::cout << "Фамилия: " << surname << std::endl;
    std::cout << "Имя: " << name << std::endl;
    std::cout << "Отчество: " << patronymic << std::endl;

    std::string shortName = surname + "_" + name[0] + "." + fio[p2 + 1] + ".";
    std::cout << "Результат: " << shortName << std::endl;

    std::cout << "\nВведите символ для подсчета: ";
    char targetChar;
    std::cin >> targetChar;

    int totalLetters = countChar(fio, targetChar);

    // Используем функцию getSymbolWord для вывода правильной формы
    std::cout << "В этой строке " << totalLetters << " " << getSymbolWord(totalLetters) << " '" << targetChar << "'" << std::endl;

    return 0;
}
