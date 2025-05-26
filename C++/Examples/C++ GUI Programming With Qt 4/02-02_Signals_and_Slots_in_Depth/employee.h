#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QObject>

class Employee : public QObject {
    Q_OBJECT
    int mySalary;
public:
    //QT explicit Employee(QObject *parent = nullptr);
    Employee() { mySalary = 0; }
    int salary() const { return mySalary; }
public slots:
    void setSalary(int newSalary);
signals:
    void salaryChanged(int newSalary);
};
#endif // EMPLOYEE_H
