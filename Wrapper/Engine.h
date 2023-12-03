#pragma once
#include "Wrapper.h"
template<typename T>
class Engine {
    std::map<std::string, Wrapper<T>*> commands;
public:

    void register_command(Wrapper<T>* wrapper, std::string const& command_name){
        if (commands.find(command_name) != commands.end())
            throw std::runtime_error("Engine_ERROR: Command " + command_name + " already exist");
        commands.insert({ command_name, wrapper });
    }

    T execute(const std::string& command_name, std::map<std::string, T> const& args) {
        
        Wrapper<T>* wrapper = getCommand(command_name);
        try {
            return wrapper->execute(args);
        }
        catch (std::runtime_error const& e) {
            throw std::runtime_error(e.what() + command_name + "!");
        }
        
    }

    void setDefaultValueInCommand(std::string const command_name, std::map<std::string, T> const& args) {
        Wrapper<T>* wrapper = getCommand(command_name);

        try {
             wrapper->setDefaultArgumets(args);
        }
        catch (std::runtime_error const& e) {
            throw std::runtime_error(e.what() + command_name + "!");
        }

    }
    Engine() = default;
    Engine(Engine&&) = default;
    Engine& operator =(Engine&&) = default;
    ~Engine() = default;
    Engine(Engine const&) = delete;
    Engine& operator =(Engine const&) = delete;


private:
    Wrapper<T>* getCommand(std::string const& command_name) {
        auto it = commands.find(command_name);

        if (it == commands.end())
            throw std::runtime_error("Engine_ERROR: Command " + command_name + " has not been registered");

        return static_cast<Wrapper<T>*>(it->second);
    }

};