#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct card
{
    std::vector<int> winning_numbers;
    std::vector<int> entries;
};
static std::vector<int> get_numbers(const std::string& line)
{
    std::vector<int> numbers;

    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ' ') continue;

        std::string number;

        while (line[i] != ' ')
        {
            number.push_back(line[i]);
            i++;
        }

        numbers.push_back(std::stoi(number));
    }

    return numbers;
}

static card process_card(const std::string& line)
{
    size_t pipe = line.find("|");

    std::string winning_nos = line.substr(line.find(":") + 2, pipe - (line.find(":") + 2));
    std::string entry_nos = line.substr(pipe + 2) + ' ';

    card c;

    c.winning_numbers = get_numbers(winning_nos);
    c.entries = get_numbers(entry_nos);

    return c;
}

static int match_numbers(card c)
{
    int matches = 0;
    int score = 1;

    for (const auto& i : c.entries)
    {
        for (const auto& j : c.winning_numbers)
        {
            if (i == j)
            {
                matches++;
                break;
            }
        }
    }

    if (matches == 0) return 0;

    return std::pow(2, matches - 1);
}

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::string line;
    std::vector<card> cards;

    while (std::getline(fs, line))
    {
        cards.push_back(process_card(line));
    }

    int total = 0;

    for (const auto& card : cards)
    {
        total += match_numbers(card);
    }
    
    std::cout << "Answer: " << std::to_string(total);

    return 0;
}