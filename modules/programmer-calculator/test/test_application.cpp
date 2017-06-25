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

TEST_F(ApplicationTest, Do_Print_Help) {
    vector<string> args = {};

    Act(args);

    Assert("This is a hex, oct, bin number calculator application.");
}

TEST_F(ApplicationTest, Is_Checking_Number_Of_Arguments) {
    vector<string> args = { "101", "110", "3" };

    Act(args);

    Assert("ERROR: Should be 4 arguments.*");
}