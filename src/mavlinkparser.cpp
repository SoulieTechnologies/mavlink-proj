#include <stdio.h>
#include <ringbuffer.h>

class MavlinkParser : public RingBuffer{
public:
    bool isHeaderValid(){
        int i = this->findPacketStart();
        if (i == -1){
            return false;
        }
        int length = this->findPacketLength();
        int message_length = 10 + length + 2;
        int data_size = this.data.size();
        return data_size == message_length;
        }
};
