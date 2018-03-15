# Find the Darknet libraries
#
# The following variables are optionally searched for defaults
#  Darknet_ROOT_DIR:    Base directory where all Darknet components are found
#
# The following are set after configuration is done:
#  Darknet_FOUND
#  Darknet_INCLUDE_DIR
#  Darknet_LIBRARIES

find_path(Darknet_INCLUDE_DIR NAMES darknet.h
            PATHS
            ${Darknet_ROOT_DIR}
            ${Darknet_ROOT_DIR}/include
            /usr/local/include/darknet
)

find_library(Darknet_LIBRARIES NAMES darknet
                              PATHS ${Darknet_ROOT_DIR} ${Darknet_ROOT_DIR}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Darknet DEFAULT_MSG Darknet_INCLUDE_DIR Darknet_LIBRARIES)

if(DARKNET_FOUND)
  message(STATUS "Found Darknet  (include: ${Darknet_INCLUDE_DIR}, library: ${Darknet_LIBRARIES})")
  mark_as_advanced(Darknet_INCLUDE_DIR Darknet_LIBRARIES)

endif()
