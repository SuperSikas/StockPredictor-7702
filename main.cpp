```cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

class DataProcessor {
private:
    std::vector<double> data;
public:
    explicit DataProcessor(const std::string &filename) {
        std::ifstream inputFile(filename);
        if(inputFile.is_open()) {
            double value;
            while(inputFile >> value) {
                data.push_back(value);
            }
            inputFile.close();
        } else {
            std::cerr << "Unable to open file: " << filename << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }

    double calculateMean() const {
        double sum = 0;
        for(const auto &value : data) {
            sum += value;
        }
        return sum / data.size();
    }

    double calculateMedian() const {
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        size_t size = sortedData.size();
        if(size % 2 == 0) {
            return (sortedData[size / 2 - 1] + sortedData[size / 2]) / 2;
        } else {
            return sortedData[size / 2];
        }
    }

    double calculateMode() const {
        std::vector<double> sortedData = data;
        std::sort(sortedData.begin(), sortedData.end());
        double mode = sortedData[0];
        int modeCount = 1;
        int count = 1;
        for(size_t i = 1; i < sortedData.size(); i++) {
            if(sortedData[i-1] == sortedData[i]) {
                count++;
            } else {
                if(count > modeCount) {
                    modeCount = count;
                    mode = sortedData[i-1];
                }
                count = 1;
            }
        }
        return mode;
    }

    void printData() const {
        for(const auto &value : data) {
            std::cout << value << std::endl;
        }
    }
};


int main() {
    DataProcessor dp("data.txt");
    std::cout << "Mean: " << dp.calculateMean() << std::endl;
    std::cout << "Median: " << dp.calculateMedian() << std::endl;
    std::cout << "Mode: " << dp.calculateMode() << std::endl;
    std::cout << "Data: " << std::endl;
    dp.printData();
    return 0;
}
```
Цей код читає дані з файлу "data.txt", обчислює середнє значення, медіану, моду і виводить всі дані.