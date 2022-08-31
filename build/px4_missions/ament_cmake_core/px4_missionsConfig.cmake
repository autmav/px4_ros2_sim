# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_px4_missions_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED px4_missions_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(px4_missions_FOUND FALSE)
  elseif(NOT px4_missions_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(px4_missions_FOUND FALSE)
  endif()
  return()
endif()
set(_px4_missions_CONFIG_INCLUDED TRUE)

# output package information
if(NOT px4_missions_FIND_QUIETLY)
  message(STATUS "Found px4_missions: 0.0.0 (${px4_missions_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'px4_missions' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${px4_missions_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(px4_missions_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${px4_missions_DIR}/${_extra}")
endforeach()
