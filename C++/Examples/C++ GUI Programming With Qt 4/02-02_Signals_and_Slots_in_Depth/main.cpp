#include <QCoreApplication>
#include <QDebug>
#include "employee.h"

int main(int argc, char *argv[]) {
    auto employee = new Employee;
    qDebug() << employee->salary();
    employee->setSalary(1000);
    qDebug() << employee->salary();
}
