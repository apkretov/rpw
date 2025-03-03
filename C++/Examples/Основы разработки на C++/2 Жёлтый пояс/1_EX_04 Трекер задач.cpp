#if 0 //@ https://github.com/avtomato/Basics-of-C-plus-plus-development-yellow-belt/tree/master/week-01/04-Programming-Assignment

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include "../../stdafx.h"
using namespace std;

enum class TaskStatus { NEW, IN_PROGRESS, TESTING, DONE }; // Перечислимый тип для статуса задачи // новая // в разработке // на тестировании // завершена
using TasksInfo = map<TaskStatus, int>; // Объявляем тип-синоним для map<TaskStatus, int>, позволяющего хранить количество задач каждого статуса

TaskStatus Next(TaskStatus task_status) { // Выделим в отдельную функцию получение следующего по приоритету типа задачи // Функция налагает требование на входной параметр: он не должен быть равен DONE // При этом task_status явно не сравнивается с DONE, что позволяет // сделать эту функцию максимально эффективной
	return static_cast<TaskStatus>(static_cast<int>(task_status) + 1); //TEST!
}

class TeamTasks {
public:
	const TasksInfo &GetPersonTasksInfo(const string &person) const; // Получить статистику по статусам задач конкретного разработчика
	void AddNewTask(const string &person); // Добавить новую задачу (в статусе NEW) для конкретного разработчика
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count); // Обновить статусы по данному количеству задач конкретного разработчика
private:
	map<string, TasksInfo> person_tasks_;
};

const TasksInfo &TeamTasks::GetPersonTasksInfo(const string &person) const {
	return person_tasks_.at(person);
}

void TeamTasks::AddNewTask(const string &person) {
	++person_tasks_[person][TaskStatus::NEW];
}

void RemoveZeros(TasksInfo &tasks_info) { // Функция для удаления нулей из словаря
	vector<TaskStatus> statuses_to_remove; // Соберём те статусы, которые нужно убрать из словаря
	for (const auto &task_item : tasks_info) {
		if (task_item.second == 0) 
			statuses_to_remove.push_back(task_item.first);
	}
	for (const TaskStatus status : statuses_to_remove) 
		tasks_info.erase(status);
}

tuple<TasksInfo, TasksInfo> TeamTasks::PerformPersonTasks(const string &person, int task_count) {
	TasksInfo updated_tasks, untouched_tasks;
	TasksInfo &tasks = person_tasks_[person]; // Здесь и далее мы будем пользоваться тем фактом, что в std::map оператор [] // в случае отсутствия ключа инициализирует значение по умолчанию, // если это возможно.	// std::map::operator[] -> 	// http://ru.cppreference.com/w/cpp/container/map/operator_at

	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) { // Посчитаем, сколько задач каждого из статусов нужно обновить, // пользуясь тем фактом, что по умолчанию enum class инциализирует значения // от нуля по возрастанию. // enum class -> http://ru.cppreference.com/w/cpp/language/enum
		updated_tasks[Next(status)] = min(task_count, tasks[status]); //TEST! //																			Считаем обновлённые
		task_count -= updated_tasks[Next(status)]; // Считаем, сколько осталось обновить
	}

	for (TaskStatus status = TaskStatus::NEW; status != TaskStatus::DONE; status = Next(status)) { // Обновляем статус текущих задач в соответствии с информацией об обновлённых // и находим количество нетронутых
		untouched_tasks[status] = tasks[status] - updated_tasks[Next(status)];
		tasks[status] += updated_tasks[status] - updated_tasks[Next(status)];
	}
	
	tasks[TaskStatus::DONE] += updated_tasks[TaskStatus::DONE]; // По условию DONE задачи не нужно возвращать в не обновлённых задачах
	RemoveZeros(updated_tasks); // По условию в словарях не должно быть нулей
	RemoveZeros(untouched_tasks);

	return {updated_tasks, untouched_tasks};
}

int main() {
	PRINT_FILE_LINE();
}
#endif //1

/*
Задание по программированию: Трекер задач

Реализуйте класс TeamTasks, позволяющий хранить статистику по статусам задач команды разработчиков:

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
  // Получить статистику по статусам задач конкретного разработчика
  const TasksInfo& GetPersonTasksInfo(const string& person) const;

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
  void AddNewTask(const string& person);

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
	  const string& person, int task_count);
};

Метод PerformPersonTasks должен реализовывать следующий алгоритм:

	Рассмотрим все не выполненные задачи разработчика person.
	Упорядочим их по статусам: сначала все задачи в статусе NEW, затем все задачи в статусе IN_PROGRESS и, наконец, задачи в статусе TESTING.
	Рассмотрим первые task_count задач и переведём каждую из них в следующий статус в соответствии с естественным порядком: NEW → IN_PROGRESS → TESTING → DONE.
	Вернём кортеж из двух элементов: информацию о статусах обновившихся задач (включая те, которые оказались в статусе DONE) и информацию о статусах остальных не выполненных задач.

Гарантируется, что task_count является положительным числом. Если task_count превышает текущее количество невыполненных задач разработчика, достаточно считать, что task_count равен количеству невыполненных задач: дважды обновлять статус какой-либо задачи в этом случае не нужно.

Кроме того, гарантируется, что метод GetPersonTasksInfo не будет вызван для разработчика, не имеющего задач.
Пример работы метода PerformPersonTasks

Предположим, что у конкретного разработчика имеется 10 задач со следующими статусами:

	NEW — 3
	IN_PROGRESS — 2
	TESTING — 4
	DONE — 1

Поступает команда PerformPersonTasks с параметром task_count = 4, что означает обновление статуса для 3 задач c NEW до IN_PROGRESS и для 1 задачи с IN_PROGRESS до TESTING. Таким образом, новые статусы задач будут следующими:

	IN_PROGRESS — 3 обновлённых, 1 старая
	TESTING — 1 обновлённая, 4 старых
	DONE — 1 старая

В этом случае необходимо вернуть кортеж из 2 словарей:

	Обновлённые задачи: IN_PROGRESS — 3, TESTING — 1.
	Не обновлённые задачи, исключая выполненные: IN_PROGRESS — 1, TESTING — 4.

Словари не должны содержать лишних элементов, то есть статусов, которым соответствует ноль задач.
Примечание

Обновление словаря одновременно с итерированием по нему может привести к непредсказуемым последствиям. При возникновении такой необходимости рекомендуется сначала в отдельном временном словаре собрать информацию об обновлениях, а затем применить их к основному словарю.
Пример кода

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
	  ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
	  ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
	  ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
	tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
	  tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
	  tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  return 0;
}

Вывод

Ilia's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Ivan's tasks: 3 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 2 tasks in progress, 0 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 1 new tasks, 0 tasks in progress, 0 tasks are being tested, 0 tasks are done
Updated Ivan's tasks: 0 new tasks, 1 tasks in progress, 1 tasks are being tested, 0 tasks are done
Untouched Ivan's tasks: 0 new tasks, 1 tasks in progress, 0 tasks are being tested, 0 tasks are done

Пояснение

В этой задаче вам надо прислать на проверку файл с реализацией класса TeamTasks. Этот файл не должен содержать определения типов TaskStatus и TasksInfo. В противном случае вы получите ошибку компиляции.

Гарантируется, что типы TaskStatus и TasksInfo объявлены в точности так же, как в коде выше.
*/