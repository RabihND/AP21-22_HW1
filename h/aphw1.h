#ifndef AP2020HW1_APHW1_H
#define AP2020HW1_APHW1_H
#include <cmath> //pow
#include <fstream>
#include <iomanip> //stod string to double
#include <iostream> //cout
#include <limits.h>
#include <memory> //shared_ptr
#include <sstream> // std::stringstream
#include <string>
#include <vector>

std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string filename);

double predict(std::vector<double> X, std::vector<double> weights);

std::vector<double> train_weight(std::vector<std::shared_ptr<std::vector<double>>> train, double learning_rate, double number_epoch);
double evaluate(std::vector<std::shared_ptr<std::vector<double>>> test, double l_rate, int n_epoch);
void Perceptron(std::vector<std::shared_ptr<std::vector<double>>> train,
    std::vector<std::shared_ptr<std::vector<double>>> test, double learning_rate,
    int number_epochs);

#endif //AP2020HW1_APHW1_H