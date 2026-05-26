#pragma once
#include <string>
#include <chrono>
#include <vector>

template <typename T = short, int N = 1024>
struct ADC {
    int bits;
    std::chrono::milliseconds clock_rate;
    double rangeMin, rangeMax;
    double sensitivity;
    double trigger_level;
    std::vector<T> samples;

public:
    T convert(double voltage) {
        int resolution = 1;
        for(int i = 0; i < bits; i++) {
            resolution = resolution*2;
        } 
        double normalized_voltage = (voltage - rangeMin)/(rangeMax - rangeMin);
        double scaled_value = normalized_voltage*(resolution - 1) - resolution/2;
        T ret_value = static_cast<T>(scaled_value);
        return ret_value;
    }

    size_t read_input(std::vector<double>& inputs) {
        for(auto input : inputs) {
            if(input >= trigger_level) { samples.push_back(convert(input)); }
        }
        return samples.size();
    }

    double value(size_t i) { return (double)samples.at(i - 1)*sensitivity; }

    std::vector<double> values() {
        std::vector<double> ret_values;
        for(size_t i = 0; i < samples.size(); i++) { ret_values.push_back(value(i)); }
        return ret_values;
    }

    std::string to_string() {
        std::vector<double> samples_double = values();
        std::string ret_string = "";
        for(auto sample : samples_double) { ret_string = ret_string + std::to_string(sample) + " "; }
        return ret_string;
    }
};