#include "Animal_proposal.h"

Animal::Animal(std::string n, int a) : name(n), age(a), isSleeping(false) {}
// тут вже передаю обидва параметри в ініціалізатори, бо в оригіналі Mammal викликав Animal(n) і не вистачало age

void Animal::makeSound() const
{
    if (isSleeping)
        return; // тварина мовчить під час сну - в оригіналі цієї перевірки не було взагалі
    std::cout << soundText();
}

void Animal::eat() const
{
    if (isSleeping)
    {
        std::cout << "The animal can't eat because it's sleeping." << std::endl;
        return; // тварина не їсть під час сну - в оригіналі eat() теж нічого не перевіряв
    }
    std::cout << eatText();
}

void Animal::sleep()
{
    if (!isSleeping)
    {
        std::cout << "The animal is sleeping." << std::endl;
        isSleeping = true;
    }
}

void Animal::wakeUp()
{
    if (isSleeping)
    {
        std::cout << name << " wakes up." << std::endl;
        isSleeping = false;
    }
}

std::string Animal::soundText() const
{
    return "This is a generic animal sound.\n";
}

std::string Animal::eatText() const
{
    return "The animal is eating.\n";
}

Mammal::Mammal(std::string n, int a) : Animal(n, a) {}

std::string Mammal::soundText() const
{
    return "This is a generic mammal sound.\n";
}

void Tail::wag() const
{
    std::cout << " tail is wagging." << std::endl;
}

Dog::Dog(std::string n, int a) : Mammal(n, a) {}
// прибрала isTailWagging = false, бо тепер хвостом керує клас Tail, а не прапорець тут

void Dog::fetch() const
{
    if (isSleeping)
        return;
    std::cout << "The dog is fetching." << std::endl;
}

void Dog::wagTail() const
{
    if (isSleeping)
    {
        std::cout << "The dog can't wag its tail because it's sleeping." << std::endl;
    }
    else
    {
        std::cout << "The dog's";
        tail.wag(); // делегую сам рух хвостом класу Tail замість прапорця isTailWagging
    }
}

std::string Dog::soundText() const
{
    return "Woof!\n";
}

std::string Dog::eatText() const
{
    return "The dog is eating.\n";
}

Cat::Cat(std::string n, int a) : Mammal(n, a)
{
    numberOfLives = 9;
}

std::string Cat::soundText() const
{
    return "Meow!\n";
}

std::string Cat::eatText() const
{
    return "The cat is eating.\n";
}

// клас Tail більше не успадковує Dog (як було в оригіналі - class Tail : public Dog),
// тепер це окремий маленький клас, який Dog тримає як свою частину (композиція "has-a", а не "is-a")

// рядок "int Cat::eat = eat();" з оригіналу прибрала повністю - eat це метод, а не змінна, такого синтаксису не існує