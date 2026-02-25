#include <stdio.h>
#include <cstdint>


class RingBuffer {
private:
    static const int SIZE = 256;
    uint8_t data[256];
    int head;
    int tail;
public:
    RingBuffer(){
        head = 0;
        tail = 0;
    }

    void write(uint8_t byte){
        data[head] = byte;
        head = (head + 1) % SIZE;
        if (head == tail){
            tail = (tail + 1) % SIZE;
        }
    }
    int findPacketStart(){
        int i = tail;
        while(i != head){
            if (data[i] == 0x7E) { 
                return i;
            }
            i = (i + 1) % SIZE;
        }
        return -1;
    }

    int findPacketLength(){
        int i = this->findPacketStart();
        if (i == -1){
            return -1;
        }
        int length = int(data[i + 1]);
        return length;
    }
};