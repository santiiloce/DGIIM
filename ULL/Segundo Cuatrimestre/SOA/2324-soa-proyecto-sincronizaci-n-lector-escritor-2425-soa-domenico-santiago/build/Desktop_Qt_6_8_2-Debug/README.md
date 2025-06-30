# Proyect of Sincronizationn of Reader-Writre with Ring Buffer on Qt

This project is a practical application of concurrent programming concepts using Qt, specifically focused on the implementation and synchronization of a ring buffer to solve the reader-writer problem

## Members:
- Raúl Suárez Jiménez
- Clara Rocio Machado

### 1. Implementation of the code

Clara:

- 1 TODO: Condition of wait, function "read" on buffer.cpp

```C++
    while (itemsAvailable == 0 || activeWriters != 0 || readersWhoReadCurrent.count(readerId) > 0)
```

- 2 TODO: Implement the logic to read the buffer and get position of the front 

```C++
    int num = queue[front];   
    int readPosition = front;      
```

- 3 TODO: Update state to refelex this lector read the element

```C++
    readersWhoReadCurrent.insert(readerId);
    readersReadCurrent += 1;
```

- 4 TODO: Condition of all lectors read the element and update the state of all required variables

```C++
    if (totalReaders == readersReadCurrent) {
        front = (front + 1) % maxSize;
        readersWhoReadCurrent.clear();
        readersReadCurrent = 0;

        --itemsAvailable;
        canWrite.wakeOne(); 
    }
```

- 5 TODO: Complete reader.cpp: 

```C++
    std::tie(num, front) = buffer->read(readerId);
```

Raúl:

- 1 TODO:  Condition of wait, function "write" on buffer.cpp

```C++
    while (activeReaders != 0 || activeWriters != 0 || rear+1 == front)
```

- 2 TODO: Check if the total write limit has been reached and act accordingly. 

```C++
    if (maxWrites == totalWrites) { 
        return -1;  
    }
```

- 3 TODO: Implement the logic to write to the buffer and update the state of the variables.

```C++
    int writePosition = rear;

    itemsAvailable = itemsAvailable+1; 
    totalWrites = totalWrites+1;    
    if (rear == maxSize - 1) { 
        rear = 0;
    } else {
        rear += 1;
    }

    queue[writePosition] = num;
```

- 4 TODO: Complete writer.cpp

```C++
    rear = buffer->write(num);
```

### 2. Distribution of the duties


- Raúl Suárez Jiménez:

    Worked on the branch "raul"

    Did all the requiered TODOs for the "write" function on buffer.cpp.

    Also did the requiered TODO on writer.cpp

- Clara Rocio Machado did all the requiered TODOs for the "read" function on buffer.cpp.

    Worked on the branch "clara"

    Did all the requiered TODOs for the "read" function on buffer.cpp.
    
    Also did the requiered TODO on reader.cpp

- Each TODO has its own commit associated with it.
- When each member finished his part, we push it to git
- Then, 1 member get the other's part with "git pull"
- To merge everything, we did it on the "main" branch and push it to github.