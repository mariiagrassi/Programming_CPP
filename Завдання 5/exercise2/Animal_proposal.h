#pragma once
#include <iostream>
#include <string>

class Animal
{
protected:
    std::string name;
    int age;
    bool isSleeping; // підняла цю змінну в Animal, бо і Mammal, і всі нащадки її використовують - це усуває дублювання (DRY)

public:
    Animal(std::string n, int a);
    virtual ~Animal() = default; // додала віртуальний деструктор, бо клас має віртуальні методи і видалення через базовий вказівник має бути безпечним

    void makeSound() const; // зробила невіртуальним і додала перевірку сну тут одного разу, а саму "фразу" звуку віддала в окремий virtual soundText()
    void eat() const;       // те саме: перевірка сну в одному місці, а фраза їжі - в virtual eatText()
    virtual void sleep();
    virtual void wakeUp(); // новий метод, бо в оригіналі тварини засинали назавжди і не мали способу прокинутись

protected:
    virtual std::string soundText() const; // тільки текст звуку, без перевірки сну - це і прибирає дублювання if(isSleeping) у кожному класі
    virtual std::string eatText() const;   // тільки текст їжі
};

class Mammal : public Animal // виправила з protected на public, бо інакше Dog/Cat не є Animal ззовні і поліморфізм через Mammal* ламається
{
public:
    Mammal(std::string n, int a);

protected:
    std::string soundText() const override;
    // eat()/sleep() тут більше нема - вони повністю дублювали Animal, а SRP+DRY каже не повторювати той самий код у дочірньому класі без потреби
};

class Tail // новий клас, бо хвіст - це не тварина, він має належати Dog через композицію, а не успадкування
{
public:
    Tail() = default;
    void wag() const;
};

class Dog : public Mammal
{
private:
    Tail tail; // замінила bool isTailWagging на об'єкт Tail - так логічніше, хвіст це окрема сутність, а не просто прапорець

public:
    Dog(std::string n, int a);
    void fetch() const;
    void wagTail() const;

protected:
    std::string soundText() const override;
    std::string eatText() const override;
};

class Cat : public Mammal
{
private:
    int numberOfLives;

public:
    Cat(std::string n, int a);

protected:
    std::string soundText() const override;
    std::string eatText() const override;
};