#include <unity.h>
#include <Transmitter.h>
#include <drivers/Driver.h>
#include "simulavr_config.h"

#ifndef NULL
#define NULL 0
#endif

using Pulse433::Transmitter;

class MockTransmitter : public Pulse433::Driver {
public:
    bool isOn = false;
    unsigned int callCount = 0;

    virtual ~MockTransmitter() {}

    void setTransmitterOn(const bool value) {
        this->callCount++;
        this->isOn = value;
    }

    void reset() {
        this->isOn = false;
        this->callCount = 0;
    }

    void runTicks(const bool pattern[], const unsigned int length) {
        this->reset();
        for (unsigned int tick = 0; tick < length; ++tick) {
            this->onTick();
            TEST_ASSERT_EQUAL(pattern[tick], this->isOn);
        }
    }
};

void test_Transmitter_constructor() {
    MockTransmitter mock;

    Transmitter testTransmitter(mock);

    TEST_ASSERT_FALSE(mock.isOn);
    TEST_ASSERT_EQUAL(1, mock.callCount);
}

void test_Transmitter_transmitData_should_transmit_a_byte() {
    MockTransmitter mock;
    Transmitter testTransmitter(mock);

    PULSE433_BYTE_T data[1];
    data[0] = 0b10101010;
    testTransmitter.transmitData(data, 1);

    TEST_ASSERT_TRUE(testTransmitter.isBusy());

    const bool startPattern[] = {1, 1, 1, 1, 1, 1, 1, 1,
                                 0, 0, 0, 0,
                                 1, 1, 1, 1,
                                 0};
    mock.runTicks(startPattern, 17);

    const bool dataPattern[] = {1, 1, 1, 1, 0,
                                1, 0, 0, 0, 0,
                                1, 1, 1, 1, 0,
                                1, 0, 0, 0, 0,
                                1, 1, 1, 1, 0,
                                1, 0, 0, 0, 0,
                                1, 1, 1, 1, 0,
                                1, 0, 0, 0, 0};

    mock.runTicks(dataPattern, 40);

    const bool endPattern[] = {1, 0};
    mock.runTicks(endPattern, 2);

    TEST_ASSERT_FALSE(testTransmitter.isBusy());
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_Transmitter_constructor);
    RUN_TEST(test_Transmitter_transmitData_should_transmit_a_byte);
    return UNITY_END();
}
