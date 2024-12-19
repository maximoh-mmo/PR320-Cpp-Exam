#include "util.h"

std::mt19937 Util::_rng{ std::random_device{}() };

// Name parts
const std::vector<std::string> Util::_first = { "Blood", "Shadow", "Iron", "Dark", "Fire", "Frost", "Storm", "Venom" };
const std::vector<std::string> Util::_last = { "fang", "blade", "bane", "claw", "mancer", "reaver", "shade", "spawn" };
const std::vector<std::string> Util::_titles = { "the Cruel", "the Merciless", "of Doom", "the Vengeful" };

int Util::Rand(int max) // returns int value between 1 and max
{
    std::uniform_int_distribution<int> dist(1, max);
    return dist(_rng);
}

int Util::Rand(int min, int max) // returns int value between min and max
{
    std::uniform_int_distribution<int> dist(min, max);
    return dist(_rng);
}

std::string Util::RandomEnemyName(bool boss)
{
    // Randomly select prefix and suffix
    auto prefix = _first[Rand(static_cast<int>(_first.size())) - 1];
    auto suffix = _last[Rand(static_cast<int>(_first.size())) - 1];
    if (boss) {
        auto title = _last[Rand(static_cast<int>(_first.size())) - 1];
        return prefix + suffix + " " + title;
    }
    // Combine and return the name
    return prefix + suffix;
}
