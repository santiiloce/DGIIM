#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

const std::string adn="ACGT";
const int DataSize = 10000;
const int BufferSize = 1000;
char buffer[BufferSize];

std::mutex mtx;
std::condition_variable cv;
bool dataReady = false;  // Bandera para indicar que los datos están listos

void producer()
{
    int j = 0;
    for(int i = 0; i < DataSize; i++)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            buffer[i % BufferSize] = adn[j % 4];
            if(i % BufferSize == BufferSize - 1)
            {
                j++;
            }
        }
        dataReady = true;  // Indicar que hay datos disponibles
        cv.notify_one();   // Despertar al consumidor
    }
}

void consumer()
{
    for(int i = 0; i < DataSize; i++)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return dataReady; });  // Espera hasta que el productor escriba
        std::cout << buffer[i % BufferSize];
        dataReady = false;  // Marcar que ya se leyó
    }
}

int main()
{
    std::thread p(producer), c(consumer);
    p.join();
    c.join();
    return 0;
}
