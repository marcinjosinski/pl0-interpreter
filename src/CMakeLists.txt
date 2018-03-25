add_executable(pl0 main.cxx)

set_target_properties(pl0
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

install(TARGETS pl0 RUNTIME DESTINATION bin)
