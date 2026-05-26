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
    T convert(double voltage) { return (short)voltage; }

    size_t read_input(std::vector<double>& inputs) {
        for(auto input : inputs) {
            if(input >= trigger_level) { samples.push_back(convert(input)); }
        }
        return samples.size();
    }

    double value(size_t i) { return (double)samples.at(i)*sensitivity; }

    std::vector<double> values() {
        std::vector<double> ret_values;
        for(type_t i; i < samples.size(); i++) { ret_values.push_back(value(i)); }
        return ret_values;
    }

    std::string to_string() {
        vector<double> samples_dobule = values();
        string ret_string = "";
        for(auto sample : samples_double) { string = string + to_string(sample) + " "; }
        return ret_string
    }
};