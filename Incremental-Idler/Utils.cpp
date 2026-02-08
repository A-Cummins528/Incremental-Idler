#include "Utils.h"
#include <iomanip> // For setprecision
#include <sstream> // For string streams

std::string Utils::formatNumber(long long value)
{
    // 1. If it's small, just return the number
    if (value < 1000)
        return std::to_string(value);

    // 2. Setup the stream for formatting (1 decimal place)
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1);

    double dValue = static_cast<double>(value);
    char suffix = ' ';

    // 3. Determine the size
    if (value < 1000000)
    {
        dValue /= 1000.0;
        suffix = 'k'; // Thousands
    }
    else if (value < 1000000000)
    {
        dValue /= 1000000.0;
        suffix = 'M'; // Millions
    }
    else
    {
        dValue /= 1000000000.0;
        suffix = 'B'; // Billions
    }

    ss << dValue << suffix;
    return ss.str();
}