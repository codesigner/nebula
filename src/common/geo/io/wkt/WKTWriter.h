/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License.
 */

#ifndef COMMON_GEO_IO_WKT_WKTWRITER_H
#define COMMON_GEO_IO_WKT_WKTWRITER_H

#include "common/base/Base.h"
#include "common/datatypes/Geography.h"

namespace nebula {
namespace geo {

class WKTWriter {
 public:
  WKTWriter() {}

  ~WKTWriter() {}

  nebula::String write(const Geography& geog) const;

  void writeCoordinate(nebula::String& wkt, const Coordinate& coord) const;

  void writeCoordinateList(nebula::String& wkt, const std::vector<Coordinate>& coordList) const;

  void writeCoordinateListList(nebula::String& wkt,
                               const std::vector<std::vector<Coordinate>>& coordListList) const;

  void writeDouble(nebula::String& wkt, double v) const;
};

}  // namespace geo
}  // namespace nebula
#endif
