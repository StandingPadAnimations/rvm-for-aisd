#include "Resurgence/resurgence.h"
#include <cstdint>
#include <functional>
#include <string>

namespace rvm_cpp {
    // Result enum
    enum Result : uint8_t {
        ERROR = 1,
        OK = 0
    };

    // A wrapper around RVMCodeHolder from resurgence,h which manages allocation and destruction
    class RVM_CodeHolder {
        friend class RVM_Interpreter;
        RVM_CodeHolder() {
            holder = rvm_codeholder_new();
        }   
        ~RVM_CodeHolder() {
            rvm_codeholder_destroy(holder);
        }

        // Codeholder instance
        RVMCodeHolder* holder;
    };

    // A wrapper around RVMInterpreter from resurgence.h that manages allocation and destruction
    class RVM_Interpreter {
        friend RVM_CodeHolder;
        RVM_Interpreter(RVM_CodeHolder code_holder) {
            instance = rvm_interpreter_new(code_holder.holder);
        }
        ~RVM_Interpreter() {
            rvm_interpreter_destroy(instance);
        }

        // Instance of the interpreter
        RVMInterpreter* instance;

        Result register_function(const std::string& name, uint8_t(*function)(RVMState*)) {
            auto res = rvm_interpreter_register_function(instance, function, name.c_str());
        }
    };
}