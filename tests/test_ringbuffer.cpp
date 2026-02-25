#include <stdio.h>
#include "ringbuffer.h"
#include "waypoint.h"
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

TEST(WayPointTest, printLocation){
    Waypoint wp(40.7128, -74.0060, 0);
    testing::internal::CaptureStdout();
    wp.printLocation();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("latitude: 40.71"), std::string::npos);
    EXPECT_NE(output.find("longitude: -74.01"), std::string::npos);
    EXPECT_NE(output.find("altitude: 0.00"), std::string::npos);
}

TEST(WayPointTest, calculateDistance1){
    Waypoint wp1(40.7128, -74.0060, 0), wp2(34.0522, -118.2437, 20.0);
    double distance = wp1.calculateDistance(wp2);
    EXPECT_NEAR(distance, 49.00, 0.01);
}

TEST(WayPointTest, calculateDistance2){
    Waypoint wp1(0, 0, 0), wp2(0, 0, 0);
    double distance = wp1.calculateDistance(wp2);
    EXPECT_NEAR(distance, 0, 0.01);
}

TEST(WayPointTest, NegativeAltitude){
    try{
    Waypoint wp1(40.7128, -74.0060, -10);
    } catch (const std::invalid_argument& e){
        EXPECT_STREQ(e.what(), "Altitude cannot be negative");
    }
}

