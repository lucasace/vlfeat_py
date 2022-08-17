if(NOT VLFEAT_FOUND)
    FetchContent_Declare(
      vlfeat
      URL https://www.vlfeat.org/download/vlfeat-0.9.21-bin.tar.gz
    )
    FetchContent_MakeAvailable(vlfeat)

    set(VLFEAT_ROOT ${vlfeat_SOURCE_DIR})
    find_package(vlFeat)
endif()