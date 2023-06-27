#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include <nlohmann/json.hpp>

using namespace nlohmann;

namespace cr
{
namespace utils
{

#define JSON_READABLE(Type, ...) \
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Type, __VA_ARGS__)

/**
 * @brief Config reader class.
 */
class ConfigReader
{
public:

    /**
     * @brief Get string of current class version.
     * @return String of current class version in format "Major.Minor.Patch".
     */
    static std::string getVersion();

    /**
     * @brief Class constructor.
     */
    ConfigReader();

    /**
     * @brief Class destructor.
     */
    ~ConfigReader();

    /**
     * @brief Read configuration from file.
     * @param fileName Configuration file name.
     * @return TRUE if the configuration was read or FALSE if not.
     */
    bool readFromFile(std::string fileName);

    /**
     * @brief Write configuration to file.
     * @param fileName File name to write configuration.
     * @return TRUE if the configuration was writed or FALSE if not.
     */
    bool writeToFile(std::string fileName);

    /**
     * @brief Read configuration from string.
     * @param json String to read configuration.
     * @return TRUE if the configuration was read or FALSE if not.
     */
    bool readFromString(std::string json);

    /**
     * @brief Write configuration to string.
     * @param json String name to write configuration.
     * @return TRUE if the configuration was writed or FALSE if not.
     */
    bool writeToString(std::string& json);

    /**
     * @brief Get object.
     * @param obj Object.
     * @param objName Name of object/property.
     * @return TRUE If the object was read or FALSE if not.
     */
    template<class T>
    bool get(T& obj, std::string objName = "") {
    json _j;
    if (!objName.empty())
    {
        std::string delimiter = ".";
        std::string _name = objName;
        size_t pos = 0;
        std::string token;
        _j = m_jsonConf;
        while ((pos = _name.find(delimiter)) != std::string::npos) {
            token = _name.substr(0, pos);
            _j = _j.at(token);
            _name.erase(0, pos + delimiter.length());
        }
        _j = _j.at(_name);
    }
    else
        _j = m_jsonConf;
    try {
        obj = _j.get<T>();
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

    /**
     * @brief Set object.
     * @param obj Object.
     * @param objName Name of object/property.
     * @return TRUE If the object was set or FALSE if not.
     */
    template<class T>
    bool set(T& obj, std::string objName = "") {
    json _j = m_jsonConf;
    std::string _name = objName;
    std::vector<std::string> tokenList = std::vector<std::string>();
    if (!objName.empty())
    {
        std::string delimiter = ".";
        size_t pos = 0;
        std::string token = "";
        while ((pos = _name.find(delimiter)) != std::string::npos) {
            token = _name.substr(0, pos);
            tokenList.push_back(token);
            _name.erase(0, pos + delimiter.length());
        }
        tokenList.push_back(_name);
    }
    try {
        m_jsonConf = setRecursive(m_jsonConf, obj, tokenList);
        return true;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

private:

    /// Json object.
    json m_jsonConf;

    /// Set object recursive.
    json setRecursive(json dst, json src, std::vector<std::string> tokenList);
};
}
}
