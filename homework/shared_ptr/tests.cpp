#include <gtest/gtest.h>

#include "MakeShared.hpp"
#include "SharedPointer.hpp"
#include "WeakPointer.hpp"

int testValue = 5;

class TestClass {
public:
    int testFunction() {
        return testValue;
    }
};

class SharedPointerTest : public ::testing::Test {
protected:
    SharedPointerTest() : s_ptr(new int{testValue}) {}
    SharedPointer<int> s_ptr;
};

class WeakPointerTest : public ::testing::Test {
protected:
    WeakPointerTest() : ss_ptr(new int{testValue}) {}
    SharedPointer<int> ss_ptr;
    WeakPointer<int> w_ptr{ss_ptr};
};

class ControlBlockTest : public ::testing::Test {
protected:
    ControlBlock<int> testControlBlock;
};

TEST_F(SharedPointerTest, shouldCreateSharedPointerFromWeakPointer) {
    WeakPointer<int> w_ptr{s_ptr};

    SharedPointer<int> ss_ptr{w_ptr};

    ASSERT_EQ(ss_ptr.get(), s_ptr.get());
}

TEST_F(SharedPointerTest, shouldCopySharedPointer) {
    auto newPtr(s_ptr);
    auto newPtr1 = s_ptr;

    ASSERT_EQ(*s_ptr, *newPtr);
    ASSERT_EQ(*s_ptr, *newPtr1);
}

TEST_F(SharedPointerTest, shouldMoveSharedPointer) {
    auto newPtr(std::move(s_ptr));
    ASSERT_EQ(*newPtr, testValue);
}

TEST_F(SharedPointerTest, shouldResetSharedPtr) {
    s_ptr.reset();

    ASSERT_EQ(s_ptr.get(), nullptr);
}

TEST_F(SharedPointerTest, shouldReturnUseCountOfSharedPointer) {
    int finalNumberOfReferences = 2;
    auto newPtr = s_ptr;

    ASSERT_EQ(s_ptr.use_count(), finalNumberOfReferences);
}

TEST_F(SharedPointerTest, shouldUseDereferenceOperatorOfSharedPointer) {
    ASSERT_EQ(*s_ptr, testValue);
}

TEST_F(SharedPointerTest, shouldUseArrowOperatorOfSharedPointer) {
    SharedPointer<TestClass> s_ptr(new TestClass{});

    ASSERT_EQ(s_ptr->testFunction(), testValue);
}

TEST_F(SharedPointerTest, shouldReturnBoolWhenUsingBoolOperator) {
    SharedPointer<int> s_ptrNew;

    ASSERT_TRUE(s_ptr);
    ASSERT_FALSE(s_ptrNew);
}

TEST_F(WeakPointerTest, shouldReturnUseCountEqualTo0WhenCreatedByDefault) {
    WeakPointer<int> w_ptr{};
    ASSERT_EQ(w_ptr.use_count(), 0);
}

TEST_F(WeakPointerTest, shouldReturnUseCountEqualTo1WhenCreatedBySharedPointer) {
    ASSERT_EQ(w_ptr.use_count(), 1);
}

TEST_F(WeakPointerTest, shouldReturnSharedPointerWhenLockWeakPointer) {
    auto s_ptrNew = w_ptr.lock();
    ASSERT_EQ(*s_ptrNew, testValue);
}

TEST_F(WeakPointerTest, shouldUseMoveConstructor) {
    WeakPointer<int> w_ptrNew{std::move(w_ptr)};
    ASSERT_TRUE(w_ptr.expired());
    ASSERT_EQ(w_ptrNew.use_count(), 1);
}

TEST_F(WeakPointerTest, shouldUseMoveAssignment) {
    WeakPointer<int> w_ptrNew{};
    w_ptrNew = std::move(w_ptr);
    ASSERT_TRUE(w_ptr.expired());
    ASSERT_EQ(w_ptrNew.use_count(), 1);
}

TEST_F(WeakPointerTest, shouldUseCopyAssignment) {
    WeakPointer<int> w_ptrNew{};
    w_ptrNew = w_ptr;
    ASSERT_EQ(w_ptr.use_count(), 1);
}

TEST_F(ControlBlockTest, shouldGetSharedRefs) {
    ASSERT_EQ(testControlBlock.getShared(), 0);
}

TEST_F(ControlBlockTest, shouldGetWeakRefs) {
    ASSERT_EQ(testControlBlock.getWeak(), 0);
}

TEST_F(ControlBlockTest, shouldIncreaseSharedRefs) {
    testControlBlock.increaseShared();
    ASSERT_EQ(testControlBlock.getShared(), 1);
}

TEST_F(ControlBlockTest, shouldIncreaseWeakRefs) {
    testControlBlock.increaseWeak();
    ASSERT_EQ(testControlBlock.getWeak(), 1);
}

TEST_F(ControlBlockTest, shouldDecreaseSharedRefs) {
    testControlBlock.increaseShared();
    testControlBlock.decreaseShared();
    ASSERT_EQ(testControlBlock.getShared(), 0);
}

TEST_F(ControlBlockTest, shouldDecreaseWeakRefs) {
    testControlBlock.increaseWeak();
    testControlBlock.decreaseWeak();
    ASSERT_EQ(testControlBlock.getWeak(), 0);
}

TEST(MakeSharedTest, shouldUseMakeSharedOnSingleTestValue) {
    auto ms_ptr = MakeShared<int>(testValue);
    ASSERT_EQ(*ms_ptr, testValue);
}

TEST(MakeSharedTest, shouldUseMakeSharedOnExampleStructure) {
    struct TestStructure {
        TestStructure(int x, int y, int z) : x_(x), y_(y), z_(z){};
        int x_;
        int y_;
        int z_;
    };
    auto ms_ptr = MakeShared<TestStructure>(testValue, testValue, testValue);
    ASSERT_EQ(ms_ptr->x_, testValue);
    ASSERT_EQ(ms_ptr->y_, testValue);
    ASSERT_EQ(ms_ptr->z_, testValue);
}
