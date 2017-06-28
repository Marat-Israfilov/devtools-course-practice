// Copyright 2017 Israfilov Marat

#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>

#include "include/application.h"

using ::testing::internal::RE;
using std::vector;
using std::string;

class ApplicationTest : public ::testing::Test {
 protected:
    void Act(vector<string> args_) {
        vector<const char*> options;

        options.push_back("appname");
        for (size_t i = 0; i < args_.size(); ++i) {
            options.push_back(args_[i].c_str());
        }

        const char** argv = &options.front();
        int argc = static_cast<int>(args_.size()) + 1;

        output_ = app_(argc, argv);
    }

    void Assert(std::string expected) {
        EXPECT_TRUE(RE::PartialMatch(output_, RE(expected)));
    }

 private:
    Application app_;
    string output_;
};

TEST_F(ApplicationTest, Do_Print_Help_Without_Arguments) {
    vector<string> args = {};

    Act(args);

    Assert("This is a HEX, OCT, BIN number calculator application.");
}

TEST_F(ApplicationTest, Is_Checking_Number_Of_Arguments) {
    vector<string> args = { "101", "110", "3" };

    Act(args);

    Assert("ERROR: Should be 4 arguments.\n\n");
}

TEST_F(ApplicationTest, Can_Detect_Wrong_Type_Format) {
    vector<string> args = {"1", "10", "7", "+"};

    Act(args);

    Assert("Wrong type!");
}

TEST_F(ApplicationTest, Can_Detect_Wrong_Operation_Format) {
    vector<string> args = {"1", "1", "3", "%"};

    Act(args);

    Assert("Wrong operation format!");
}

TEST_F(ApplicationTest, Can_Detect_Wrong_Number_Format) {
    vector<string> args = {"1", "2", "3", "+"};

    Act(args);

    Assert("Numbers don't match the type!");
}

TEST_F(ApplicationTest, Can_Add) {
    vector<string> args = {"1f", "3", "1", "+"};

    Act(args);

    Assert("Result = 22");
}

TEST_F(ApplicationTest, Can_Diff) {
    vector<string> args = {"13", "3", "2", "-"};

    Act(args);

    Assert("Result = 10");
}

TEST_F(ApplicationTest, Can_Mult) {
    vector<string> args = {"11", "10", "3", "*"};

    Act(args);

    Assert("Result = 110");
}

TEST_F(ApplicationTest, Can_Divide) {
    vector<string> args = {"110", "11", "3", "/"};

    Act(args);

    Assert("Result = 10");
}

TEST_F(ApplicationTest, Can_Detect_Divide_By_Zero) {
    vector<string> args = {"120", "0", "2", "/"};

    Act(args);

    Assert("Can't divide by zero!");
}
