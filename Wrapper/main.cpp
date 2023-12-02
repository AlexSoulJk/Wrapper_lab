#include<iostream>
#include "Subj.h"
#include "Wrapper.h"
#include "Engine.h"
int main() {
    Subj subj;
    try {
        Wrapper<int> wrapper(&subj, &Subj::summ, { {"arg1", 0}, {"arg2", 0} });
        Engine engine;
        engine.register_command<int>(&wrapper, "summ");
        std::cout << engine.execute<int>("summ", { {"arg1", 6}, {"arg2", 10} }) << std::endl;
        Wrapper<std::string> wrapperS(&subj, & Subj::getString);
        engine.register_command<double>(&wrapperS, "getString", {});
        std::cout << engine.execute<std::string>("getString", {}) << std::endl;
    }
    catch (std::runtime_error const& e) {
        std::cout << e.what() << std::endl;
    }
    

    return 0;
}