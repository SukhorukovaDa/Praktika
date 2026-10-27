#include <iostream>
#include <string>
#include <vector>
#include <windows.h>


using namespace std;



    string name;
// Îáúÿâëåíèå ñòðóêòóðû
struct Student {
    string name;
    int age;
    int group;
    double average_grade; // Ñðåäíÿÿ îöåíêà
};

int main() {
    setlocale(LC_ALL, "rus");
     // Óñòàíîâêà êîäèðîâêè 1251 äëÿ ââîäà è âûâîäà
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::setlocale(LC_ALL, "Russian"); // Äîïîëíèòåëüíàÿ íàñòðîéêà ëîêàëè C++
    // Ñîçäàíèå îáúåêòà ñòðóêòóðû
    Student s1;

    // Çàïîëíåíèå ïîëåé
    s1.name = "Òðóáèíà Âàðâàðà";
    s1.age = 54;
    s1.group = 2;
    s1.average_grade = 58;

    // Âûâîä íà ýêðàí (âñå ïîëÿ ïåðâîãî ñòóäåíòà)
    cout << "Ñòóäåíò: " << s1.name << endl;
    cout << "Âîçðàñò: " << s1.age << endl;
    cout << "Ãðóïïà: " << s1.group << endl;
    cout << "Ñð. áàëë: " << s1.average_grade << endl;

    // Ñîâðåìåííàÿ èíèöèàëèçàöèÿ (C++11 è âûøå)
    Student s2{"Òåðìèøåâà Àíãåëèíà", 45, 4511, 99.99};
    cout << "\nÑòóäåíò 2: " << s2.name << ", Ãðóïïà: " << s2.group << ", Ñð.áàëë: " << s2.average_grade << endl;

    Student s3; // Ñîçäàåì òðåòüåãî ñòóäåíòà äëÿ ââîäà ñ êëàâèàòóðû
    cout << "\n=== Ââîä äàííûõ íîâîãî ñòóäåíòà ñ ýêðàíà ===" << endl;

    cout << "Ââåäèòå ÔÈÎ ñòóäåíòà: ";
    getline(cin >> ws, s3.name);

    cout << "Ââåäèòå âîçðàñò: ";
    cin >> s3.age;

    cout << "Ââåäèòå íîìåð ãðóïïû: ";
    cin >> s3.group;

    cout << "Ââåäèòå ñðåäíèé áàëë: ";
    cin >> s3.average_grade;

    // Âûâîä ââåäåííûõ ïîëüçîâàòåëåì äàííûõ (â îäíó ñòðîêó)
    cout << "\nÄàííûå ââåäåííîãî ñòóäåíòà:" << endl;
    cout << "Ñòóäåíò: " << s3.name << " | Âîçðàñò: " << s3.age << " | Ãðóïïà: " << s3.group << ", Ñð. áàëë: " << s3.average_grade << endl;

    // Ñîçäàåì âåêòîð è äîáàâëÿåì òóäà âñåõ òðåõ ñòóäåíòîâ
    vector<Student> students = {s1, s2, s3};

    // Ïîèñê ñòóäåíòà ñ ìàêñèìàëüíûì ñðåäíèì áàëëîì
    size_t max_index = 0;

    for (size_t i = 1; i < students.size(); ++i) {
        if (students[i].average_grade > students[max_index].average_grade) {
            max_index = i;
        }
    }

    // Âûâîä èòîãîâîãî ðåçóëüòàòà ïîèñêà
    cout << "\n=== Ñòóäåíò ñ ìàêñèìàëüíûì ñðåäíèì áàëëîì ===" << endl;
    cout << "Ñòóäåíò: " << students[max_index].name << " | Ãðóïïà: " << students[max_index].group << ", Ìàêñèìàëüíûé ñð. áàëë: " << students[max_index].average_grade << endl;

    return 0;
}
