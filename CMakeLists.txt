include(CheckIncludeFiles)

set( lib_name ekfvloc )
set( libVersion 1.0.0 )
GBX_ADD_LICENSE( LGPL2+ )

set( build TRUE )

GBX_REQUIRE_OPTION( build LIB ${lib_name} ON )

CHECK_INCLUDE_FILES( gsl/gsl_version.h have_gsl )

GBX_REQUIRE_VAR( build LIB ${lib_name} have_gsl "libgsl not found" )
# set ( libs "gsl" ) # -lgsl -lgslcblas

if( build )

    include( ${GBX_CMAKE_DIR}/UseBasicRules.cmake )

    file( GLOB hdrs *.hh)
    file( GLOB srcs *.cc )

    GBX_ADD_LIBRARY( ${lib_name} DEFAULT ${libVersion} ${srcs} )
    GBX_ADD_HEADERS( ${lib_name} ${hdrs} )
    # TARGET_LINK_LIBRARIES( ${lib_name} ${libs} )

endif( build )