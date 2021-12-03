#include "../../src/element/triangle_element_2d.hpp"
#include "../../src/node/node.hpp"
#include "../../src/node/node_2d.hpp"
#include "Eigen/Core"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <iostream>
#include <memory>

using ::testing::Pointee;
using ::testing::Return;

class MockNode : public Node {
  public:
    MOCK_METHOD(double, X, (), (const, override));
    MOCK_METHOD(double, Y, (), (const, override));
    MOCK_METHOD(double, Z, (), (const, override));
    MOCK_METHOD(int, Index, (), (const, override));
};

class OrdinaryNodes : public ::testing::Test {
  protected:
    virtual void SetUp() {
        std::shared_ptr<MockNode> n1(new MockNode());
        std::shared_ptr<MockNode> n2(new MockNode());
        std::shared_ptr<MockNode> n3(new MockNode());

        EXPECT_CALL(*n1, X())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n1, Y())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n1, Z())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n1, Index())
            .WillRepeatedly(Return(1));

        EXPECT_CALL(*n2, X())
            .WillRepeatedly(Return(1));
        EXPECT_CALL(*n2, Y())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n2, Z())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n2, Index())
            .WillRepeatedly(Return(2));

        EXPECT_CALL(*n3, X())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n3, Y())
            .WillRepeatedly(Return(1));
        EXPECT_CALL(*n3, Z())
            .WillRepeatedly(Return(0));
        EXPECT_CALL(*n3, Index())
            .WillRepeatedly(Return(3));

        anElement = std::make_unique<TriangleElement2D>(n1, n2, n3);
    }

    std::unique_ptr<TriangleElement2D> anElement;
};

TEST_F(OrdinaryNodes, BMatrixTest) {
    Eigen::MatrixXd expected(3, 6);

    expected << -1, 0, 1, 0, 0, 0,
        0, -1, 0, 0, 0, 1,
        -1, -1, 0, 1, 1, 0;

    Eigen::MatrixXd actual = anElement->BMatrix();

    EXPECT_TRUE(expected.isApprox(actual));
}

TEST_F(OrdinaryNodes, AreaTest) {
    double expected = 0.5;

    double actual = anElement->Area();

    EXPECT_EQ(expected, actual);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
