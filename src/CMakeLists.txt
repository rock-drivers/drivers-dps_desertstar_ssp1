rock_library(dps_desertstar-ssp1
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(dps_desertstar-ssp1_bin Main.cpp
    DEPS dps_desertstar-ssp1)

