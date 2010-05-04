IF (HAVE_STL)
	PLAYERDRIVER_OPTION (ekfvloc build_ekfvloc ON)
ELSE (HAVE_STL)
	PLAYERDRIVER_OPTION (ekfvloc build_ekfvloc OFF "STL not found")
ENDIF (HAVE_STL)

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
