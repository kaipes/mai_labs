#include <iostream>
#include <vector>
#include <string>

class TPair {
    private:
        unsigned short localKey;
        std::string localValue;
    public:
        TPair(unsigned short key, std::string value) {
            localKey = key;
            localValue = value;
        }
        int GetKey() {
            return localKey;
        }
        std::string GetValue() {
            return localValue;
        }
};

std::vector<int> CountingSort(std::vector<TPair>& input, int max) {
    std::vector<int> entries(max+1,0);
    for (int i = 0; i < input.size(); ++i) {
        ++entries[input[i].GetKey()];
    }
    for (int i = 1; i < entries.size(); ++i) {
        entries[i] += entries[i-1];
    }
    std::vector<int> output(input.size());
    for (int i = input.size() - 1; i >= 0; --i) {
        --entries[input[i].GetKey()];
        output[entries[input[i].GetKey()]] = i; 
    }
    return output;
 }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::vector<TPair> input;
    unsigned short key;
    std::string value;
    int max = 0;
    while(std::cin >> key >> value) {
        input.push_back({key, value});
        if (key > max) { 
            max = key;
        }
    }
    std::vector<int> output(input.size());
    output = CountingSort(input, max);
    for (int i = 0; i < output.size();i++) {
        std::cout << input[output[i]].GetKey() << '\t' << input[output[i]].GetValue() << "\n";
    } 
}