#include "reader.h"
#include <QDebug>
#include <QRandomGenerator>
#include <QThread>

void Reader::run() {
    int front, num;
    int sum;
    double media, desv;
    for (int i = 0; i < readCount; ++i) {
        // Lee un elemento y obten un pair con el elemento leido y la posición del front
        std::tie(num, front) = buffer->read(readerId);  // Desestructuramos el pair devuelto por la función

        if (problem == 1)   //Caso consumidor 1: moda
        {
            frequencies.clear();
            for (int j = 0; j < my_vect.size(); j++) {
                my_vect[j] = my_vect[j] - num;
                bool found = false;
                for (int x = 0; x < frequencies.size(); x++) {
                    if (my_vect[j] == frequencies[x].first) {
                        frequencies[x].second = frequencies[x].second + 1;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    frequencies.push_back(std::make_pair(my_vect[j], 1));
                }
            }

            for (int j = 0; j < 3; j++) {
                int max_freq = 0;
                int pos = 0;
                for (int x = 0; x < frequencies.size(); x++) {
                    if (frequencies[x].second > max_freq) {
                        max_freq = frequencies[x].second;
                        pos = x;
                    }
                }
                sec_vect.push_back(frequencies[pos].first);
                frequencies.erase(frequencies.begin() + pos);
            }
        }
        else if(problem == 2) {  //Consumidor 2: desviacion tipica actualizada
            for (int j = 0; j < my_vect.size(); j++) { sum = sum + my_vect[j]; }
            media = sum/my_vect.size();
            sum = 0;
            for (int j = 0; j < my_vect.size(); j++) {
                my_vect[j] = (my_vect[j] + num)/2;
                sum = sum + std::pow(my_vect[j]-media,2);
            }
            desv = std::sqrt(sum/my_vect.size()-1);
        }
        else {  //Caso 3: Sumatoria
            int sum = 0;
            for (int element : my_vect) {
                sum += element;
            }
            int resultado = sum * num;
        }

        qDebug() << i << "Reader(" << QThread::currentThreadId() << ") ID:" << readerId << "Reading from pos:" << front << ", Value:" << num;
        QThread::msleep(266); // Caso 1
        // QThread::msleep((200)); // Caso 2
    }
    qDebug() << "-----Se terminó de leer reader " << readerId << "-----";
}
