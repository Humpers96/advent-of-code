#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct card
{
    int id;
    std::vector<int> winning_numbers;
    std::vector<int> entries;

    int matches() const
    {
        int matches = 0;

        for (const auto& i : entries)
        {
            for (const auto& j : winning_numbers)
            {
                if (i == j)
                {
                    matches++;
                    break;
                }
            }
        }

        return matches;
    }

    bool operator<(const card& other) const
    {
        return id < other.id;
    }
};

static int get_card_id(const std::string& line)
{
    size_t space = line.find(" ");
    size_t colon = line.find(":");

    return std::stoi(line.substr(space + 1, colon - space));
}

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
    c.id = get_card_id(line);
    c.winning_numbers = get_numbers(winning_nos);
    c.entries = get_numbers(entry_nos);

    return c;
}

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::string line;

    std::map<card, int> card_map;

    while (std::getline(fs, line))
    {
        card c = process_card(line);

        card_map[c] = 1;
    }

    for (auto it = card_map.begin(); it != card_map.end(); ++it)
    {
        int matches = it->first.matches();

        if (matches != 0)
        {
            auto end = std::next(it, matches + 1);
            for (auto it_2 = std::next(it); it_2 != end; ++it_2)
            {
                it_2->second += it->second;
            }
        }
    }

    int total = 0;

    for (const auto& card : card_map)
    {
        total += card.second;
    }

    std::cout << "Answer: " << std::to_string(total);

    return 0;
}