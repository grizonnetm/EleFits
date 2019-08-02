/**
 * @file src/lib/BintableWrapper.cpp
 * @date 07/27/19
 * @author user
 *
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

#include <algorithm>

#include "EL_CFitsIOWrapper/BintableWrapper.h"
#include "EL_CFitsIOWrapper/CfitsioUtils.h"

namespace Cfitsio {
namespace Bintable {

std::size_t column_index(fitsfile* fptr, std::string name) {
	int index;
	int status = 0;
	fits_get_colnum(fptr, CASESEN, to_char_ptr(name), &index, &status);
	may_throw_cfitsio_error(status);
	return index;
}

std::vector<std::string> internal::ColumnDispatcher<std::string>::read(fitsfile* fptr, std::string name) {
	auto ptr_data = ColumnDispatcher<char*>::read(fptr, name);
	const auto rows = ptr_data.size();
	std::vector<std::string> data(rows);
	for(std::size_t i=0; i<rows; ++i) {
		char* ptr_i = ptr_data[i];
		data[i] = std::string(ptr_i);
		delete[] ptr_data[i]; //TODO keep?
	}
	return data;
}

void internal::ColumnDispatcher<std::string>::write(fitsfile* fptr, const Column<std::string>& column) {
	const auto rows = column.data.size();
	Column<char*> char_ptr_column { column.name, column.width, column.unit, std::vector<char*>(rows) };
	for(std::size_t i=0; i<rows; ++i)
		char_ptr_column.data[i] = to_char_ptr(column.data[i]);
	internal::ColumnDispatcher<char*>::write(fptr, char_ptr_column);
}

}
}

