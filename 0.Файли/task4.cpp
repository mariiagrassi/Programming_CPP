#include <fstream>  // Підключає бібліотеку для роботи з файлами
#include <iostream> // Підключає бібліотеку для вводу/виводу
#include <string>   // Підключає бібліотеку для роботи з рядками (std::string)
#include <sstream>
using namespace std;

struct SportsTeam
{
    string name;
    string sport;
    int playersCount;
    int winsCount;
};

void read_stream()
{                                 // Оголошення функції read_stream
    ifstream myfile("task3.csv"); // Відкриває файл для читання (текстовий режим за замовчуванням)
    if (myfile.is_open())
    {                // Перевіряє, чи файл успішно відкрився
        string line; // Змінна для збереження рядка з файлу
        int counterOfLines = 0;
        while (getline(myfile, line))
        {                      // Читає файл построчно, поки є дані
            if (!line.empty()) // Перевіряємо, щоб рядок не був порожнім
            {
                cout << line << endl; // Виводить кожен рядок у консоль
                counterOfLines++;
            }
        }
        cout << "Lines in this file: " << counterOfLines << endl;

        if (counterOfLines == 0)
        {
            myfile.close();
            return;
        }

        // Для встановлення поточної позиції у файлі на початок, якщо файл було відкрито та прочитано весь або частину, потрібно написати:
        myfile.clear();
        myfile.seekg(0);

        // Створити динамічний масив відповідної довжини для збереження даних з файлу у масив структур
        SportsTeam *teams = new SportsTeam[counterOfLines];
        int i = 0;

        // Прочитати  дані з файлу у динамічний масив, довжина масиву дорівнює кількості записів у файлі
        while (getline(myfile, line) && i < counterOfLines)
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            ss >> teams[i].name >> teams[i].sport >> teams[i].playersCount >> teams[i].winsCount;

            i++;
        }
        myfile.close();

        // Обчислення для завдання 5
        int totalPlayers = 0;
        for (int i = 0; i < counterOfLines; i++)
        {
            totalPlayers += teams[i].playersCount;
        }
        cout << "Total players: " << totalPlayers << endl;

        // Обчислення для завдання 4
        int maxWinsIndex = 0;
        for (int i = 1; i < counterOfLines; i++)
        {
            if (teams[i].winsCount > teams[maxWinsIndex].winsCount)
            {
                maxWinsIndex = i;
            }
        }
        cout << "Team with max wins: " << teams[maxWinsIndex].name << endl;

        // Відсортувати дані по полю у завданні 4
        for (int i = 0; i < counterOfLines - 1; i++)
        {
            for (int j = 0; j < counterOfLines - i - 1; j++)
            {
                if (teams[j].winsCount < teams[j + 1].winsCount)
                {
                    SportsTeam temp = teams[j];
                    teams[j] = teams[j + 1];
                    teams[j + 1] = temp;
                }
            }
        }

        cout << "\nSorted teams by wins:" << endl;
        for (int i = 0; i < counterOfLines; i++)
        {
            cout << teams[i].name << "\t" << teams[i].sport << "\t"
                 << teams[i].playersCount << "\t" << teams[i].winsCount << endl;
        }

        // Зберегти у відсортованому порядку у новий файл.
        ofstream outfile("sorted_teams.txt");
        if (outfile.is_open())
        {
            for (int i = 0; i < counterOfLines; i++)
            {
                outfile << teams[i].name << "\t"
                        << teams[i].sport << "\t"
                        << teams[i].playersCount << "\t"
                        << teams[i].winsCount << endl;
            }

            outfile << "\nВІДПОВІДЬ НА ЗАВДАННЯ 4" << endl;
            outfile << "Команда з найбільшою кількістю перемог: " << teams[maxWinsIndex].name
                    << " (" << teams[maxWinsIndex].winsCount << " перемог)" << endl;

            outfile << "\nВІДПОВІДЬ НА ЗАВДАННЯ 5" << endl;
            outfile << "Загальна кількість гравців у всіх командах: " << totalPlayers << endl;

            outfile.close();
            cout << "\nData and all answers successfully saved to sorted_teams.txt" << endl;
        }
        else
        {
            cout << "Unable to create output file" << endl;
        }

        delete[] teams;
    }
    else
    {                                          // Якщо файл не вдалося відкрити
        cout << "Unable to open file" << endl; // Виводить повідомлення про помилку
    }
}

int main()
{
    setlocale(LC_ALL, "Ukrainian");
    read_stream(); // Точка входу в програму: викликає функцію read_stream
    return 0;
}