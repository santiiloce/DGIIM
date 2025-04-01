#include <QCoreApplication>
#include "producer.h"
#include "consumer.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    const int bufferSize = 10;
    const int produceCount = 50;
    const int consumeCount = 50;

    Buffer buffer(bufferSize);
    Producer producer(&buffer, produceCount);
    Consumer consumer(&buffer, consumeCount);

    producer.start();
    consumer.start();

    producer.wait();
    consumer.wait();

    return a.exec();
}
