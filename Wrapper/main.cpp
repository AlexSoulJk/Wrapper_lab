#include<iostream>

#include "Subj.h"
#include "Wrapper.h"
#include "Engine.h"

int main() {
    Subj subj;
    try {
        Wrapper<int> wrapper(&subj, &Subj::summ, { {"arg1", 0}, {"arg", 0}});
        Engine<int> engineI;
        Engine<std::string> engineS;
        engineI.register_command(&wrapper, "summ");
        std::cout << engineI.execute("summ", { {"arg1", 6} }) << std::endl;
        Wrapper<std::string> wrapperS(&subj, &Subj::getString, {});
        engineS.register_command(&wrapperS, "getString");
        std::cout << engineS.execute("getString", {}) << std::endl;
    }
    catch (std::runtime_error const& e) {
        std::cout << e.what() << std::endl;
    }
    

    return 0;
}