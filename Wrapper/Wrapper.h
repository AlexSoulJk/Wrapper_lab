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
    using ObjectMethod = T(Object::*)(Args...);
public:

    template<typename Object, typename... Args>
    Wrapper(Object* object, ObjectMethod<Object, Args...> method, DefaultArguments const& inputArgs) {
        if (inputArgs.size() != sizeof ...(Args))
        {
            throw std::runtime_error("Wrapper_ERROR: The number of default arguments entered does not match the number of arguments for calling the method.");
        }
        args = inputArgs;
        command = [this, object, method](std::vector<T> argsForFunc) {
            return call_method(object, method, argsForFunc, std::make_index_sequence<sizeof...(Args)>{});
        };
    }

    T execute(InputArguments const& Args) {
        std::vector<T> argsVec;
        return command(argsVec);
    }

    Wrapper() = default;
    Wrapper(Wrapper const&) = delete;
    Wrapper& operator=(Wrapper const&) = delete;
    Wrapper(Wrapper&&) = default;
    Wrapper& operator=(Wrapper&&) = default;
    ~Wrapper() = default;

private:
    template<typename Object, typename Method, size_t... I>
    T call_method(Object* object, Method method, std::vector<T> inArgs, std::index_sequence<I...>) {
        return ((object->*method)(inArgs[I]...));
    }
    Command command;
    DefaultArguments args;
};