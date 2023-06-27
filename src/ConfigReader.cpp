#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "ConfigReader.h"
#include "ConfigReaderVersion.h"



// Method to get class version.
std::string cr::utils::ConfigReader::getVersion()
{
    // Return version string.
    return CONFIG_READRER_VERSION;
}



// Class constructor.
cr::utils::ConfigReader::ConfigReader()
{

}



// Class destructor.
cr::utils::ConfigReader::~ConfigReader()
{

}



// Method to read configuration from file.
bool cr::utils::ConfigReader::readFromFile(std::string fileName)
{
    // Open JSON file.
    std::ifstream in(fileName);
    if (!in.is_open())
        return false;

    // Parse JSON.
    try
    {
        m_jsonConf = json::parse(in);
    }
    catch (json::parse_error& e)
    {
        std::cout << e.what() << std::endl;
        // Close file.
        in.close();
        return false;
    }

    // Close file.
    in.close();

    return true;
}



// Method to write configuration to file.
bool cr::utils::ConfigReader::writeToFile(std::string fileName)
{
    // Create output stream.
    std::ofstream out(fileName);

    // Write to file.
    out << std::setw(4) << m_jsonConf << std::endl;

    // Close output stream.
    out.close();

    return true;
}



// Method to read configuration from string.
bool cr::utils::ConfigReader::readFromString(std::string json)
{
    // Parse JSON.
    try
    {
        m_jsonConf = json::parse(json);
    }
    catch (json::parse_error& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}



// Method to write configuration to string.
bool cr::utils::ConfigReader::writeToString(std::string &json)
{
    // Parse JSON.
    try
    {
        json = m_jsonConf.dump();
    }
    catch (json::parse_error& e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }

    return true;
}



// Set recursive.
json cr::utils::ConfigReader::setRecursive(json dst, json src,
                                           std::vector<std::string> tokenList)
{
    // Check list size.
    if (tokenList.size() > 0)
    {
        // Get string to file.
        std::string token = tokenList[0];
        // Create token list.
        std::vector<std::string> newTokenList = tokenList;
        newTokenList.erase(newTokenList.begin());
        const auto it = dst.find(token);
        if (it != dst.end())
        {
            *it = setRecursive(*it, src, newTokenList);
        }else
        {
            dst[token] = setRecursive(dst[token], src, newTokenList);
        }
        return dst;
    }else
    {
        return src;
    }
}



