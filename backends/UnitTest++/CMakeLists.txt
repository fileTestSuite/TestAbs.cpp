cpack_add_component(Backend_UnitTestPlusPlus
	DISPLAY_NAME "UnitTestPlusPlus backend library"
	DESCRIPTION "Implements a wrapper for UnitTestPlusPlus"
)

add_library(TestAbsBackend_UnitTestPlusPlus "${CMAKE_CURRENT_SOURCE_DIR}/UnitTest++.cpp")
target_link_libraries(TestAbsBackend_UnitTestPlusPlus PUBLIC TestAbs PRIVATE ${UNITTESTPP_LIBRARIES})
target_include_directories(TestAbsBackend_UnitTestPlusPlus PRIVATE "${Include_dir}" PUBLIC "${UNITTESTPP_INCLUDEDIR}")
harden(TestAbsBackend_UnitTestPlusPlus)

set_target_properties(TestAbsBackend_UnitTestPlusPlus PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_UnitTestPlusPlus"
	LIBRARY
	COMPONENT "Backend_UnitTestPlusPlus"
)
set("CPACK_DEBIAN_BACKEND_UNITTESTPLUSPLUS_PACKAGE_NAME" "libTestAbs-backend-UnitTestPlusPlus")
set("CPACK_RPM_BACKEND_UNITTESTPLUSPLUS_PACKAGE_NAME" "libTestAbs-backend-UnitTestPlusPlus")

list(APPEND CPACK_COMPONENTS_ALL "Backend_UnitTestPlusPlus")  # strangely, not populated automatically correctly

set("CPACK_DEBIAN_BACKEND_UNITTESTPLUSPLUS_PACKAGE_DEPENDS" "libunittest++2")
set("CPACK_RPM_BACKEND_UNITTESTPLUSPLUS_PACKAGE_DEPENDS" "unittest-cpp")

pass_through_cpack_vars()


