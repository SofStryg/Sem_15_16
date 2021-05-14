#include<stdio.h> 
#include<math.h> 
#include <iostream>
#include <ctime>
#include <Windows.h>
#include <thread>
#include <vector>

#define limit_Nmax 204800 //Максимальное количество точек
#define limit_a 16 //Максиальный радиус круга
#define min_a 100 //Начальный радиус

using namespace std;

double circle(double x1, double radius1)
{
    double y = radius1 * radius1 - x1 * x1;
    return y;
}

void task(long long int a, double N) {
    srand(time(0));
    double x, y, Pi;
    double Ncirc = 0; double i = 0; //обнуляторы
    while (i < N)
    {
        x = (rand() % (a * 100) / 100);  //Рандомный Х с 3 знаками после запятой
        y = (rand() % (a * 100) / 100);  //Рандомный Y с 3 знаками после запятой
        if (y * y <= circle(x, (a / 2)))  //Условие принадлежности точки к кругу
        {
            Ncirc++;
        }
        i++;
    }
    Pi = (Ncirc / N) * 4;

    printf("\n%lld,%.0f,%f", a, N, Pi);
    cout << endl;
}

int main()
{
    // Последовательный алгоритм
    double x, y, Pi;
    long long int a = min_a;
    double i = 0;//Счетчик 
    double Ncirc = 0;//Количество точек, попавших в круг 
    double Nmax = a; //Общее количество точек
        Nmax = a;
        while (Nmax <= limit_Nmax) // Перебор значения количества точек
        {
            srand(time(0));
            Ncirc = 0; i = 0; //обнуляторы
            while (i < Nmax)
            {
                x = (rand() % (a * 100) / 100);  //Рандомный Х с 3 знаками после запятой
                y = (rand() % (a * 100) / 100);  //Рандомный Y с 3 знаками после запятой
                if (y * y <= circle(x, (a / 2)))  //Условие принадлежности точки к кругу
                {
                    Ncirc++;
                }
                i++;
            }
            Pi = (Ncirc / Nmax) * 4;
            Nmax *= 2;

            printf("\n%lld,%.0f,%f", a, Nmax, Pi);
            cout << endl;
        }

        // Параллельный алгоритм
        vector<thread> threads(15);
        for (int i = 0; i < 15; i++) {
            threads[i] = thread(task,a ,200 * pow((i + 1),2));
        }
        for (auto& th : threads) {
            th.join();
        }
        return 0;
}

