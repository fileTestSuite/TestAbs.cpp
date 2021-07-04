cpack_add_component(Backend_GTest
	DISPLAY_NAME "Google Test backend library"
	DESCRIPTION "Implements a wrapper for Google Test"
)

add_library(TestAbsBackend_GTest "${CMAKE_CURRENT_SOURCE_DIR}/GoogleTest.cpp")
target_link_libraries(TestAbsBackend_GTest PUBLIC TestAbs PRIVATE GTest::gtest)
target_include_directories(TestAbsBackend_GTest PRIVATE "${Include_dir}")
target_compile_definitions(TestAbsBackend_GTest PRIVATE "-DTESTABS_BACKEND_EXPORTS")
harden(TestAbsBackend_GTest)

set_target_properties(TestAbsBackend_GTest PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_GTest"
	LIBRARY
	COMPONENT "Backend_GTest"
)
set("CPACK_DEBIAN_BACKEND_GTEST_PACKAGE_NAME" "libTestAbs-backend-googletest")
set("CPACK_RPM_BACKEND_GTEST_PACKAGE_NAME" "libTestAbs-backend-googletest")

list(APPEND CPACK_COMPONENTS_ALL "Backend_GTest")  # strangely, not populated automatically correctly

set("CPACK_DEBIAN_BACKEND_GTEST_PACKAGE_DEPENDS" "googletest")
set("CPACK_RPM_BACKEND_GTEST_PACKAGE_DEPENDS" "googletest")

pass_through_cpack_vars()


