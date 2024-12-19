#pragma once

#include <random>

class Util
{
public:
    Util() = delete;
    ~Util() = delete;

    static int Rand(int max);
    static int Rand(int min, int max);
    static std::string RandomEnemyName(bool boss);

private:
    static std::mt19937 _rng;
    static const std::vector<std::string> _first;
    static const std::vector<std::string> _last;
    static const std::vector<std::string> _titles;
};