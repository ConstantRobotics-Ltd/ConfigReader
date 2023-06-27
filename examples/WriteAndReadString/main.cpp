#include <iostream>
#include "ConfigReader.h"



/// Link namespaces.
using namespace std;
using namespace cr::utils;



/// Custom parameter class.
class CustomParam
{
public:
    /// Parameter 1.
    int param1{1};
    /// Parameter 2.
    int param2{2};

    /// Declare params as readable for JSON.
    JSON_READABLE(CustomParam, param1, param2)
};



/// Parameters class.
class Params
{
public:
    /// Parameter.
    int param1{-10};
    /// Parameter.
    float param2{10.0f};
    /// Parameter.
    double param3{-10.0};
    /// Parameter.
    bool param4{false};
    /// Mass of parameters.
    float mass1[3];
    /// Mass of parameters.
    int mass2[3];
    /// List of parameters.
    vector<int> list1{vector<int>()};
    /// List of objects.
    vector<CustomParam> list2{vector<CustomParam>()};

    /// Declare params as readable for JSON.
    JSON_READABLE(Params, param1, param2, param3, mass1, list1, list2)
};



// Entry point.
int main(void)
{
    cout<< "==================================================" << endl;
    cout<< "ConfigReader v" << ConfigReader::getVersion()       << endl;
    cout<< "Write and read string example"                      << endl;
    cout<< "==================================================" << endl;
    cout<< endl;

    // Prepare parameters.
    Params outParams;
    outParams.param1 = rand() % 255;
    outParams.param2 = (float)(rand() % 255);
    outParams.param3 = (double)(rand() % 255);
    outParams.param4 = true; // Will not be saved.
    for (int i = 0; i < 4; ++i)
    {
        outParams.list1.push_back(rand() % 255);
    }
    for (int i = 0; i < 4; ++i)
    {
        CustomParam param;
        param.param1 = rand() % 255;
        param.param2 = rand() % 255;
        outParams.list2.push_back(param);
    }
    for (int i = 0; i < 4; ++i)
        outParams.mass1[i] = (float)(rand() % 255);
    for (int i = 0; i < 4; ++i)
        outParams.mass2[i] = (int)(rand() % 255);

    // Copy params to config reader.
    ConfigReader outConfig;
    if (!outConfig.set(outParams, "Params"))
    {
        cout << "ERROR: Can't copy params" << endl;
        return -1;
    }

    // Write params to string.
    string jsonData;
    if (!outConfig.writeToString(jsonData))
    {
        cout << "ERROR: Can't write file" << endl;
        return -1;
    }

    // Read params from string.
    ConfigReader inConfig;
    if(!inConfig.readFromString(jsonData))
    {
        cout << "ERROR: Can't read file" << endl;
        return -1;
    }

    // Read values from "Params" section.
    Params inParams;
    if(!inConfig.get(inParams, "Params"))
    {
        cout << "ERROR: Can't read params" << endl;
        return -1;
    }

    // Compare params.
    if (outParams.param1 != inParams.param1)
        cout << "ERROR: param1 has wrong value" << endl;
    if (outParams.param2 != inParams.param2)
        cout << "ERROR: param2 has wrong value" << endl;
    if (outParams.param3 != inParams.param3)
        cout << "ERROR: param3 has wrong value" << endl;
    if (outParams.param4 != inParams.param4)
        cout << "OK: param4 not included to list for reading/writing" << endl;
    for (int i = 0; i < 3; ++i)
        if (outParams.mass1[i] != inParams.mass1[i])
            cout << "ERROR: mass1[" << i << "] has wrong value" << endl;
    for (int i = 0; i < 3; ++i)
        if (outParams.mass2[i] != inParams.mass2[i])
            cout << "OK: mass2[" << i << "] not included to list for" <<
                    "reading/writing" << endl;
    if (outParams.list1.size() == inParams.list1.size())
    {
        for (int i = 0; i < inParams.list1.size(); ++i)
            if (outParams.list1[i] != inParams.list1[i])
                cout << "ERROR: list1[" << i << "] has wrong value" << endl;
    }
    else
    {
        cout << "ERROR: list1 has wrong size" << endl;
    }
    if (outParams.list2.size() == inParams.list2.size())
    {
        for (int i = 0; i < inParams.list2.size(); ++i)
            if (outParams.list2[i].param1 != inParams.list2[i].param1 ||
                outParams.list2[i].param2 != inParams.list2[i].param2)
                cout << "ERROR: list1[" << i << "] has wrong value" << endl;
    }
    else
    {
        cout << "ERROR: list2 has wrong size" << endl;
    }
}
