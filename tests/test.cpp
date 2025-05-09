#include <gtest/gtest.h>
#include <string>

std::string intToBinary(int input);
void checkAddress(const std::string input);

TEST(IntToBinaryTest, ConvertsCorrectly) {
    EXPECT_EQ(intToBinary(0), "00000000");
    EXPECT_EQ(intToBinary(5), "00000101");
    EXPECT_EQ(intToBinary(255), "11111111");
}

TEST(CheckAddressTest, ValidAddressDoesNotThrow) {
    EXPECT_NO_THROW(checkAddress("192.168.1.1/24"));
}

TEST(CheckAddressTest, InvalidAddressThrows) {
    EXPECT_THROW(checkAddress("999.999.999.999/24"), std::invalid_argument);
    EXPECT_THROW(checkAddress("192.168.1.1/33"), std::invalid_argument);
    EXPECT_THROW(checkAddress("192.168.1.1"), std::invalid_argument);
}