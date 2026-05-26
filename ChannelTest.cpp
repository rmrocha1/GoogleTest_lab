#include <gtest/gtest.h>
#include "Channel.h"

struct ChannelFixture : public ::testing::Test {
    ChannelFixture() {}
    ~ChannelFixture() override {}
    void SetUp() override {}
    void TearDown() override {}
};

std::vector<double> inputs {1., 2., 3., 4., 1.5, 1.99, 2.5, 3.5, 4.5, 4.99};
int bits { 16 };
std::chrono::milliseconds clock_rate { 100 };
double rangeMin { -5. }, rangeMax { 5. };
double sensitivity { 1. }, trigger_level { 2. };
ADC<short, 4> adc { bits, clock_rate, rangeMin, rangeMax, sensitivity, trigger_level };
Channel<short, 4> channel { std::move(adc) };

TEST_F(ChannelFixture, Initialization) {
    EXPECT_EQ(bits, channel.get_adc().bits);
    EXPECT_EQ(rangeMin, channel.get_adc().rangeMin);
    EXPECT_EQ(rangeMax, channel.get_adc().rangeMax);
    EXPECT_EQ(sensitivity, channel.get_adc().sensitivity);
    EXPECT_EQ(trigger_level, channel.get_adc().trigger_level);
}

TEST_F(ChannelFixture, Run) {
    EXPECT_EQ(7,channel.run(inputs));
}

TEST_F(ChannelFixture, AdcConversion) {
    EXPECT_EQ(-32768, channel.get_adc().convert(-5.));
    EXPECT_EQ(-13107, channel.get_adc().convert(-2.));
    EXPECT_EQ(0, channel.get_adc().convert(0.));
    EXPECT_EQ(11795, channel.get_adc().convert(1.8));
    EXPECT_EQ(32767, channel.get_adc().convert(5.));
}

TEST_F(ChannelFixture, ReadInputs) {
    EXPECT_EQ(7, channel.get_adc().read_input(inputs));
}

TEST_F(ChannelFixture, Values) {
    int expected_value;
    size_t i = 1;
    for(auto input : inputs) {
        if(input >= 2.) {
            expected_value = static_cast<int>(6553.5*(input + 5) - 32768);
            EXPECT_EQ(expected_value,channel.get_adc().value(i++));
        }
    }
}