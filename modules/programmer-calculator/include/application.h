// Copyright 2017 Israfilov Marat

#ifndef MODULES_PROGRAMMER_CALCULATOR_INCLUDE_APPLICATION_H_
#define MODULES_PROGRAMMER_CALCULATOR_INCLUDE_APPLICATION_H_

#include <string>

class Application {
 public:
    Application();
    std::string operator()(int argc, const char** argv);

 private:
    void help(const char* appname, const char* message = "");
    bool validateNumberOfArguments(int argc, const char** argv);
    std::string message_;
    typedef struct {
        std::string first_number;
        std::string second_number;
        char operation;
        char type;
    } Arguments;
};

#endif  // MODULES_PROGRAMMER_CALCULATOR_INCLUDE_APPLICATION_H_
