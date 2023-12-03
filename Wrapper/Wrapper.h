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

    Command command;
    DefaultArguments args;
    int const size_args = 0;

public:



    template<typename Object, typename... Args>
    Wrapper(Object* object, ObjectMethod<Object, Args...> method, DefaultArguments const& inputArgs) noexcept : size_args(sizeof ...(Args)), args(inputArgs) {
        command = [this, object, method](std::vector<T> argsForFunc) {
            if (argsForFunc.size() != size_args) 
                throw std::runtime_error("Wrapper_ERROR: The number of default arguments entered does not match the number of arguments for calling the method ");
            return call_method(object, method, argsForFunc, std::make_index_sequence<sizeof...(Args)>{});
        };
    }

    T execute(InputArguments Args) {
        std::string nameOfInvalidArg = "";
        //validation of name of Input params.
        if (!isNamesOfInputParamValid(Args, nameOfInvalidArg))
            throw std::runtime_error("Wrapper_ERROR: The param with name " + nameOfInvalidArg + "doesn't found in command ");
        std::vector<T> currentValues;
        //adding args into current values to invoke function
        for (auto const& arg : args) {
            currentValues.push_back(Args.find(arg.first) != Args.end() ? Args[arg.first] : arg.second);
        }

        return command(currentValues);
    }

    void setDefaultArgumets(DefaultArguments const& inputArgs) {
        if (size_args != inputArgs.size()) 
            throw std::runtime_error("Wrapper_ERROR: The number of default arguments entered does not match the number of arguments for calling the method ");
        args = inputArgs;
    }
    Wrapper& operator=(Wrapper&&) noexcept = default;
    ~Wrapper() noexcept = default;
    Wrapper(Wrapper const&) = delete;
    Wrapper& operator=(Wrapper const&) = delete;
    Wrapper() = delete;
    Wrapper(Wrapper&&) = default;
private:

    template<typename Object, typename Method, size_t... I>
    T call_method(Object* object, Method method, std::vector<T> inArgs, std::index_sequence<I...>) {
        return ((object->*method)(inArgs[I]...));
    }


    bool isNamesOfInputParamValid(InputArguments const& Args, std::string nameOfInvalidArg) {
        for (auto const& arg : Args) {
            if (args.find(arg.first) == args.end()) {
                nameOfInvalidArg = arg.first;
                return false;
            }
        }
        return true;
    }

};