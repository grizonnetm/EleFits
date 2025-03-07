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

#include "EleCfitsioWrapper/FileWrapper.h"

#include "EleCfitsioWrapper/ErrorWrapper.h"
#include "EleCfitsioWrapper/HduWrapper.h"

namespace Euclid {
namespace Cfitsio {
namespace FileAccess {

fitsfile* createAndOpen(const std::string& filename, CreatePolicy policy) {
  std::string cfitsioName = filename;
  if (policy == CreatePolicy::OverWrite) {
    cfitsioName.insert(0, 1, '!'); // CFitsIO convention
  }
  fitsfile* fptr;
  int status = 0;
  fits_create_file(&fptr, cfitsioName.c_str(), &status);
  CfitsioError::mayThrow(status, fptr, "Cannot create file: " + filename);
  HduAccess::initPrimary(fptr);
  return fptr;
}

fitsfile* open(const std::string& filename, OpenPolicy policy) {
  fitsfile* fptr;
  int status = 0;
  int permission = READONLY;
  if (policy == OpenPolicy::ReadWrite) {
    permission = READWRITE;
  }
  fits_open_file(&fptr, filename.c_str(), permission, &status);
  CfitsioError::mayThrow(status, fptr, "Cannot open file: " + filename);
  return fptr;
}

void close(fitsfile*& fptr) {
  if (not fptr) {
    return;
  }
  int status = 0;
  fits_close_file(fptr, &status);
  CfitsioError::mayThrow(status, fptr, "Cannot close file");
  fptr = nullptr;
}

void closeAndDelete(fitsfile*& fptr) {
  if (not fptr) {
    return;
  }
  mayThrowReadonlyError(fptr);
  int status = 0;
  fits_delete_file(fptr, &status);
  CfitsioError::mayThrow(status, fptr, "Cannot close and delete file");
  fptr = nullptr;
}

std::string name(fitsfile* fptr) {
  int status = 0;
  char filename[FLEN_FILENAME];
  fits_file_name(fptr, filename, &status);
  CfitsioError::mayThrow(status, fptr, "Filename not found");
  return filename;
}

bool isWritable(fitsfile* fptr) {
  int status = 0;
  int filemode;
  fits_file_mode(fptr, &filemode, &status);
  return filemode == READWRITE;
}

} // namespace FileAccess
} // namespace Cfitsio
} // namespace Euclid
