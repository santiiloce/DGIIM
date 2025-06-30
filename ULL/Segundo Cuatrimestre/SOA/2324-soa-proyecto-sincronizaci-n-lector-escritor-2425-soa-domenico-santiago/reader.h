#ifndef READER_H
#define READER_H

#include <QThread>
#include <QRandomGenerator>
#include <vector>
#include "buffer.h"

class Reader : public QThread {
    Q_OBJECT

public:
    Reader(Buffer *buf, int count, int id, int prob) : buffer(buf), readCount(count), readerId(id), problem(prob) {
        my_vect.resize(100);
        for (int i = 0; i < my_vect.size(); i++) { my_vect[i] = QRandomGenerator::global()->bounded(100); }
    }

protected:
    void run() override;

private:

    std::vector <int> my_vect;
    std::vector <int> sec_vect;
    std::vector <std::pair <int, int>> frequencies;
    int problem;
    Buffer *buffer;
    int readCount;
    int readerId; // ID único para el lector
};

#endif // READER_H
