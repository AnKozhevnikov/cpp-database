#include <gtest/gtest.h>
#include "DataBase.h"

TEST(SampleTest, Addition) {
    EXPECT_EQ(2+2, 4);
}

int main() {
    testing::InitGoogleTest();
    int val = RUN_ALL_TESTS();
    return 0;
}