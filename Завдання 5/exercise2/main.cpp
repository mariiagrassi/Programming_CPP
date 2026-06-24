#include <iostream>
#include "Animal_proposal.h"

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

    std::cout << std::endl;

    // should eat in dog, cat, dog order
    for (int i = 0; i < 3; i++)
    {
        arr[i]->eat();
    }

    std::cout << std::endl;

    // should sleep in dog, cat, dog order
    for (int i = 0; i < 3; i++)
    {
        arr[i]->sleep();
    }

    std::cout << std::endl;

    // shouldn't do anything as they're sleeping
    for (int i = 0; i < 3; i++)
    {
        arr[i]->makeSound();
    }

    // shouldn't eat actually, as they are sleeping
    for (int i = 0; i < 3; i++)
    {
        arr[i]->eat();
    }

    std::cout << std::endl;

    // shouldn't wag tails, they are sleeping, but Cat doesn't have wagTail at all
    for (int i = 0; i < 3; i++)
    {
        if (Dog *dogPtr = dynamic_cast<Dog *>(arr[i]))
        {
            dogPtr->wagTail();
        }
    }

    std::cout << std::endl;

    // тепер тварини можуть прокинутись - цього не було в оригінальному коді
    for (int i = 0; i < 3; i++)
    {
        arr[i]->wakeUp();
    }

    std::cout << std::endl;

    // тепер хвости мають вагатись, бо всі вже прокинулись
    for (int i = 0; i < 3; i++)
    {
        if (Dog *dogPtr = dynamic_cast<Dog *>(arr[i]))
        {
            dogPtr->wagTail();
        }
    }

    return 0;
}