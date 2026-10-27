#include <iostream>
#include <string>
#include <vector>
#include <windows.h>


using namespace std;



    string name;
// Объявление структуры
struct Student {
    string name;
    int age;
    int group;
    double average_grade; // Средняя оценка
};

int main() {
    setlocale(LC_ALL, "rus");
     // Установка кодировки 1251 для ввода и вывода
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::setlocale(LC_ALL, "Russian"); // Дополнительная настройка локали C++
    // Создание объекта структуры
    Student s1;

    // Заполнение полей
    s1.name = "Трубина Варвара";
    s1.age = 54;
    s1.group = 2;
    s1.average_grade = 58;

    // Вывод на экран (все поля первого студента)
    cout << "Студент: " << s1.name << endl;
    cout << "Возраст: " << s1.age << endl;
    cout << "Группа: " << s1.group << endl;
    cout << "Ср. балл: " << s1.average_grade << endl;

    // Современная инициализация (C++11 и выше)
    Student s2{"Термишева Ангелина", 45, 4511, 99.99};
    cout << "\nСтудент 2: " << s2.name << ", Группа: " << s2.group << ", Ср.балл: " << s2.average_grade << endl;

    Student s3; // Создаем третьего студента для ввода с клавиатуры
    cout << "\n=== Ввод данных нового студента с экрана ===" << endl;

    cout << "Введите ФИО студента: ";
    getline(cin >> ws, s3.name);

    cout << "Введите возраст: ";
    cin >> s3.age;

    cout << "Введите номер группы: ";
    cin >> s3.group;

    cout << "Введите средний балл: ";
    cin >> s3.average_grade;

    // Вывод введенных пользователем данных (в одну строку)
    cout << "\nДанные введенного студента:" << endl;
    cout << "Студент: " << s3.name << " | Возраст: " << s3.age << " | Группа: " << s3.group << ", Ср. балл: " << s3.average_grade << endl;

    // Создаем вектор и добавляем туда всех трех студентов
    vector<Student> students = {s1, s2, s3};

    // Поиск студента с максимальным средним баллом
    size_t max_index = 0;

    for (size_t i = 1; i < students.size(); ++i) {
        if (students[i].average_grade > students[max_index].average_grade) {
            max_index = i;
        }
    }

    // Вывод итогового результата поиска
    cout << "\n=== Студент с максимальным средним баллом ===" << endl;
    cout << "Студент: " << students[max_index].name << " | Группа: " << students[max_index].group << ", Максимальный ср. балл: " << students[max_index].average_grade << endl;

    return 0;
}
