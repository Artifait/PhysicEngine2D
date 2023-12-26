#pragma once

#include <StructData/v2f.h>
#include <StructData/TransformPhis2D.h>
#include <StructData/v2fRect.h>


#include <boost/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/register/box.hpp>
#include <boost/geometry/index/rtree.hpp>


namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
BOOST_GEOMETRY_REGISTER_POINT_2D(v2f, float, cs::cartesian, x, y)
BOOST_GEOMETRY_REGISTER_BOX(v2fRect, v2f, GetMinCorner(), GetMaxCorner())