#include "../../src/core/material/material.hpp"
#include "../../src/core/material/material_constant.hpp"
#include "../../src/core/material/plane_strain_material.hpp"
#include "../../src/core/material/plane_stress_material.hpp"
#include "Eigen/Core"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

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

    std::shared_ptr<Material> material = std::make_shared<PlaneStressMaterial>(e, nu);

    Eigen::MatrixXd actual = material->DMatrix();
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

    std::shared_ptr<Material> material = std::make_shared<PlaneStrainMaterial>(e, nu);

    Eigen::MatrixXd actual = material->DMatrix();
    Eigen::MatrixXd expected(3, 3);
    expected << 1, 0, 0,
        0, 1, 0,
        0, 0, 0.5;

    EXPECT_TRUE(actual.isApprox(expected));
}
