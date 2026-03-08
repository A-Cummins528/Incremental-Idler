#include "Utils.h"
#include <iomanip> // For setprecision
#include <sstream> // For string streams
#include <cmath>

std::string Utils::formatNumber(long long value)
{
    // If it's small, just return the number
    if (value < 1000)
        return std::to_string(value);

    // 2. Setup the stream for formatting (1 decimal place)
   // 
  //  ss << std::fixed << std::setprecision(1);

    double dValue = static_cast<double>(value);
    char suffix = ' ';

    // Determine the size
    if (value < 1000000)
    {
        dValue /= 1000.0;
        suffix = 'k'; 
    }
    else if (value < 1000000000)
    {
        dValue /= 1000000.0;
        suffix = 'M'; 
    }
    else
    {
        dValue /= 1000000000.0;
        suffix = 'B'; 
    }

    std::stringstream ss;

	// Check if the fractional part is zero (e.g., 1.0M should be "1M")
    if (std::fmod(dValue, 1.0) == 0.0)
    {
        ss << std::fixed << std::setprecision(0); // No decimal places
    }
       
    else
    {
        ss << std::fixed << std::setprecision(1); // 1 decimal place)
    }
    ss << dValue << suffix;
    return ss.str();
}