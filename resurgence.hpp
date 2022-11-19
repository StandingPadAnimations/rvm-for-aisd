#include "Resurgence/resurgence.h"
#include <cstdint>
#include <functional>
#include <string>

namespace rvm_cpp {
    // Result enum
    enum class Result : uint8_t {
        ERROR,
        OK
    };

    // Converts Result to uint8_1 because Resurgence doesn't understand the C++ Result enum 
    inline uint8_t result_to_rvm(Result res) {
        if (res == Result::ERROR) {
            return 1;
        }
        return 0;
    }
    
    inline Result to_result(uint8_t res) {
        if (res == 1) {
            return Result::ERROR;
        }
        return Result::OK;
    }
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

        // Registers a function to the interpreter
        Result register_function(const std::string& name, uint8_t(*function)(RVMState*)) {
            auto res = rvm_interpreter_register_function(instance, function, name.c_str());
            return to_result(res);
        }
    };
}