#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

class OSOBA
{
protected:
    string name;
    int age;

public:
    OSOBA() : name("Невідомо"), age(0) {}
    OSOBA(string name, int age) : name(name), age(age) {}

    virtual void showInfo(ostream& os) const
    {
        os << "Ім'я: " << name << endl;
        os << "Вік: " << age << endl;
    }

    friend istream& operator>>(istream& is, OSOBA& osoba)
    {
        cout << "Введіть ім'я: ";
        is >> osoba.name;
        cout << "Введіть вік: ";
        is >> osoba.age;
        return is;
    }

    friend ostream& operator<<(ostream& os, const OSOBA& osoba)
    {
        osoba.showInfo(os);
        return os;
    }
};

class SLUZHBOVETS : public OSOBA
{
private:
    string position;
    double salary;

public:
    SLUZHBOVETS() : OSOBA(), position("Невідомо"), salary(0.0) {}
    SLUZHBOVETS(string name, int age, string position, double salary)
        : OSOBA(name, age), position(position), salary(salary) {}

    void showInfo(ostream& os) const override
    {
        OSOBA::showInfo(os);
        os << "Посада: " << position << endl;
        os << "Зарплата: " << salary << endl;
    }

    friend istream& operator>>(istream& is, SLUZHBOVETS& sluzhbovets)
    {
        is >> static_cast<OSOBA&>(sluzhbovets);
        cout << "Введіть посаду: ";
        is >> sluzhbovets.position;
        cout << "Введіть зарплату: ";
        is >> sluzhbovets.salary;
        return is;
    }

    friend ostream& operator<<(ostream& os, const SLUZHBOVETS& sluzhbovets)
    {
        sluzhbovets.showInfo(os);
        return os;
    }
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    OSOBA osoba;
    SLUZHBOVETS sluzhbovets;

    cout << "Введення інформації про особу:\n";
    cin >> osoba;

    cout << "\nВведення інформації про службовця:\n";
    cin >> sluzhbovets;

    ofstream File("info.txt");
    if (File.is_open())
    {
        File << "Інформація про особу:\n" << osoba;
        File << "\nІнформація про службовця:\n" << sluzhbovets;
        File.close();
        cout << "\nІнформація успішно записана у файл info.txt" << endl;
    }
    else
    {
        cerr << "Помилка відкриття файлу для запису!" << endl;
    }

    return 0;
}