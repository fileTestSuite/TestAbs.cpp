find_package("DyLib")
find_package("function-loader")

find_package(HydrArgs REQUIRED)
find_package(HydrArgs_backend_cxxopts REQUIRED)

file(GLOB SRCFILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

message(STATUS "SRCFILES ${SRCFILES}")
add_executable(testabs-runner "${SRCFILES}")
target_include_directories(testabs-runner PRIVATE "${Include_dir}")
target_link_libraries(testabs-runner PRIVATE dl "${LIB_FILE_NAME}" burda::function-loader HydrArgs::HydrArgs HydrArgs_backend_cxxopts::HydrArgs_backend_cxxopts)

set_target_properties(testabs-runner PROPERTIES
	CXX_STANDARD 20
)



harden(testabs-runner)

cpack_add_component(runner
	DISPLAY_NAME "Runner"
	DESCRIPTION "The testabs-runner combining the backebnd implementing TestAbs spec and user's shared library, implementing testing"
	REQUIRED
)

install(TARGETS "testabs-runner"
	RUNTIME
	COMPONENT "runner"
)
set("CPACK_DEBIAN_RUNNER_PACKAGE_NAME" "TestAbs-runner")
set("CPACK_RPM_RUNNER_PACKAGE_NAME" "TestAbs-runner")

list(APPEND CPACK_COMPONENTS_ALL "runner")  # strangely, not populated automatically correctly


pass_through_cpack_vars()
