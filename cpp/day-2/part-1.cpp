#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

enum colour
{
    red,
    green,
    blue,
};

struct hand
{
    int reds = 0;
    int greens = 0;
    int blues = 0;
};
struct game
{
    int n;
    std::vector<hand> hands;

    int reds() const
    {
        int max = 0;

        for (const auto& hand : hands)
        {
            max = std::max(hand.reds, max);
        }

        return max;
    }

    int greens() const
    {
        int max = 0;

        for (const auto& hand : hands)
        {
            max = std::max(hand.greens, max);
        }

        return max;
    }

    int blues() const
    {
        int max = 0;

        for (const auto& hand : hands)
        {
            max = std::max(hand.blues, max);
        }

        return max;
    }

    void print()
    {
        std::cout << "Game " << n << ": ";

        for (const auto& hand : hands)
        {
            std::cout << hand.reds << " red, " << hand.greens << " green, " << hand.blues << " blue; ";
        }

        std::cout << std::endl;
    }
};

static hand process_hand(std::string line)
{
    hand h;

    while (1)
    {
        size_t comma = line.find(",");

        std::string cube_set = line.substr(0, comma);

        std::regex red_regex("(\\d+)\\s*red");
        std::regex green_regex("(\\d+)\\s*green");
        std::regex blue_regex("(\\d+)\\s*blue");

        size_t space = line.find(" ");
        std::string n = line.substr(0, space);

        if (std::regex_match(cube_set, red_regex))
        {
            h.reds = std::stoi(n);
        }
        else if (std::regex_match(cube_set, green_regex))
        {
            h.greens = std::stoi(n);
        }
        else if (std::regex_match(cube_set, blue_regex))
        {
            h.blues = std::stoi(n);
        }
        else
        {
            throw;
        }

        if (comma == line.length() - 1) break;

        line = line.substr(comma + 2);
    }

    return h;
}

static game process_game(std::string line)
{
    std::vector<std::string> hands_s;

    size_t i = line.find(" ");
    size_t colon = line.find(":");

    int n = std::stoi(line.substr(i, colon));
    line = line.substr(colon + 2);

    size_t char_it = 0;

    while (1)
    {
        size_t semicolon = line.find(";");

        if (semicolon == std::string::npos)
        {
            hands_s.push_back(line + ",");
            break;
        }

        std::string hand = line.substr(0, semicolon);
        hands_s.push_back(hand + ",");
        line = line.substr(semicolon + 2);
    }

    game g;
    g.n = n;

    for (const auto& hand : hands_s)
    {
        g.hands.push_back(process_hand(hand));
    }

    return g;
};

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::string line;
    std::vector<game> games;

    while (std::getline(fs, line))
    {
        games.push_back(process_game(line));
        games.back().print();
    }

    int total = 0;

    for (const auto& game : games)
    {
        if (game.reds() <= 12 && game.greens() <= 13 && game.blues() <= 14)
        {
            std::cout << "Valid: Game " + std::to_string(game.n) << std::endl;
            total += game.n;
        }
    }

    std::cout << "Answer: " << std::to_string(total);

    return 0;
}