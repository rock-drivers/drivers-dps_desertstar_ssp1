rock_library(dps_desertstar_ssp1
    SOURCES Driver.cpp
    HEADERS Driver.hpp
    DEPS_PKGCONFIG base-lib iodrivers_base 
    )

rock_executable(dps_desertstar_ssp1_bin Main.cpp
    DEPS dps_desertstar_ssp1)

