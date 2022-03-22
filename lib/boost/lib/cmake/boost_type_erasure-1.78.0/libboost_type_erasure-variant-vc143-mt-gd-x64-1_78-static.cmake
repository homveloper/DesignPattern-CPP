# Generated by Boost 1.78.0

# address-model=64

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
  _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "64 bit, need 32")
  return()
endif()

# layout=versioned

# toolset=vc143

if(Boost_COMPILER)
  if(NOT Boost_COMPILER STREQUAL "vc143" AND NOT Boost_COMPILER STREQUAL "-vc143")
    _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "vc143, Boost_COMPILER=${Boost_COMPILER}")
    return()
  endif()
else()
  if(BOOST_DETECTED_TOOLSET AND NOT BOOST_DETECTED_TOOLSET STREQUAL "vc143")
    _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "vc143, detected ${BOOST_DETECTED_TOOLSET}, set Boost_COMPILER to override")
    return()
  endif()
endif()

# link=static

if(DEFINED Boost_USE_STATIC_LIBS)
  if(NOT Boost_USE_STATIC_LIBS)
    _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "static, Boost_USE_STATIC_LIBS=${Boost_USE_STATIC_LIBS}")
    return()
  endif()
else()
  if(NOT WIN32 AND NOT _BOOST_SINGLE_VARIANT)
    _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "static, default is shared, set Boost_USE_STATIC_LIBS=ON to override")
    return()
  endif()
endif()

# runtime-link=shared

if(Boost_USE_STATIC_RUNTIME)
  _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "shared runtime, Boost_USE_STATIC_RUNTIME=${Boost_USE_STATIC_RUNTIME}")
  return()
endif()

# runtime-debugging=on

if(NOT "${Boost_USE_DEBUG_RUNTIME}" STREQUAL "" AND NOT Boost_USE_DEBUG_RUNTIME)
  _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "debug runtime, Boost_USE_DEBUG_RUNTIME=${Boost_USE_DEBUG_RUNTIME}")
  return()
endif()

# threading=multi

if(DEFINED Boost_USE_MULTITHREADED AND NOT Boost_USE_MULTITHREADED)
  _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "multithreaded, Boost_USE_MULTITHREADED=${Boost_USE_MULTITHREADED}")
  return()
endif()

# variant=debug

if(NOT "${Boost_USE_DEBUG_LIBS}" STREQUAL "" AND NOT Boost_USE_DEBUG_LIBS)
  _BOOST_SKIPPED("libboost_type_erasure-vc143-mt-gd-x64-1_78.lib" "debug, Boost_USE_DEBUG_LIBS=${Boost_USE_DEBUG_LIBS}")
  return()
endif()

if(Boost_VERBOSE OR Boost_DEBUG)
  message(STATUS "  [x] libboost_type_erasure-vc143-mt-gd-x64-1_78.lib")
endif()

# Create imported target Boost::type_erasure

if(NOT TARGET Boost::type_erasure)
  add_library(Boost::type_erasure STATIC IMPORTED)

  set_target_properties(Boost::type_erasure PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${_BOOST_INCLUDEDIR}"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_TYPE_ERASURE_NO_LIB"
  )
endif()

# Target file name: libboost_type_erasure-vc143-mt-gd-x64-1_78.lib

get_target_property(__boost_imploc Boost::type_erasure IMPORTED_LOCATION_DEBUG)
if(__boost_imploc)
  message(SEND_ERROR "Target Boost::type_erasure already has an imported location '${__boost_imploc}', which is being overwritten with '${_BOOST_LIBDIR}/libboost_type_erasure-vc143-mt-gd-x64-1_78.lib'")
endif()
unset(__boost_imploc)

set_property(TARGET Boost::type_erasure APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)

set_target_properties(Boost::type_erasure PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG CXX
  IMPORTED_LOCATION_DEBUG "${_BOOST_LIBDIR}/libboost_type_erasure-vc143-mt-gd-x64-1_78.lib"
  )

list(APPEND _BOOST_TYPE_ERASURE_DEPS chrono system thread headers)
