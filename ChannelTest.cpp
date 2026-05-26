#include "Channel.h"

struct ChannelFixture : public testing::Test {
    ChannelFixture() {}
    ~ChannelFixture() override {}
    void SetUp() override {}
    void TearDown() override {}
};

std::vector<double> inputs {1., 2., 3., 4., 1.5, 1.99, 2.5, 3.5, 4.5, 4.99};
int bits { 16 };
std::chrono::milliseconds clock_rate { 100 };
double rangeMin { -5. }, rangeMax { 2. };
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