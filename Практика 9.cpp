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

// Ôóíêöèÿ äëÿ âûáîðà ïðàâèëüíîãî ñêëîíåíèÿ ñëîâà "ñèìâîë"
std::string getSymbolWord(int count) {
    // Èñêëþ÷åíèÿ äëÿ ÷èñåë, îêàí÷èâàþùèõñÿ íà 11-14
    if (count % 100 >= 11 && count % 100 <= 14) {
        return "ñèìâîëîâ";
    }

    // Ïðîâåðêà ïîñëåäíåé öèôðû
    switch (count % 10) {
        case 1:
            return "ñèìâîë";
        case 2:
        case 3:
        case 4:
            return "ñèìâîëà";
        default:
            return "ñèìâîëîâ";
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Ââåñòè ñâîå ÔÈÎ: ";
    std::string fio;
    std::getline(std::cin, fio);

    std::cout << "Äëèíà äàííîé ñòðîêè: " << fio.length() << std::endl;
    size_t p1 = fio.find(' ');
    std::cout << "Ïåðâûé ïðîáåë: " << p1 << std::endl;
    size_t p2 = fio.find(' ', p1 + 1);

    std::string surname = fio.substr(0, p1);
    std::string name = fio.substr(p1 + 1, p2 - p1 - 1);
    std::string patronymic = fio.substr(p2 + 1);

    std::cout << "Ôàìèëèÿ: " << surname << std::endl;
    std::cout << "Èìÿ: " << name << std::endl;
    std::cout << "Îò÷åñòâî: " << patronymic << std::endl;

    std::string shortName = surname + "_" + name[0] + "." + fio[p2 + 1] + ".";
    std::cout << "Ðåçóëüòàò: " << shortName << std::endl;

    std::cout << "\nÂâåäèòå ñèìâîë äëÿ ïîäñ÷åòà: ";
    char targetChar;
    std::cin >> targetChar;

    int totalLetters = countChar(fio, targetChar);

    // Èñïîëüçóåì ôóíêöèþ getSymbolWord äëÿ âûâîäà ïðàâèëüíîé ôîðìû
    std::cout << "Â ýòîé ñòðîêå " << totalLetters << " " << getSymbolWord(totalLetters) << " '" << targetChar << "'" << std::endl;

    return 0;
}
