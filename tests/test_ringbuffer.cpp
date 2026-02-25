#include <stdio.h>
#include "ringbuffer.h"
#include "gtest/gtest.h"

TEST(RingBufferTest, StartsEmpty){
    RingBuffer rb;
    EXPECT_EQ(rb.findPacketStart(), -1);
}

TEST(RingBufferTest, findPacketStart){
    RingBuffer rb;
    rb.write(0x01);
    rb.write(0x02);
    rb.write(0x7E);
    rb.write(0xFD);
    EXPECT_EQ(rb.findPacketStart(), 2);
}

TEST(RingBufferTest, HandlesWrapAround){
    RingBuffer rb;
    for (int i = 0; i<254; i++){
        rb.write(0x00);
    }
    rb.write(0x7E);
    rb.write(0xAA);
    rb.write(0xBB);
    EXPECT_EQ(rb.findPacketStart(), 254);
}

TEST(RingBufferTest, findPacketLength){
    RingBuffer rb;
    rb.write(0x00);
    rb.write(0x01);
    rb.write(0x02);
    rb.write(0x7E);
    rb.write(0xAA);
    EXPECT_EQ(rb.findPacketLength(), 170);
}

