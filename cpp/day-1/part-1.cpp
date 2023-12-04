#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char** argv)
{
    std::ifstream fs("input.txt");

    int total = 0;

    std::string line;
    while (std::getline(fs, line))
    {
        std::cout << line << std::endl;

        std::string digit_1;
        std::string digit_2;

        for (auto it = line.begin(); it != line.end(); ++it)
        {
            try
            {
                int digit = std::stoi(std::string{*it});
                digit_1 = *it;
                break;
            }
            catch(const std::exception& e){};
        }

        for (auto it = line.rbegin(); it != line.rend(); ++it)
        {
            try
            {
                int digit = std::stoi(std::string{*it});
                digit_2 = *it;
                break;
            }
            catch(const std::exception& e){};
        }

        int result = std::stoi(std::string{ digit_1 + digit_2 });
        std::cout << result << std::endl;

        total += result;
    }

    std::cout << "Answer: " << total << std::endl;

    return 0;
}