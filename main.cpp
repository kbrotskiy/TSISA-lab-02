#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

double f_of_x(const double x) {
    return ((-0.5) * std::cos(0.5 * x) - 0.5);
}

double f_of_new_x(const double x) {
    return (f_of_x(x) * sin(5 * x));
}

const std::vector<double> P = {0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99},
        q = {0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08,
             0.085, 0.09, 0.095, 0.1};

const double a = -5.0, b = 2.0;


double random(double min, double max) {
    return (double) (rand()) / RAND_MAX * (max - min) + min;
}

std::vector<std::vector<int>> n_p_of_q(const std::vector<double> &P, const std::vector<double> &q) {
    std::vector<std::vector<int>> table;
    for (size_t i = 0; i < q.size(); i++) {
        std::vector<int> string;
        for (size_t j = 0; j < P.size(); j++) {
            string.push_back(std::ceil(log(1 - P[j]) / log(1 - q[i]) ));
        }
        table.push_back(string);
    }
    return table;
}

void pr_n_p_of_q(const std::vector<std::vector<int>> &table) {
    std::cout << std::string(68, '-') << std::endl;
    std::cout << "|q\\\P   ";
    for (size_t i = 0; i < P.size(); i++) {
        std::cout << "|" << std::setw(5) << std::left << P[i];
    }
    std::cout << '|' << std::endl;
    std::cout << std::string(68, '-') << std::endl;
    for (size_t i = 0; i < table.size(); i++) {
        std::cout << "|";
        std::cout << std::setw(6) << std::left << q[i];
        for (size_t j = 0; j < table[i].size(); j++) {
            std::cout << '|' << std::setw(5) << std::left << table[i][j];
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::string(68, '-') << std::endl;
}

void print_table(const std::vector<std::vector<double>> &table) {
    std::cout << std::string(118, '-') << std::endl;
    std::cout << "|q\\\P   ";
    for (size_t i = 0; i < P.size(); i++) {
        std::cout << "|" << std::setw(10) << std::left << P[i];
    }
    std::cout << '|' << std::endl;
    std::cout << std::string(118, '-') << std::endl;
    for (size_t i = 0; i < table.size(); i++) {
        std::cout << "|";
        std::cout << std::setw(6) << std::left << q[i];
        for (size_t j = 0; j < table[i].size(); j++) {
            std::cout << '|' << std::setw(10) << std::left << table[i][j];
        }
        std::cout << '|' << std::endl;
    }
    std::cout << std::string(118, '-') << std::endl;
}

std::vector<std::vector<double>> rand_search(const std::vector<std::vector<int>> &all_n, const int choice) {
    std::vector<std::vector<double>> table;
    for (size_t i = 0; i < q.size(); i++) {
        std::vector<double> string;
        for (size_t j = 0; j < P.size(); j++) {
            double min = 9223372036854775807.0;
            for (size_t k = 0; k < all_n[i][j]; k++) {
                double elem;
                if (choice == 0) {
                    elem = f_of_x(random(a, b));
                } else if (choice == 1) {
                    elem = f_of_new_x(random(a, b));
                } else {
                    throw std::logic_error("Invalid choice");
                }
                if (elem < min) {
                    min = elem;
                }
            }
            string.push_back(min);
        }
        table.push_back(string);
    }
    return table;
}

int main() {
    pr_n_p_of_q(n_p_of_q(P, q));
    std::cout << std::endl;

    print_table(rand_search(n_p_of_q(P, q), 0));
    std::cout << std::endl;

    print_table(rand_search(n_p_of_q(P, q), 1));
    std::cout << std::endl;

    return 0;
}