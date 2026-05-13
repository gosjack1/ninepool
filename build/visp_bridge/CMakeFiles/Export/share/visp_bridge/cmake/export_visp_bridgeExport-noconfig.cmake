#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "visp_bridge::visp_bridge" for configuration ""
set_property(TARGET visp_bridge::visp_bridge APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(visp_bridge::visp_bridge PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_NOCONFIG "rcpputils::rcpputils"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libvisp_bridge.so"
  IMPORTED_SONAME_NOCONFIG "libvisp_bridge.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS visp_bridge::visp_bridge )
list(APPEND _IMPORT_CHECK_FILES_FOR_visp_bridge::visp_bridge "${_IMPORT_PREFIX}/lib/libvisp_bridge.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
