#include <unity.h>
#include <Transmitter.h>
#include <functional>

class MockTransmitter {
public:
    bool isOn = false;
    unsigned int callCount = 0;

    auto getFuncPointer() {
        return [this](const bool value) {
            this->transmitFunction(value);
        };
    }

    void transmitFunction(const bool value) {
        this->callCount++;
        this->isOn = value;
    }

    void reset() {
        this->isOn = false;
        this->callCount = 0;
    }
};

void test_Transmitter_constructor() {
    MockTransmitter mock;

    Pulse433::Transmitter<std::function<void (const bool)>> testTransmitter(mock.getFuncPointer());

    TEST_ASSERT_FALSE(mock.isOn);
    TEST_ASSERT_EQUAL(1, mock.callCount);
}
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_Transmitter_constructor);
    return UNITY_END();
}
