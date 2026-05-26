size_t Channel::run(std::vector<double>& inputs) {
    return adc.read_input(inputs);
}

std::vector<double> Channel::get_values() {
    return adc.values();
}

std::string Channel::to_string() {
    return adc.to_string();
}