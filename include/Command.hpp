/*
 * @Description: command template class
 * @Author: Sean
 * @Date: 2021-08-06 11:10:44
 * @LastEditTime: 2021-08-06 17:27:23
 * @LastEditors: Sean
 * @Reference: 
 */

#pragma once

// c++ stl
#include <functional>
#include <memory>
#include <unordered_map>

#include <typeinfo>

namespace CommandSystem{
class BaseCommand {
public:
    ~BaseCommand() {}
};

template<typename... ArgTypes>
class Command : public BaseCommand {
    std::function<void(ArgTypes...)> func;
public:
    explicit Command(std::function<void(ArgTypes...)> _func) : func(_func) {}
    void operator()(ArgTypes... args) {
        if (func)
            func(args...);
    }
};

class Manager {
public:
    Manager(){}
    template<typename T>
    void attach(std::string name, const T& func) {
        hash.insert(std::make_pair(name, std::shared_ptr<BaseCommand>(new T(func))));
    }
    template<typename... ArgTypes>
    void execute(std::string name, ArgTypes... args) {
        std::unordered_map<std::string, std::shared_ptr<BaseCommand>>::const_iterator itr = hash.find(name);

        if (itr == hash.end())
            return;
        auto cur_cmd = (Command<ArgTypes...>*)(itr->second.get());
        if (cur_cmd)
            (*cur_cmd)(args...);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<BaseCommand>> hash;
};
};
