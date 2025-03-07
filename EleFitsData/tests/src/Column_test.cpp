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

#include "EleFitsData/Column.h"
#include "EleFitsData/TestColumn.h"

#include <boost/test/unit_test.hpp>

using namespace Euclid::Fits;

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE(Column_test)

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(column_data_can_be_shared_test) {
  std::vector<int> input { 1, 2, 3 };
  PtrColumn<int> column({ "SHARED", "", 1 }, input.size(), input.data());
  BOOST_TEST(column.data()[1] == 2);
  input[1] = 4;
  BOOST_TEST(column.data()[1] == 4);
}

BOOST_AUTO_TEST_CASE(column_data_can_be_moved_test) {
  std::vector<int> input { 4, 5, 6 };
  VecColumn<int> column({ "DATA", "", 1 }, std::move(input));
  BOOST_TEST(column.vector()[1] == 5);
  BOOST_TEST(input.size() == 0);
  column.moveTo(input);
  BOOST_TEST(input[1] == 5);
  BOOST_TEST(column.vector().size() == 0);
  BOOST_TEST(column.elementCount() == 0);
}

BOOST_AUTO_TEST_CASE(subscript_bounds_test) {
  const long rowCount = 10;
  const long repeatCount = 3;
  Test::RandomVectorColumn<int> column(repeatCount, rowCount);
  column.at(1, -1) = 1;
  BOOST_TEST(column.at(1, -1) == 1);
  const auto& vec = column.vector();
  BOOST_TEST(column.at(0) == vec[0]);
  BOOST_TEST(column.at(-1) == vec[(rowCount - 1) * repeatCount]);
  BOOST_TEST(column.at(-rowCount) == vec[0]);
  BOOST_TEST(column.at(0, -1) == vec[repeatCount - 1]);
  BOOST_TEST(column.at(-1, -1) == vec[rowCount * repeatCount - 1]);
  BOOST_CHECK_THROW(column.at(rowCount), FitsError);
  BOOST_CHECK_THROW(column.at(-1 - rowCount), FitsError);
  BOOST_CHECK_THROW(column.at(0, repeatCount), FitsError);
  BOOST_CHECK_THROW(column.at(0, -1 - repeatCount), FitsError);
}

BOOST_AUTO_TEST_CASE(string_column_elementcount_is_rowcount_test) {
  
  constexpr long rowCount = 17;
  constexpr long repeatCount = 7;

  /* VecColumn */
  VecColumn<std::string> vecColumn({ "STR", "", repeatCount }, rowCount);
  BOOST_TEST(vecColumn.info().repeatCount == repeatCount);
  BOOST_TEST(vecColumn.rowCount() == rowCount);
  BOOST_TEST(vecColumn.elementCount() == rowCount);

  /* PtrColumn */
  PtrColumn<std::string> ptrColumn({ "STR", "", repeatCount }, rowCount, vecColumn.data());
  BOOST_TEST(ptrColumn.info().repeatCount == repeatCount);
  BOOST_TEST(ptrColumn.rowCount() == rowCount);
  BOOST_TEST(ptrColumn.elementCount() == rowCount);

  /* Constant VecColumn */
  const VecColumn<std::string> cVecColumn({ "STR", "", repeatCount }, rowCount);
  BOOST_TEST(cVecColumn.info().repeatCount == repeatCount);
  BOOST_TEST(cVecColumn.rowCount() == rowCount);
  BOOST_TEST(cVecColumn.elementCount() == rowCount);

  /* Constant PtrColumn */
  const PtrColumn<const std::string> cPtrColumn({ "STR", "", repeatCount }, rowCount, cVecColumn.data());
  BOOST_TEST(cPtrColumn.info().repeatCount == repeatCount);
  BOOST_TEST(cPtrColumn.rowCount() == rowCount);
  BOOST_TEST(cPtrColumn.elementCount() == rowCount);
}

//-----------------------------------------------------------------------------

BOOST_AUTO_TEST_SUITE_END()
