#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main() {
    const int iterations = 20000000;
    double sum = 0.0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        double x = static_cast<double>(i) / 3.141592653589793;
        double y = std::sin(x) * std::cos(x);
        sum += std::sqrt(std::abs(y)) + std::log1p(std::abs(x) + 1.0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "result=" << std::fixed << std::setprecision(6) << sum << "\n";
    std::cout << "time_us=" << elapsed << "\n";
    return 0;
}
