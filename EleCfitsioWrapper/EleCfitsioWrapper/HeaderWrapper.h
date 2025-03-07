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

#ifndef _ELECFITSIOWRAPPER_HEADERWRAPPER_H
#define _ELECFITSIOWRAPPER_HEADERWRAPPER_H

#include "EleCfitsioWrapper/CfitsioUtils.h"
#include "EleCfitsioWrapper/ErrorWrapper.h"
#include "EleCfitsioWrapper/HduWrapper.h"
#include "EleCfitsioWrapper/TypeWrapper.h"
#include "EleFitsData/KeywordCategory.h"
#include "EleFitsData/Record.h"
#include "EleFitsData/RecordVec.h"

#include <fitsio.h>
#include <string>
#include <tuple>
#include <typeinfo> // type_info
#include <vector>

namespace Euclid {
namespace Cfitsio {

/**
 * @brief Header-related functions.
 */
namespace HeaderIo {

/**
 * @brief Read the whole header as a string.
 * @param fptr A pointer to the fitsfile object.
 * @param incNonValued Include non-valued records (COMMENT, HISTORY, blank).
 */
std::string readHeader(fitsfile* fptr, bool incNonValued = true);

/**
 * @brief List the keywords of selected categories.
 */
std::vector<std::string>
listKeywords(fitsfile* fptr, Fits::KeywordCategory categories = Fits::KeywordCategory::All);

/**
 * @brief List the keywords of selected categories, as well as their values.
 */
std::map<std::string, std::string>
listKeywordsValues(fitsfile* fptr, Fits::KeywordCategory categories = Fits::KeywordCategory::All);

/**
 * @brief Check whether the current HDU contains a given keyword.
 */
bool hasKeyword(fitsfile* fptr, const std::string& keyword);

/**
 * @brief Parse a record.
 */
template <typename T>
Fits::Record<T> parseRecord(fitsfile* fptr, const std::string& keyword);

/**
 * @brief Parse records.
 */
template <typename... Ts>
std::tuple<Fits::Record<Ts>...> parseRecords(fitsfile* fptr, const std::vector<std::string>& keywords);

/**
 * @brief Parse records and store them in a user-defined structure.
 * @tparam TReturn A class which can be brace-initialized with a pack of records or values.
 */
template <class TReturn, typename... Ts>
TReturn parseRecordsAs(fitsfile* fptr, const std::vector<std::string>& keywords);

/**
 * @brief Parse homogeneous records and store them in a vector.
 */
template <typename T>
Fits::RecordVec<T> parseRecordVec(fitsfile* fptr, const std::vector<std::string>& keywords);

/**
 * @brief Write a new record.
 */
template <typename T>
void writeRecord(fitsfile* fptr, const Fits::Record<T>& record);

/**
 * @brief Write new records.
 */
template <typename... Ts>
void writeRecords(fitsfile* fptr, const Fits::Record<Ts>&... records);

/**
 * @brief Write new records.
 */
template <typename... Ts>
void writeRecords(fitsfile* fptr, const std::tuple<Fits::Record<Ts>...>& records);

/**
 * @brief Write homogeneous records.
 */
template <typename T>
void writeRecords(fitsfile* fptr, const std::vector<Fits::Record<T>>& records);

/**
 * @brief Update an existing record or write a new one.
 */
template <typename T>
void updateRecord(fitsfile* fptr, const Fits::Record<T>& record);

/**
 * @brief Update existing records or write new ones.
 */
template <typename... Ts>
void updateRecords(fitsfile* fptr, const Fits::Record<Ts>&... records);

/**
 * @brief Update existing records or write new ones.
 */
template <typename... Ts>
void updateRecords(fitsfile* fptr, const std::tuple<Fits::Record<Ts>...>& records);

/**
 * @brief Update existing homogeneous records or write new ones.
 */
template <typename T>
void updateRecords(fitsfile* fptr, const std::vector<Fits::Record<T>>& records);

/**
 * @brief Delete an existing record.
 */
void deleteRecord(fitsfile* fptr, const std::string& keyword);

/**
 * @brief Get the typeid of a record value.
 */
const std::type_info& recordTypeid(fitsfile* fptr, const std::string& keyword);

/**
 * @brief Write COMMENT record.
 */
void writeComment(fitsfile* fptr, const std::string& comment);

/**
 * @brief Write HISTORY record.
 */
void writeHistory(fitsfile* fptr, const std::string& history);

} // namespace HeaderIo
} // namespace Cfitsio
} // namespace Euclid

/// @cond INTERNAL
#define _ELECFITSIOWRAPPER_HEADERWRAPPER_IMPL
#include "EleCfitsioWrapper/impl/HeaderWrapper.hpp"
#undef _ELECFITSIOWRAPPER_HEADERWRAPPER_IMPL
/// @endcond

#endif
