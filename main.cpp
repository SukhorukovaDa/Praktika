#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <ctime>

using namespace std;

struct Student {
    string str, fio, dob;
    double h, w, bmi;
    int age;
};


string get_age_string(int age) {
    int last_digit = age % 10;
    int last_two_digits = age % 100;

    if (last_two_digits >= 11 && last_two_digits <= 14) {
        return to_string(age) + " лет";
    }
    if (last_digit == 1) {
        return to_string(age) + " год";
    }
    if (last_digit >= 2 && last_digit <= 4) {
        return to_string(age) + " года";
    }
    return to_string(age) + " лет";
}

int calculate_age(string dob_str) {
    int birth_year = stoi(dob_str.substr(0, 4));
    int birth_month = stoi(dob_str.substr(5, 2));
    int birth_day = stoi(dob_str.substr(8, 2));

    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int current_year = now->tm_year + 1900;
    int current_month = now->tm_mon + 1;
    int current_day = now->tm_mday;

    int age = current_year - birth_year;

    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
        age--;
    }
    return age;
}

int main() {
    setlocale(LC_ALL, "Russian");
    ifstream file("students.txt");
    string line;
    vector<Student> students;

    regex pat("^[ \\t]*(.+?)[ \\t]*;[ \\t]*(\\d{4}-\\d{2}-\\d{2})[ \\t]*;[ \\t]*(\\d+)[ \\t]*;[ \\t]*(\\d+)[ \\t]*$");
    regex girl_pat(".+(вна|чна)");

    while (getline(file, line)) {
        smatch m;
        if (regex_match(line, m, pat)) {
            Student s;
            s.str = line;
            s.fio = m[1].str();
            s.dob = m[2].str();
            s.h = stod(m[3].str());
            s.w = stod(m[4].str());
            s.bmi = s.w / ((s.h / 100.0) * (s.h / 100.0));
            s.age = calculate_age(s.dob);
            students.push_back(s);
        }
    }
    file.close();

    if (students.empty()) {
        cout << "Список студентов пуст или файл не найден." << endl;
        return 0;
    }


    Student young_girl = {"", "", "0000-00-00"};
    for (auto &s : students) {
        if (regex_match(s.fio, girl_pat) && s.dob > young_girl.dob) {
            young_girl = s;
        }
    }
    cout << "1. Самая молодая девушка:\n" << young_girl.str
         << " (Возраст: " << get_age_string(young_girl.age) << ")\n\n";

    cout << fixed << setprecision(2);


    cout << "2. ФИО, Возраст, Вес и ИМТ:\n";
    for (auto &s : students) {
        cout << s.fio << " — " << get_age_string(s.age) << ", " << s.w << " кг (ИМТ: " << s.bmi << ")\n";
    }
    cout << "\n";


    Student max_bmi = students[0];
    for (auto &s : students) {
        if (s.bmi > max_bmi.bmi) max_bmi = s;
    }
    cout << "3. Макс. ИМТ:\n" << max_bmi.str
         << " (Возраст: " << get_age_string(max_bmi.age) << ", ИМТ: " << max_bmi.bmi << ")\n\n";


    double total_h = 0, total_w = 0, total_age = 0;
    for (auto &s : students) {
        total_h += s.h;
        total_w += s.w;
        total_age += s.age;
    }
    cout << "4. Средний рост группы: " << total_h / students.size() << " см\n";
    cout << "Средний вес группы: " << total_w / students.size() << " кг\n";
    cout << "Средний возраст группы: " << total_age / students.size() << " лет\n\n";

    return 0;
}


