#include <iostream>
#include <fstream>
#include <vector>
#include <string>

enum colour
{
    red,
    green,
    blue,
};

struct hand
{
    std::pair<colour, int> reds;
    std::pair<colour, int> greens;
    std::pair<colour, int> blues;
};
struct game
{
    int n;
    std::vector<hand> hands;
};

game process_game(std::string line)
{
    std::vector<std::string> hands_s;

    size_t colon = line.find(":");
    int n  = std::stoi(line.substr(colon - 1, colon));
    line = line.substr(colon + 2);

    size_t char_it = 0;

    while (1)
    {
        size_t semicolon = line.find(";");

        if (semicolon == std::string::npos)
        {
            hands_s.push_back(line);
            break;
        }

        std::string hand = line.substr(0, semicolon);
        hands_s.push_back(hand);
        line = line.substr(semicolon + 2);
    }

    game g;
    return g;
};

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(fs, line))
    {
        lines.push_back(line);
    }

    for (auto& l : lines)
    {
        process_game(l);
    }

    return 0;
}