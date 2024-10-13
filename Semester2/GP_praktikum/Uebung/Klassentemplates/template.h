#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <vector>
#include <string>

template<typename T>
class BMap 
{

public:
    void insert(const std::string key, const T value);
    std::vector<T> getVector(std::string key);
private:
    std::map<std::string, std::vector<T>> aMap;

};

template<typename T>
void BMap<T>::insert(std::string key, const T value) 
{
    bool keyExists = false;
    for (auto& e: aMap) 
    {
        if(key == e.first) 
        {
            e.second.push_back(value);
            keyExists = true;
            break;    
        }
    }
    if(!keyExists) 
    {
        aMap[key].push_back(value);
    }
}

template<typename T>
std::vector<T> BMap<T>::getVector(std::string key) 
{
    for(const auto& e: aMap) {
        if(key == e.first) 
            return e.second;
    }
    std::cout << "Key not found, returned empty vector" << std::endl;
    return std::vector<T> {};
}


#endif