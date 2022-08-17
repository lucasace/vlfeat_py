include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)
find_path(VLFEAT_INCLUDE_DIR
          NAMES vl
          PATHS ${VLFEAT_ROOT}
          DOC "VLFEAT include directory")
find_library(VLFEAT_LIBRARY_RELEASE
             NAMES vl
             PATHS ${VLFEAT_ROOT}/bin/glnxa64
             DOC "VLFEAT library file (release version)")
find_library(VLFEAT_LIBRARY_DEBUG
             NAMES vld 
             PATHS ${VLFEAT_ROOT}/bin/glnxa64
             DOC "VLFEAT library file (debug version)") 

if(VLFEAT_INCLUDE_DIR AND (VLFEAT_LIBRARY_RELEASE OR VLFEAT_LIBRARY_DEBUG))
  set(VLFEAT_FOUND TRUE)
else()
  set(VLFEAT_FOUND FALSE)
  return()
endif()

select_library_configurations(VLFEAT)
set(VLFEAT_LIBRARIES ${VLFEAT_LIBRARY})
set(VLFEAT_INCLUDE_DIRS ${VLFEAT_INCLUDE_DIR})

mark_as_advanced(VLFEAT_LIBRARIES VLFEAT_INCLUDE_DIRS)

