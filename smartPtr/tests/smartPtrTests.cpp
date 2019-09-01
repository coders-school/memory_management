#include <gtest/gtest.h>
#include <string>
#include "smartPtr.hpp"
#include "A.hpp"

class smartPointerTests : public ::testing::Test {
public:
    smartPointerTests()
    {
    }
    ~smartPointerTests()
    {
    }
    void SetUp()
    {    
    }
    void TearDown()
    {  
    }

    bool bool1 = true;
    bool bool2 = false;
    char char1 = 'a';
    char char2 = 'b';
    int int1 = 11;
    int int2 = 13;
    float flt1 = 1.41421356237;
    float flt2 = 1.73205080757;
    double dbl1 = 3.14159265359;
    double dbl2 = 2.718281828459;
    std::string str1 = "Lorem ipsum dolor sit amet";
    std::string str2 = "Consectetur adipiscing elit";
    int AInt1 = 17;
    int AInt2 = 29;
};

TEST_F(smartPointerTests, canProperlyConstructAndDereferenceSmartPtr)
{
    // ARRANGE
    // ACT
    smartPointer<bool> sPtrBool1(new bool(bool1));
    smartPointer<char> sPtrChar1(new char(char1));
    smartPointer<int> sPtrInt1(new int(int1));
    smartPointer<float> sPtrFloat1(new float(flt1));
    smartPointer<double> sPtrDouble1(new double(dbl1));
    smartPointer<std::string> sPtrString1(new std::string(str1));
    smartPointer<A> sPtrA1(new A(AInt1));
    
    // ASSERT
    ASSERT_TRUE(*sPtrBool1 == bool1);
    ASSERT_TRUE(*sPtrChar1 == char1);
    ASSERT_TRUE(*sPtrInt1 == int1);
    ASSERT_TRUE(*sPtrFloat1 == flt1);
    ASSERT_TRUE(*sPtrDouble1 == dbl1);
    ASSERT_TRUE(*sPtrString1 == str1);
    ASSERT_TRUE(*sPtrA1 == A(AInt1));
}

TEST_F(smartPointerTests, canConstructSmartPtrWithMoveConstructor)
{
    // ARRANGE
    smartPointer<bool> sPtrBool2(new bool(bool2));
    smartPointer<char> sPtrChar2(new char(char2));
    smartPointer<int> sPtrInt2(new int(int2));
    smartPointer<float> sPtrFloat2(new float(flt2));
    smartPointer<double> sPtrDouble2(new double(dbl2));
    smartPointer<std::string> sPtrString2(new std::string(str2));
    smartPointer<A> sPtrA2(new A(AInt2));  

    // ACT
    smartPointer<bool> sPtrBool1(std::move(sPtrBool2));
    smartPointer<char> sPtrChar1(std::move(sPtrChar2));
    smartPointer<int> sPtrInt1(std::move(sPtrInt2));
    smartPointer<float> sPtrFloat1(std::move(sPtrFloat2));
    smartPointer<double> sPtrDouble1(std::move(sPtrDouble2));
    smartPointer<std::string> sPtrString1(std::move(sPtrString2));
    smartPointer<A> sPtrA1(std::move(sPtrA2));

    // ASSERT
    ASSERT_TRUE(*sPtrBool1 == bool2);
    ASSERT_TRUE(*sPtrChar1 == char2);
    ASSERT_TRUE(*sPtrInt1 == int2);
    ASSERT_TRUE(*sPtrFloat1 == flt2);
    ASSERT_TRUE(*sPtrDouble1 == dbl2);
    ASSERT_TRUE(*sPtrString1 == str2);
    ASSERT_TRUE(*sPtrA1 == A(AInt2));
}

TEST_F(smartPointerTests, canChangeSmartPtrValueWithDereferenceOperator)
{
    // ARRANGE
    smartPointer<bool> sPtrBool1(new bool(bool1));
    smartPointer<char> sPtrChar1(new char(char1));
    smartPointer<int> sPtrInt1(new int(int1));
    smartPointer<float> sPtrFloat1(new float(flt1));
    smartPointer<double> sPtrDouble1(new double(dbl1));
    smartPointer<std::string> sPtrString1(new std::string(str1));
    smartPointer<A> sPtrA1(new A(AInt1));
    A A2(23);

    // ACT
    *sPtrBool1 = bool2;
    *sPtrChar1 = char2;
    *sPtrInt1 = int2;
    *sPtrFloat1 = flt2;
    *sPtrDouble1 = dbl2;
    *sPtrString1 = str2;
    *sPtrA1 = A2;

    // ASSERT:
    ASSERT_TRUE(*sPtrBool1==bool2);
    ASSERT_TRUE(*sPtrChar1==char2);
    ASSERT_TRUE(*sPtrInt1==int2);
    ASSERT_TRUE(*sPtrFloat1==flt2);
    ASSERT_TRUE(*sPtrDouble1==dbl2);
    ASSERT_TRUE(*sPtrString1==str2);
    ASSERT_TRUE(*sPtrA1==A2);
}

TEST_F(smartPointerTests, canUseArrowOperatorOnUnderlyingClassInstance)
{
    // ARRANGE
    const int input1 = 31;
    const int input2 = 37;
    int output1, output2;
    smartPointer<A> sPtrA1(new A(input1));
    smartPointer<A> sPtrA2(new A(input2));

    // ACT
    output1 = sPtrA1->bar();
    output2 = sPtrA2->bar();

    // ASSERT:
    ASSERT_TRUE(2*input1==output1);
    ASSERT_TRUE(2*input2==output2);
}

TEST_F(smartPointerTests, checkIfGetMethodReturnsUnderlyingPointer)
{
    // ARRANGE
    smartPointer<bool> sPtrBool1(new bool(bool1));
    smartPointer<char> sPtrChar1(new char(char1));
    smartPointer<int> sPtrInt1(new int(int1));
    smartPointer<float> sPtrFloat1(new float(flt1));
    smartPointer<double> sPtrDouble1(new double(dbl1));
    smartPointer<std::string> sPtrString1(new std::string(str1));
    smartPointer<A> sPtrA1(new A(AInt1));
    bool* rPtrBool1 = nullptr;
    char* rPtrChar1 = nullptr;
    int* rPtrInt1 = nullptr;
    float* rPtrFloat1 = nullptr;
    double* rPtrDouble1 = nullptr;
    std::string* rPtrString1 = nullptr;
    A* rPtrA1 = nullptr;

    // ACT
    rPtrBool1 = sPtrBool1.get();
    rPtrChar1 = sPtrChar1.get();
    rPtrInt1 = sPtrInt1.get();
    rPtrFloat1 = sPtrFloat1.get();
    rPtrDouble1 = sPtrDouble1.get();
    rPtrString1 = sPtrString1.get();
    rPtrA1 = sPtrA1.get();

    // ASSERT
    ASSERT_FALSE(nullptr==rPtrBool1);
    ASSERT_FALSE(nullptr==rPtrChar1);
    ASSERT_FALSE(nullptr==rPtrInt1);
    ASSERT_FALSE(nullptr==rPtrFloat1);
    ASSERT_FALSE(nullptr==rPtrDouble1);
    ASSERT_FALSE(nullptr==rPtrString1);
    ASSERT_FALSE(nullptr==rPtrA1);
    ASSERT_TRUE(rPtrBool1==sPtrBool1.get());
    ASSERT_TRUE(rPtrChar1==sPtrChar1.get());
    ASSERT_TRUE(rPtrInt1==sPtrInt1.get());
    ASSERT_TRUE(rPtrFloat1==sPtrFloat1.get());
    ASSERT_TRUE(rPtrDouble1==sPtrDouble1.get());
    ASSERT_TRUE(rPtrString1==sPtrString1.get());
    ASSERT_TRUE(rPtrA1==sPtrA1.get());  
}   





