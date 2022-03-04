add_library(sampler STATIC
  sampler.c
)

target_include_directories(sampler
  PUBLIC .
)

target_compile_definitions(sampler
  PUBLIC -D_POSIX_C_SOURCE=199309L
)

target_link_libraries(sampler
  -lrt
)

set_property(TARGET sampler
  PROPERTY PUBLIC_HEADER sampler.h
)

include(GNUInstallDirs)
install(TARGETS sampler
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/libsampler"
  ARCHIVE
)
