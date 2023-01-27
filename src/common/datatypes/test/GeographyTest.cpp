/* Copyright (c) 2020 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#include <gtest/gtest.h>
#include <s2/util/coding/coder.h>

#include "common/base/Base.h"
#include "common/datatypes/Geography.h"

namespace nebula {

TEST(Geography, shape) {
  {
    nebula::String wkt = "POINT(3 7)";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    EXPECT_EQ(GeoShape::POINT, g.shape());
  }
  {
    nebula::String wkt = "LINESTRING(28.4 79.20, 134.25 -28.34)";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    EXPECT_EQ(GeoShape::LINESTRING, g.shape());
  }
  {
    nebula::String wkt = "POLYGON((1 2, 3 4, 5 6, 1 2))";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    EXPECT_EQ(GeoShape::POLYGON, g.shape());
  }
}

TEST(Geography, asWKT) {
  {
    nebula::String wkt = "POINT(3 7)";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    nebula::String got = g.asWKT();
    EXPECT_EQ(wkt, got);
  }
  {
    nebula::String wkt = "LINESTRING(28.4 79.2, 134.25 -28.34)";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    nebula::String got = g.asWKT();
    EXPECT_EQ(wkt, got);
  }
  {
    nebula::String wkt = "POLYGON((1 2, 3 4, 5 6, 1 2))";
    auto gRet = Geography::fromWKT(wkt);
    ASSERT_TRUE(gRet.ok());
    auto g = gRet.value();
    nebula::String got = g.asWKT();
    EXPECT_EQ(wkt, got);
  }
}

}  // namespace nebula

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  folly::init(&argc, &argv, true);
  google::SetStderrLogging(google::INFO);

  return RUN_ALL_TESTS();
}
