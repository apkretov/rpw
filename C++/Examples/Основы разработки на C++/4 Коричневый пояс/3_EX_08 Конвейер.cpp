#if 0 //@ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/tree/main/week3/08%20Programming%20Assignment

#include <forward_list>
#include <memory>
#include <stdexcept>
#include "../../stdafx.h"
#include "../test_runner.h"
using namespace std;

struct Email {
	string from;
	string to;
	string body;
};

#pragma region GITHUB //MINE: I could not solve this task. @ https://github.com/Hrodvintir/-basics-of-c-plus-plus-development-brown-belt/blob/main/week3/08%20Programming%20Assignment/solution.cpp
class Worker {
	unique_ptr<Worker> next_; //TEST!!
public:
	virtual ~Worker() = default;
	virtual void Process(unique_ptr<Email> email) = 0;
	virtual void Run() { throw logic_error("Unimplemented"); } // только первому worker-у в пайплайне нужно это имплементировать
	void SetNext(unique_ptr<Worker> next) {	next_ = std::move(next); } //TEST!!
protected:
	void PassOn(unique_ptr<Email> email) const { //TEST!! //																							реализации должны вызывать PassOn, чтобы передать объект дальше по цепочке обработчиков
		if (next_)
			next_->Process(std::move(email));
	}
};

class Reader : public Worker {
	istream &in_;
public:
	explicit Reader(istream &in) : in_(in) {}
	void Process(unique_ptr<Email> /* email */) override { /*не делаем ничего*/	} //MINE: Run is a kind of Process for Reader. I would've got rid of Run (from Worker altogether) and used Process instead.

	void Run() override {
		for (;;) {
			auto email = make_unique<Email>();
			getline(in_, email->from);
			getline(in_, email->to);
			getline(in_, email->body);
			if (in_)
				PassOn(std::move(email)); //TEST!!
			else // в реальных программах здесь стоит раздельно проверять badbit и eof
				break;
		}
	}
};

class Filter : public Worker {
public:
	using Function = function<bool(const Email &)>;
	explicit Filter(Function func) : func_(std::move(func)) {}

	void Process(unique_ptr<Email> email) override {
		if (func_(*email))
			PassOn(std::move(email));
	}
private:
	Function func_;
};

class Copier : public Worker {
	string to_;
public:
	explicit Copier(string to) : to_(std::move(to)) {}

	void Process(unique_ptr<Email> email) override {
		if (email->to != to_) {
			auto copy = make_unique<Email>(*email);
			copy->to = to_;
			PassOn(std::move(email));
			PassOn(std::move(copy));
		} else
			PassOn(std::move(email));
	}
};

class Sender : public Worker {
	ostream &out_;
public:
	explicit Sender(ostream &out) : out_(out) {}

	void Process(unique_ptr<Email> email) override {
		out_
			<< email->from << endl
			<< email->to << endl
			<< email->body << endl;
		PassOn(std::move(email));  // never forget
	}
};

class PipelineBuilder { //TEST!!
	vector<unique_ptr<Worker>> workers_; //TEST!
public:
	explicit PipelineBuilder(istream &in) { workers_.push_back(make_unique<Reader>(in)); }

	PipelineBuilder &FilterBy(Filter::Function filter) {
		workers_.push_back(make_unique<Filter>(std::move(filter)));
		return *this;
	}

	PipelineBuilder &CopyTo(string recipient) {
		workers_.push_back(make_unique<Copier>(std::move(recipient)));
		return *this;
	}

	PipelineBuilder &Send(ostream &out) {
		workers_.push_back(make_unique<Sender>(out));
		return *this;
	}

	unique_ptr<Worker> Build() { //TEST!
		for (size_t i = workers_.size() - 1; i > 0; --i)
			workers_[i - 1]->SetNext(std::move(workers_[i])); //TEST!!
#ifdef ORIG
		return std::move(workers_[0]);
#else //MINE
		auto reader = std::move(workers_[0]);
		workers_.clear(); // Clear the moved-from pointers.
		return std::move(reader);
#endif //MINE
	}
};
#pragma endregion //GITHUB

void TestSanity() {
#pragma region string input
	string input = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"ralph@example.com\n"
		"erich@example.com\n"
		"I do not make mistakes of that kind\n"
		);
#pragma endregion //string input

	istringstream inStream(input);
	ostringstream outStream;
	PipelineBuilder builder(inStream);
	builder.FilterBy([](const Email &email) { return email.from == "erich@example.com";	});
	builder.CopyTo("richard@example.com");
	builder.Send(outStream);
	auto pipeline = builder.Build(); //TEST!
	pipeline->Run(); 

#pragma region string expectedOutput
	string expectedOutput = (
		"erich@example.com\n"
		"richard@example.com\n"
		"Hello there\n"

		"erich@example.com\n"
		"ralph@example.com\n"
		"Are you sure you pressed the right button?\n"

		"erich@example.com\n"
		"richard@example.com\n"
		"Are you sure you pressed the right button?\n"
		);
#pragma endregion //string expectedOutput
	ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
	PRINT_FILE_LINE();
	TestRunner tr;
	RUN_TEST(tr, TestSanity);
	return 0;
}
#endif //1

/*
Конвейер
Введение

Многие программы создаются для пакетной обработки большого числа однородных записей. Часто при этом обработка этих записей может быть разделена на логически самостоятельные этапы, это упрощает совместную разработку новых фич и позволяет легко комбинировать эти этапы в новые конфигурации. Такую обработку можно мысленно вообразить себе как поток объектов, идущих по конвейеру от одного обработчика к другому. В этой задаче вам предстоит закончить реализацию такого конвейера.

Основная идея конвейера в том, чтобы использовать функции, "поглощающие" объекты и вызывающие друг друга:

void ConsumeObject(unique_ptr<SomeObject> obj) {
	// обработка
	ConsumeObject2(move(obj));  // теряем владение объектом
}

Возможен вариант архитектуры с shared_ptr, но обычно достаточно unique_ptr, и он в этой ситуации обладает преимуществами:

	уменьшает накладные расходы

	однозначно передает владение: предполагается, что отдав объект, обработчик уже не будет его модифицировать, что упрощает рассуждения о корректности программы

Использование классов вместо функций позволяет отвязать обработчиков друг от друга и упрощает поддержку нескольких классов обрабатываемых объектов.
Постановка задачи

В этой задаче вам предлагается разработать конвейер обработчиков электронных писем:

struct Email {
  string from;
  string to;
  string body;
};

Обработчики должны реализовывать абстрактный класс Worker:

class Worker {
public:
  virtual void Process(unique_ptr<Email> email) = 0;
  virtual void Run() {
	// только первому worker-у в пайплайне нужно реализовать этот метод
	throw logic_error("Unimplemented");
  }

protected:
  // реализации должны вызывать PassOn, чтобы передать объект дальше
  // по цепочке обработчиков
  void PassOn(unique_ptr<Email> email) const;

public:
  void SetNext(unique_ptr<Worker> worker);
};

Также реализуйте обработчики Reader, Filter, Copier и Sender, наследующие от класса Worker, а также класс PipelineBuilder, конструирующий цепочку обработчиков:

class PipelineBuilder {
public:
  // добавляет в качестве первого обработчика Reader
  explicit PipelineBuilder(istream& in);

  // добавляет новый обработчик Filter
  PipelineBuilder& FilterBy(Filter::Function filter);

  // добавляет новый обработчик Copier
  PipelineBuilder& CopyTo(string recipient);

  // добавляет новый обработчик Sender
  PipelineBuilder& Send(ostream& out);

  // строит цепочку с помощью метода Worker::SetNext и возвращает первый обработчик в построенной цепочке
  unique_ptr<Worker> Build();
};

Требования:

Worker

	метод SetNext должен принимать во владение следующий обработчик из цепочки

	метод PassOn должен вызывать метод Process следующего обработчика, если он был установлен

Reader

	конструктор должен принимать входной поток (istream&), из которого нужно читать сообщения

	метод Run должен читать из входного потока все e-mail'ы и передавать дальше каждый из них. Один e-mail представляется во входном потоке полями from, to, body, каждое из которых находится на своей строке.

Filter

	конструктор должен принимать предикат типа function<bool(const Email&)>

	метод Process должен передавать дальше только сообщения, удовлетворяющие предикату Copier

	конструктор должен принимать строку-адрес получателя

	метод Process должен передавать сообщение как исходному получателю, так и указанному в конструкторе. В случае, если они совпадают, дублировать сообщение не нужно

Sender

	конструктор должен принимать поток для записи сообщений

	метод Process должен записывать сообщения в поток в том же формате, в котором они были прочитаны

	Все обработчики должны передавать сообщения дальше, если обратное не требуется явно.

PipelineBuilder

	Конструктор должен инициализировать цепочку обработчиков обработчиком Reader с переданным потоком.

	Методы с типом возврата PipelineBuilder& должны возвращать ссылку на экземпляр класса, для которого они были вызваны, а также добавлять в конец цепочки новый обработчик, соответствующий вызванному методу (Filter для метода FilterBy, Sender для метода Send и т.д.).

	Метод Build должен возвращать готовую цепочку обработчиков; подразумевается, что после его завершения экземпляр PipelineBuilder больше использоваться не будет
*/