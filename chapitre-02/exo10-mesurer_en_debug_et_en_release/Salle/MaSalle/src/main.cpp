#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    const int iterations = 5000000;
    double total = 0.0;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        total += std::sqrt(static_cast<double>(i + 1));
        total *= 1.00001;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "total=" << total << "\n";
    std::cout << "time_us=" << elapsed << "\n";
    return 0;
}
