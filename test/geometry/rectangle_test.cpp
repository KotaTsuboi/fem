#include "../../src/core/geometry/point.hpp"
#include "../../src/core/geometry/rectangle.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Return;

class MockPoint : public Point {
 public:
  MOCK_METHOD(double, X, (), (const, override));
  MOCK_METHOD(double, Y, (), (const, override));
  MOCK_METHOD(double, Z, (), (const, override));
};

class RectangleTest : public ::testing::Test {
  protected:
    virtual void SetUp() {
        MockPoint p1;
        MockPoint p2;

        EXPECT_CALL(p1, X())
            .WillRepeatedly(Return(-1));
        EXPECT_CALL(p1, Y())
            .WillRepeatedly(Return(-1));

        EXPECT_CALL(p2, X())
            .WillRepeatedly(Return(1));
        EXPECT_CALL(p2, Y())
            .WillRepeatedly(Return(1));

        aRectangle = std::make_shared<Rectangle>(p1, p2);
    }

    std::shared_ptr<Rectangle> aRectangle;
};

TEST_F(RectangleTest, MinXTest) {
    double expected = -1;

    double actual = aRectangle->MinX();

    EXPECT_EQ(expected, actual);
}

TEST_F(RectangleTest, MinYTest) {
    double expected = -1;

    double actual = aRectangle->MinY();

    EXPECT_EQ(expected, actual);
}

TEST_F(RectangleTest, MaxXTest) {
    double expected = 1;

    double actual = aRectangle->MaxX();

    EXPECT_EQ(expected, actual);
}

TEST_F(RectangleTest, MaxYTest) {
    double expected = 1;

    double actual = aRectangle->MaxY();

    EXPECT_EQ(expected, actual);
}

TEST_F(RectangleTest, WidthTest) {
    double expected = 2;

    double actual = aRectangle->Width();

    EXPECT_EQ(expected, actual);
}

TEST_F(RectangleTest, HeightTest) {
    double expected = 2;

    double actual = aRectangle->Height();

    EXPECT_EQ(expected, actual);
}

