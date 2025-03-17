#include <iostream>
#include <thread>
#include <string>
#include <barrier>

const std::string adn="ACGT";
const int DataSize = 10000;
const int BufferSize = 1000;
char buffer[BufferSize];

std::barrier sync_point(2);  // Barrera con 2 hilos

void producer()
{
    int j = 0;
    for(int i = 0; i < DataSize; i++)
    {
        buffer[i % BufferSize] = adn[j % 4];
        if(i % BufferSize == BufferSize - 1)
        {
            j++;
        }
        sync_point.arrive_and_wait();  // Esperar al consumidor antes de escribir más
    }
}

void consumer()
{
    for(int i = 0; i < DataSize; i++)
    {
        sync_point.arrive_and_wait();  // Esperar a que el productor termine de escribir
        std::cout << buffer[i % BufferSize];
    }
}

int main()
{
    std::thread p(producer), c(consumer);
    p.join();
    c.join();
    return 0;
}
