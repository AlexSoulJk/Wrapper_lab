#pragma once
#include "Wrapper.h"
class Engine {
public:
    template<typename T>
    void register_command(Wrapper<T>* wrapper, std::string const& command);

    template<typename T>
    T execute(const std::string& command, std::map<std::string, T> const args);

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