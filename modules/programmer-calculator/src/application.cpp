// Copyright 2017 Israfilov Marat

#include "include/application.h"
#include "include/programmer_calculator.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sstream>

Application::Application() : message_("") {}

void Application::help(const char* appname, const char* message) {
    message_ =
        std::string(message) +
          "This is a hex, oct, bin number calculator application.\n\n" +
          "Please provide arguments in the following format:\n\n"+

          "  $ " + appname + " <first_number> <second_number> <type> <operation>\n\n" +    

          "<operation> is one of '+', '-', '*', '/'\n\n" +
          "<type> is one of '1'-HEX, '2'-OCT, '3'-BIN ";
}

bool Application::validateNumberOfArguments(int argc, const char** argv) {
    if (argc == 1) {
        help(argv[0]);
        return false;
    } else if (argc != 5) {
        help(argv[0], "ERROR: Should be 4 arguments.\n\n");
        return false;
    }
    return true;
}

/*double parseDouble(const char* arg) {
    char* end;
    double value = strtod(arg, &end);

    if (end[0]) {
        throw std::string("Wrong number format!");
    }

    return value;
}*/

char parseOperation(const char* arg) {
    char op;
    if (strcmp(arg, "+") == 0) {
        op = '+';
    } else if (strcmp(arg, "-") == 0) {
        op = '-';
    } else if (strcmp(arg, "*") == 0) {
        op = '*';
    } else if (strcmp(arg, "/") == 0) {
        op = '/';
    } else {
        throw std::string("Wrong operation format!");
    }
    return op;
}

std::string Application::operator()(int argc, const char** argv) {
    Arguments args;

    if (!validateNumberOfArguments(argc, argv)) {
        return message_;
    }
    try {
        args.first_number  = argv[1];
        args.second_number = argv[2];
        args.type          = argv[3];        
        args.operation     = parseOperation(argv[4]);
    }
    catch(std::string& str) {
        return str;
    }

    ProgrammerCalculator converter; 
    int tmp_num1;
	int tmp_num2;
    int tmp_result;    
    std::ostringstream stream;
	
	switch (args.type) {
     case '1':
        tmp_num1 = converter.ConvertHexToDec(argv[1]);
		tmp_num2 = converter.ConvertHexToDec(argv[2]);
        break;
     case '2':
        tmp_num1 = converter.ConvertOctToDec(argv[1]);
		tmp_num2 = converter.ConvertOctToDec(argv[2]);
        break;
     case '3':
        tmp_num1 = converter.ConvertBinToDec(argv[1]);
		tmp_num2 = converter.ConvertBinToDec(argv[2]);
        break;
     default:
        return "Wrong type!";
    }
	
    switch (args.operation) {
     case '+':
        tmp_result = tmp_num1 + tmp_num2;        
        break;
     case '-':
        tmp_result = tmp_num1 - tmp_num2;
        break;
     case '*':
        tmp_result = tmp_num1 * tmp_num2;
        break;
     case '/':
        try {
            tmp_result = tmp_num1 / tmp_num2;
            break;
        }
        catch(std::string& str) {
            return str;
        }
    }
	
	switch (args.type) {
     case '1':
        stream << converter.ConvertDecToHex(tmp_result);
        break;
     case '2':
        stream << converter.ConvertDecToOct(tmp_result);
        break;
     case '3':
        stream << converter.ConvertDecToBin(tmp_result);
        break;
     default:
        return "Wrong type!";
    }

    message_ = stream.str();

    return message_;
}