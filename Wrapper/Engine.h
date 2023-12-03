#pragma once
#include "Wrapper.h"
class Engine {
public:

    template<typename T>
    void register_command(Wrapper<T>* wrapper, std::string const& command_name){
        if (commands.find(command) != commands.end())
            throw std::runtime_error("Engine_ERROR: Command " + command_name + " already exist");
        commands.insert({ command, wrapper });
    }

    template<typename T>
    T execute(const std::string& command_name, std::map<std::string, T> const args) {
        auto it = commands.find(command);

        if (it == commands.end())
            throw std::runtime_error("Engine_ERROR: Command " + command_name + " has not been registered");
        
        Wrapper<T>* wrapper = static_cast<Wrapper<T>*>(it->second);

        try {
            return wrapper->execute(args);
        }
        catch (std::runtime_error const& e) {
            throw std::runtime_error(e.what() + command_name + "!");
        }
        
    }

    Engine() = default;
    Engine(Engine const&) = delete;
    Engine& operator =(Engine const&) = delete;
    Engine(Engine&&) = default;
    Engine& operator =(Engine&&) = default;
    ~Engine() = default;

private:

    //Have void* cos need to store Wrapper<?>, think that need Wrapper_base.
    std::map<std::string, void*> commands;
};