#include "aphw1.h"

//Reads a CSV file into a vector of <string, vector<int>> pairs where each pair represents <column name, column values>
std::vector<std::shared_ptr<std::vector<double>>> read_csv(std::string filename)
{
    std::ifstream file { filename }; // Create an input filestream
    std::vector<std::shared_ptr<std::vector<double>>> data; // Create a vector of <string, int vector> pairs to store the result
    //This part to find the horizontal size of the "data"
    char temp_char { ',' };
    double temp_double {};
    size_t counter {};
    while (temp_char == ',') {
        file >> temp_double;
        file >> temp_char;
        counter++;
    }
    file.close();
    file.open(filename);
    char delimiter;
    // define a vector to fill it with the data from the file and push back all the datasets,step by step, to the "data" vector
    std::vector<double> features(counter, 1);
    while (!file.eof()) {
        size_t i {};
        if (i < counter)
            file >> features[i] >> delimiter >> features[i + 1] >> delimiter >> features[i + 2];
        else
            file >> features[counter];
        data.push_back(std::make_shared<std::vector<double>>(features));
    }
    return data;
}

//Make a weighted prediction.
double predict(std::vector<double> X, std::vector<double> weights)
{
    double result {};
    result = weights[0];
    for (size_t i {}; i < X.size(); i++)
        result += weights[i] * X[i - 1];
    if (result >= 0)
        return 1;
    else
        return 0;
}

//To train and identify the best weights, Perceptron uses an iterative process.
std::vector<double> train_weight(std::vector<std::shared_ptr<std::vector<double>>> train, double learning_rate, double number_epoch)
{
    std::vector<double> weights(3, 0);
    for (size_t i = 0; i < number_epoch; i++) {
        for (size_t j = 0; j < train.size(); j++) {
            double prediction = predict(*train[j], weights);
            double error = train[j]->at(2) - prediction;
            weights[0] += learning_rate * error;
            for (size_t k = 0; k < 2; k++)
                weights[k + 1] += learning_rate * error * train[j]->at(k);
        }
    }
    return weights;
}

double evaluate(std::vector<std::shared_ptr<std::vector<double>>> test, double l_rate, int n_epoch)
{
    double correct { 0 };
    std::vector<double> weights = train_weight(test, l_rate, n_epoch);
    // for (int k {}; k < n_folds; k++) {
    for (size_t i {}; i < test.size(); i++) {
        auto prediction = predict(*test[i], weights);
        if (test[i]->at(2) == prediction)
            correct += 1;
    }
    return correct / static_cast<double>(test.size()) * 100;
}
// Declare the perceptron function, which takes the train dataset, test dataset, learning rate, and number of epochs to do all of the preceding operations.
void Perceptron(std::vector<std::shared_ptr<std::vector<double>>> train,
    std::vector<std::shared_ptr<std::vector<double>>> test, double learning_rate,
    int number_epochs)
{
    // std::vector<double> predictions;
    // std::vector<double> weights = train_weight(train, learning_rate, number_epochs);
    // for (size_t i {}; i < test.size(); i++) {
    //     double prediction = predict(*test[i], weights);
    //     predictions.push_back(prediction);
    // }
    //Evaluate
    double scores = evaluate(test, learning_rate, number_epochs);
    std::cout << "Accuracy = " << scores << " %" << std::endl;
}
