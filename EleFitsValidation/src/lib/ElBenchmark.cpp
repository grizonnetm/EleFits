/**
 * @copyright (C) 2012-2020 Euclid Science Ground Segment
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation; either version 3.0 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "EleFitsValidation/ElBenchmark.h"

namespace Euclid {
namespace Fits {
namespace Test {

ElColwiseBenchmark::ElColwiseBenchmark(const std::string& filename) :
    Benchmark(filename), m_f(filename, FileMode::Overwrite) {
  m_logger.info() << "EleFits benchmark (column-wise, filename: " << filename << ")";
}

void ElColwiseBenchmark::open() {
  m_f.reopen();
}

void ElColwiseBenchmark::close() {
  m_f.close();
}

BChronometer::Unit ElColwiseBenchmark::writeBintable(const BColumns& columns) {
  m_chrono.start();
  const auto& ext = m_f.initBintableExt(
      "",
      std::get<0>(columns).info(),
      std::get<1>(columns).info(),
      std::get<2>(columns).info(),
      std::get<3>(columns).info(),
      std::get<4>(columns).info(),
      std::get<5>(columns).info(),
      std::get<6>(columns).info(),
      std::get<7>(columns).info(),
      std::get<8>(columns).info(),
      std::get<9>(columns).info());
  ext.writeColumn(std::get<0>(columns));
  ext.writeColumn(std::get<1>(columns));
  ext.writeColumn(std::get<2>(columns));
  ext.writeColumn(std::get<3>(columns));
  ext.writeColumn(std::get<4>(columns));
  ext.writeColumn(std::get<5>(columns));
  ext.writeColumn(std::get<6>(columns));
  ext.writeColumn(std::get<7>(columns));
  ext.writeColumn(std::get<8>(columns));
  ext.writeColumn(std::get<9>(columns));
  return m_chrono.stop();
}

BColumns ElColwiseBenchmark::readBintable(long index) {
  m_chrono.start();
  const auto& ext = m_f.access<BintableHdu>(index);
  const auto columns = std::make_tuple(
      ext.readColumn<std::tuple_element<0, BColumns>::type::Value>(0),
      ext.readColumn<std::tuple_element<1, BColumns>::type::Value>(1),
      ext.readColumn<std::tuple_element<2, BColumns>::type::Value>(2),
      ext.readColumn<std::tuple_element<3, BColumns>::type::Value>(3),
      ext.readColumn<std::tuple_element<4, BColumns>::type::Value>(4),
      ext.readColumn<std::tuple_element<5, BColumns>::type::Value>(5),
      ext.readColumn<std::tuple_element<6, BColumns>::type::Value>(6),
      ext.readColumn<std::tuple_element<7, BColumns>::type::Value>(7),
      ext.readColumn<std::tuple_element<8, BColumns>::type::Value>(8),
      ext.readColumn<std::tuple_element<9, BColumns>::type::Value>(9));
  m_chrono.stop();
  return columns;
}

ElBenchmark::ElBenchmark(const std::string& filename) : ElColwiseBenchmark(filename) {
  m_logger.info() << "EleFits benchmark (buffered, filename: " << filename << ")";
}

BChronometer::Unit ElBenchmark::writeImage(const BRaster& raster) {
  m_chrono.start();
  m_f.assignImageExt("", raster);
  return m_chrono.stop();
}

BChronometer::Unit ElBenchmark::writeBintable(const BColumns& columns) {
  m_chrono.start();
  m_f.assignBintableExt("", columns);
  return m_chrono.stop();
}

BRaster ElBenchmark::readImage(long index) {
  m_chrono.start();
  const auto raster = m_f.access<ImageHdu>(index).readRaster<BRaster::Value, BRaster::Dim>();
  m_chrono.stop();
  return raster;
}

BColumns ElBenchmark::readBintable(long index) {
  m_chrono.start();
  const auto columns = m_f.access<BintableHdu>(index).columns().readSeq(
      colIndexed<0>(),
      colIndexed<1>(),
      colIndexed<2>(),
      colIndexed<3>(),
      colIndexed<4>(),
      colIndexed<5>(),
      colIndexed<6>(),
      colIndexed<7>(),
      colIndexed<8>(),
      colIndexed<9>());
  m_chrono.stop();
  return columns;
}

} // namespace Test
} // namespace Fits
} // namespace Euclid
