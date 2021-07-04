cpack_add_component(Backend_CPPTest
	DISPLAY_NAME "CPPTest backend library"
	DESCRIPTION "Implements a wrapper for CPPTest"
)

add_library(TestAbsBackend_CPPTest "${CMAKE_CURRENT_SOURCE_DIR}/CPPTest.cpp")
target_link_libraries(TestAbsBackend_CPPTest PUBLIC TestAbs PRIVATE "${CPPTEST_LIBRARIES}")
target_include_directories(TestAbsBackend_CPPTest PRIVATE "${Include_dir}" PUBLIC "${CPPTEST_INCLUDEDIR}")
target_compile_definitions(TestAbsBackend_CPPTest PRIVATE "-DTESTABS_BACKEND_EXPORTS")
harden(TestAbsBackend_CPPTest)

set_target_properties(TestAbsBackend_CPPTest PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_CPPTest"
	LIBRARY
	COMPONENT "Backend_CPPTest"
)
set("CPACK_DEBIAN_BACKEND_CPPTEST_PACKAGE_NAME" "libTestAbs-backend-CPPTest")
set("CPACK_RPM_BACKEND_CPPTEST_PACKAGE_NAME" "libTestAbs-backend-CPPTest")

list(APPEND CPACK_COMPONENTS_ALL "Backend_CPPTest")  # strangely, not populated automatically correctly

set("CPACK_DEBIAN_BACKEND_CPPTEST_PACKAGE_DEPENDS" "libcpptest1")
set("CPACK_RPM_BACKEND_CPPTEST_PACKAGE_DEPENDS" "cpptest")

pass_through_cpack_vars()


