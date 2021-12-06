#include "Eigen/Core"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../../src/core/material/material_constant.hpp"
#include "../../src/core/material/material.hpp"

using ::testing::Return;

class MockMaterialConstant : public MaterialConstant {
 public:
  MOCK_METHOD(double, Value, (), (const, override));
};

TEST(DMatrixTest, PlaneStress) {
    MockMaterialConstant e;
    EXPECT_CALL(e, Value())
        .WillOnce(Return(1));

    MockMaterialConstant nu;
    EXPECT_CALL(nu, Value())
        .WillOnce(Return(0));

    Material material = Material(e, nu);

    Eigen::MatrixXd actual = material.DMatrix(ProblemType::PlaneStress);
    Eigen::MatrixXd expected(3, 3);
    expected << 1, 0, 0,
             0, 1, 0,
             0, 0, 0.5;

    EXPECT_TRUE(actual.isApprox(expected));
}

TEST(DMatrixTest, PlaneStrain) {
    MockMaterialConstant e;
    EXPECT_CALL(e, Value())
        .WillOnce(Return(1));

    MockMaterialConstant nu;
    EXPECT_CALL(nu, Value())
        .WillOnce(Return(0));

    Material material = Material(e, nu);

    Eigen::MatrixXd actual = material.DMatrix(ProblemType::PlaneStrain);
    Eigen::MatrixXd expected(3, 3);
    expected << 1, 0, 0,
             0, 1, 0,
             0, 0, 0.5;

    EXPECT_TRUE(actual.isApprox(expected));
}

/*
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
*/

