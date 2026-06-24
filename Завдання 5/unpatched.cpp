#include <iostream>
#include <string>

class Animal
{
protected:
    std::string name;
    int age;

public:
    Animal(std::string n, int a);
    virtual void makeSound();
    void eat();
    virtual void sleep();
};

// class Mammal : protected Animal - помилка, бо Dog і Cat мають бути Mammal, а Mammal має бути Animal, а protected inheritance = "is NOT a", тобто Dog не є Animal публічно і поліморфізм ламається
class Mammal : public Animal
{
protected:
    // bool getSleeping; - помилка, бо далі в коді використовується 'isSleeping', а це вже різні змінні і код не буде компілюватися
    bool isSleeping;

public:
    Mammal(std::string n, int a);
    void makeSound();
    void eat();
    void sleep();
};

class Dog : public Mammal
{
private:
    bool isTailWagging;

public:
    Dog(std::string n, int a);
    void makeSound();
    void eat();
    void sleep();
    void fetch();
    void wagTail();
};

class Cat : public Mammal
{
private:
    int numberOfLives;

public:
    Cat(std::string n, int a);
    void makeSound();
    void eat();
    void sleep();
};

// class Tail : public Dog - помилка, бо виходить хвіст = собака, а це вже абсурд. Тому тут має бути композиція, а не спадкування
class Tail
{
public:
    Tail(std::string n, int a);
};

Animal::Animal(std::string n, int a)
{
    name = n;
    age = a;
}

void Animal::makeSound()
{
    std::cout << "This is a generic animal sound." << std::endl;
}

void Animal::eat() { std::cout << "The animal is eating." << std::endl; }

void Animal::sleep() { std::cout << "The animal is sleeping." << std::endl; }

// Mammal::Mammal(std::string n, int a) : Animal(n) { isSleeping = false; } - помилка, бо в конструкри Animal 2 параметри (Animal(std::string n, int a);), а тут передано лише один. Тобто не вистачає параметра age
Mammal::Mammal(std::string n, int a) : Animal(n, a) { isSleeping = false; }

void Mammal::makeSound()
{
    std::cout << "This is a generic mammal sound." << std::endl;
}

void Mammal::eat() { std::cout << "The mammal is eating." << std::endl; }

void Mammal::sleep()
{
    std::cout << "The mammal is sleeping." << std::endl;
    isSleeping = true;
}

Dog::Dog(std::string n, int a) : Mammal(n, a) { isTailWagging = false; }

void Dog::makeSound() { std::cout << "Woof!" << std::endl; } // це помилка, бо метод makeSound() не перевіряє, чи тварина спить, а тварини повинні мовчати під час сну і так само щодо eat() і wagTail()

void Dog::eat() { std::cout << "The dog is eating." << std::endl; }

void Dog::sleep()
{
    std::cout << "The dog is sleeping." << std::endl;
    isSleeping = true;
}

void Dog::fetch() { std::cout << "The dog is fetching." << std::endl; }

void Dog::wagTail()
{
    if (isSleeping)
    {
        std::cout << "The dog can't wag its tail because it's sleeping."
                  << std::endl;
    }
    else
    {
        std::cout << "The dog is wagging its tail." << std::endl;
        isTailWagging = true;
    }
}

Cat::Cat(std::string n, int a) : Mammal(n, a) { numberOfLives = 9; }

void Cat::makeSound() { std::cout << "Meow!" << std::endl; } // це помилка, бо метод makeSound() не перевіряє, чи тварина спить, а тварини повинні мовчати під час сну і так само щодо eat() і wagTail()

void Cat::eat() { std::cout << "The cat is eating." << std::endl; }

void Cat::sleep()
{
    std::cout << "The cat is sleeping." << std::endl;
    isSleeping = true;
}

// Tail::Tail(std::string n, int a) : Dog() {} - помилка, бо Dog не має конструктора БЕЗ параметрів. Клас Dog має лише конструктор з параметрами (Dog(std::string n, int a)), тому виклик Dog() це як виклик неіснуючого конструктора і буде помилка компіляції
Tail::Tail(std::string n, int a) {}

// int Cat::eat = eat(); - це помилка, бо eat це метод, а метод не можна присвоювати змінній. Тобто метод не можна оголошувати як змінну

int main()
{
    Dog d("Fido", 3);
    Cat c("Fluffy", 5);
    Dog d1("Barky", 3);

    Mammal *arr[] = {&d, &c, &d1};

    // should woof, meow, woof
    for (int i = 0; i < 3; i++)
    {
        arr[i]->makeSound();
    }

    // should eat in dog, cat, dog order
    for (int i = 0; i < 3; i++)
    {
        arr[i]->eat();
    }

    // should woof, meow, woof
    for (int i = 0; i < 3; i++)
    {
        arr[i]->makeSound();
    }

    // should sleep in dog, cat, dog order
    for (int i = 0; i < 3; i++)
    {
        arr[i]->sleep();
    }

    // shoudn't do anything as they're sleeping
    for (int i = 0; i < 3; i++)
    {
        arr[i]->makeSound();
    }

    // shoudn't eat actually, as they are sleeping
    for (int i = 0; i < 3; i++)
    {
        arr[i]->eat();
    }

    // shouldn't wag tails, they are sleeping, but some of them do not wag tail at all
    // for (int i = 0; i < 3; i++)
    // {
    //     arr[i]->wagTail();
    // }
    // - помилка, бо arr має тип Mammal*, а в Mammal немає методу wagTail() взагалі (він є лише в Dog). Тому викликати arr[i]->wagTail() для масиву Mammal* не можна, код не скомпілюється

    // Tail t("Taily", 2);
    // t.makeSound(); - помилка, бо Tail не має методу makeSound(). Tail зараз не наслідує Animal, тому виклик t.makeSound() некоректний. Тому можна це просто прибрати, бо хвіст не робить звук (або додати метод makeSound() у Tail)
}