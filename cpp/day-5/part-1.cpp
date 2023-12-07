#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

struct mapping
{
    long source;
    long dest;
    long range;
    
    long offset() const
    {
        return source - dest;
    }

    std::pair<long, long> src_bounds()
    {
        return { source, source + range - 1 };
    }

    std::pair<long, long> dst_bounds()
    {
        return { dest, dest + range - 1 };
    }
};

std::vector<std::string> parse_on_space(const std::string& line)
{
    std::vector<std::string> return_vec;

    auto slice_front = line.begin();

    for (auto it = line.begin(); it != line.end(); ++it)
    {
        if (it == line.end() || *it == ' ')
        {
            return_vec.push_back(std::string{ slice_front, it });
            slice_front = std::next(it);
        }
    }

    return return_vec;
}

int main(int argc, char** argv)
{
    std::fstream fs("input.txt");
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(fs, line))
    {
        if (!line.empty())
            lines.push_back(line + " ");
    }

    std::vector<mapping> seed2soil{};
    std::vector<mapping> soil2fertiliser{};
    std::vector<mapping> fertiliser2water{};
    std::vector<mapping> water2light{};
    std::vector<mapping> light2temp{};
    std::vector<mapping> temp2humidity{};
    std::vector<mapping> humidity2location{};

    std::tuple<std::vector<mapping>, 
        std::vector<mapping>, 
        std::vector<mapping>, 
        std::vector<mapping>, 
        std::vector<mapping>, 
        std::vector<mapping>, 
        std::vector<mapping>> conversion_maps = std::make_tuple(seed2soil, 
            soil2fertiliser, 
            fertiliser2water, 
            water2light, 
            light2temp, 
            temp2humidity, 
            humidity2location);


    for (const auto& l : lines)
    {
        if (!l.empty() && l.find(":") == std::string::npos)
        {
            parse_on_space(l);
        }
    }

    int total = 0;

    std::cout << "Answer: " << std::to_string(total);

    return 0;
}