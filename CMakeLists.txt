cmake_minimum_required(VERSION 2.6)

find_file (HAVE_GSL gsl_version.h /usr/include /usr/include/gsl)

if (NOT HAVE_GSL)
    PLAYERDRIVER_OPTION (nxt build_nxt OFF "libusb-1.0 not found (package libusb-1.0-0-dev in debian)")
elseif(NOT HAVE_STL)
	PLAYERDRIVER_OPTION (ekfvloc build_ekfvloc OFF "STL not found")
else()
    PLAYERDRIVER_OPTION (ekfvloc build_ekfvloc ON)
endif ()

PLAYERDRIVER_REQUIRE_OS(ekfvloc build_ekfvloc UNIX)
PLAYERDRIVER_ADD_DRIVER(
    ekfvloc build_ekfvloc
    
    SOURCES
    ekfvloc_driver.cc
    feature.cc
    hregions.cc
    localize.cc
    params.cc
    robot_location.cc
    scan.cc
    segment_map.cc
    sub_opt.cc
    transf.cc
    uloc.cc

    CFLAGS
    -Wall
    -pedantic
    -g

    LINKFLAGS
    -lgsl -lgslcblas
    )
