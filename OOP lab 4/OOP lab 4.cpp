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
    OSOBA() : name("�������"), age(0) {}
    OSOBA(string name, int age) : name(name), age(age) {}

    virtual void showInfo(ostream& os) const
    {
        os << "��'�: " << name << endl;
        os << "³�: " << age << endl;
    }

    friend istream& operator>>(istream& is, OSOBA& osoba)
    {
        cout << "������ ��'�: ";
        is >> osoba.name;
        cout << "������ ��: ";
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
    SLUZHBOVETS() : OSOBA(), position("�������"), salary(0.0) {}
    SLUZHBOVETS(string name, int age, string position, double salary)
        : OSOBA(name, age), position(position), salary(salary) {}

    void showInfo(ostream& os) const override
    {
        OSOBA::showInfo(os);
        os << "������: " << position << endl;
        os << "��������: " << salary << endl;
    }

    friend istream& operator>>(istream& is, SLUZHBOVETS& sluzhbovets)
    {
        is >> static_cast<OSOBA&>(sluzhbovets);
        cout << "������ ������: ";
        is >> sluzhbovets.position;
        cout << "������ ��������: ";
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

    cout << "�������� ���������� ��� �����:\n";
    cin >> osoba;

    cout << "\n�������� ���������� ��� ���������:\n";
    cin >> sluzhbovets;

    ofstream File("info.txt");
    if (File.is_open())
    {
        File << "���������� ��� �����:\n" << osoba;
        File << "\n���������� ��� ���������:\n" << sluzhbovets;
        File.close();
        cout << "\n���������� ������ �������� � ���� info.txt" << endl;
    }
    else
    {
        cerr << "������� �������� ����� ��� ������!" << endl;
    }

    return 0;
}