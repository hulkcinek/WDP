#include <iostream>
#include <cmath>

bool is_square(int number) {
    int number_sqrt = static_cast<int>(std::sqrt(number));
    return number_sqrt * number_sqrt == number;
}

bool can_be_factored_to_desired_count(int number, int desired_factor_count) {
    if (desired_factor_count == 1) {
        return !is_square(number);
    }
    int number_sqrt = static_cast<int>(std::sqrt(number));
    for (int divisor = 2; divisor <= number_sqrt; divisor++) {
        if (number % divisor == 0) {
            if (is_square(divisor)) {
                continue;
            }
            int dividend = number / divisor;
            if (can_be_factored_to_desired_count(dividend, desired_factor_count-1)) {
                return true;
            }
        }
    }
    return false;
}

void readInputs() {
    int input_count;
    std::cin >> input_count;
    for (int i = 0; i < input_count; i++) {
        int number;
        std::cin >> number;
        int desired_factor_count;
        std::cin >> desired_factor_count;
        if (can_be_factored_to_desired_count(number, desired_factor_count)) {
            std::cout << "TAK" << std::endl;
        } else {
            std::cout << "NIE" << std::endl;
        }
    }
}

int main() {
    readInputs();
    return 0;
}