#pragma once

struct Quackable {
	virtual void quack() const { cout << "The duck quacks.\n"; }
};

struct Flyable {
	void fly() const { cout << "The duck flies.\n"; }
};

struct MallardDuck final : Duck, Quackable, Flyable {
	void display() const override { cout << "The duck looks like a mallard.\n"; }
};

struct RedheadDuck final : Duck, Quackable, Flyable {
	void display() const override { cout << "The duck looks like a redhead.\n"; }
};

struct RubberDuck final : Duck, Quackable {
	void quack() const override { cout << "The duck squeaks.\n"; }
	void display() const override { cout << "The duck looks like a rubber duck.\n"; }
};

struct DecoyDuck final : Duck {
	void display() const override { cout << "The duck looks like a decoy duck.\n"; }
};