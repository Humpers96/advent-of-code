#include <iostream>
#include <fstream>
#include <string>

const int line_length = 142;
auto c_array = new char[line_length][line_length];

static void scan_surroundings(int i, int j)
{

}

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::string line;

    for (int i = 0; i < line_length; i++)
    {
        c_array[0][i] = 'x';
        c_array[line_length - 1][i] = 'x';
        c_array[i][0] = 'x';
        c_array[i][line_length - 1] = 'x';
    }

    {
        int i = 1;

        while (std::getline(fs, line))
        {
            for (int j = 1; j < line.length() + 1; j++)
            {
                c_array[i][j] = line[j - 1];
            }

            i++;
        }
    }

    for (int i = 0; i < line_length; i++)
    {
        for (int j = 0; j < line_length; j++)
        {
            std::cout << c_array[i][j];
        }
        std::cout << std::endl;
    }

    scan_surroundings(3, 33);

    int total = 0;
    
    std::cout << "Answer: " << std::to_string(total);

    delete[] c_array;

    return 0;
}