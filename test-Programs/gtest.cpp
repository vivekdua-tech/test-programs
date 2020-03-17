//
//  gtest.cpp
//  test-Programs
//
//  Created by vidua on 2/28/20.
//  Copyright © 2020 Vivek Dua. All rights reserved.
//

#include <iostream>
#include <gtest/gtest.h>

class AdditionTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
    }
};
TEST_F(AdditionTest,twoValues){
    const int x = 4;
    const int y = 5;
    Addition addition;
    EXPECT_EQ(9,addition.twoValues(x,y));
    EXPECT_EQ(5,addition.twoValues(2,3));
}


int main(int argc, char **argv) {
    
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
    
}


