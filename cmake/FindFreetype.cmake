if(NOT CMAKE_CROSSCOMPILING)
  find_package(PkgConfig QUIET)
  pkg_check_modules(PC_FREETYPE freetype2)
endif()

set_extra_dirs_lib(FREETYPE freetype)
find_library(FREETYPE_LIBRARY
  NAMES freetype freetype.6
  HINTS ${HINTS_FREETYPE_LIBDIR} ${PC_FREETYPE_LIBDIR} ${PC_FREETYPE_LIBRARY_DIRS}
  PATHS ${PATHS_FREETYPE_LIBDIR}
  ${CROSSCOMPILING_NO_CMAKE_SYSTEM_PATH}
)
set_extra_dirs_include(FREETYPE freetype "${FREETYPE_LIBRARY}")
find_path(FREETYPE_INCLUDEDIR
  NAMES config/ftheader.h freetype/config/ftheader.h
  PATH_SUFFIXES freetype2
  HINTS ${HINTS_FREETYPE_INCLUDEDIR} ${PC_FREETYPE_INCLUDEDIR} ${PC_FREETYPE_INCLUDE_DIRS}
  PATHS ${PATHS_FREETYPE_INCLUDEDIR}
  ${CROSSCOMPILING_NO_CMAKE_SYSTEM_PATH}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Freetype DEFAULT_MSG FREETYPE_LIBRARY FREETYPE_INCLUDEDIR)

mark_as_advanced(FREETYPE_LIBRARY FREETYPE_INCLUDEDIR)

set(FREETYPE_LIBRARIES ${FREETYPE_LIBRARY})
set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDEDIR})

is_bundled(IS_BUNDLED "${FREETYPE_LIBRARY}")
if(IS_BUNDLED AND TARGET_OS STREQUAL "windows")
  set(FREETYPE_COPY_FILES "${EXTRA_FREETYPE_LIBDIR}/libfreetype.dll")
else()
  set(FREETYPE_COPY_FILES)
endif()
