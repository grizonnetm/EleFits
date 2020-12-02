# - Locate EL_FitsFile library
# Defines:
#
#  EL_FITSFILE_FOUND
#  EL_FITSFILE_INCLUDE_DIR
#  EL_FITSFILE_INCLUDE_DIRS (not cached)
#  EL_FITSFILE_LIBRARY
#  EL_FITSFILE_LIBRARIES (not cached)

if(NOT EL_FITSFILE_FOUND)

  find_path(EL_FITSFILE_INCLUDE_DIR EL_FITSFILE/EL_FitsFile/MefFile.h
            HINTS ENV EL_FITSFILE_ROOT_DIR EL_FITSFILE_INSTALL_DIR
            PATH_SUFFIXES include)

  find_library(EL_FITSFILE_LIBRARY EL_FitsFile
               HINTS ENV EL_FITSFILE_ROOT_DIR EL_FITSFILE_INSTALL_DIR
               PATH_SUFFIXES lib)

  set(EL_FITSFILE_LIBRARIES ${EL_FITSFILE_LIBRARY})
  set(EL_FITSFILE_INCLUDE_DIRS ${EL_FITSFILE_INCLUDE_DIR})

  INCLUDE(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(EL_FITSFILE DEFAULT_MSG EL_FITSFILE_INCLUDE_DIRS EL_FITSFILE_LIBRARIES)

  mark_as_advanced(EL_FITSFILE_FOUND EL_FITSFILE_INCLUDE_DIRS EL_FITSFILE_LIBRARIES)

  list(REMOVE_DUPLICATES EL_FITSFILE_LIBRARIES)
  list(REMOVE_DUPLICATES EL_FITSFILE_INCLUDE_DIRS)

endif()
