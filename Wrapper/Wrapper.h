#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <stdexcept>

template<typename T>
class Wrapper {
    using Command = std::function<T(std::vector<T>&)>;
    using DefaultArguments = std::map<std::string, T>;
    using InputArguments = std::map<std::string, T>;
    template<typename Object, typename... Args>
    using ObjectMethod = T(Object::*func)(Args...);
public:
    template<typename Object, typename... Args>
    Wrapper(Object* object, ObjectMethod<Object,Args...> method, DefaultArguments const& Args);

    T execute(InputArguments const& Args);

    Wrapper() = default;
    Wrapper(Wrapper const&) = delete;
    Wrapper& operator=(Wrapper const&) = delete;
    Wrapper(Wrapper&&) = default;
    Wrapper& operator=(Wrapper&&) = default;
    ~Wrapper() = default;

private:
    Command command;
    DefaultArguments args;
};