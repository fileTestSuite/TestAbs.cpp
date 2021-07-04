cpack_add_component(Backend_CppUTest
	DISPLAY_NAME "CppUTest backend library"
	DESCRIPTION "Implements a wrapper for CppUTest"
)

add_library(TestAbsBackend_CppUTest "${CMAKE_CURRENT_SOURCE_DIR}/CppUTest.cpp")
target_link_libraries(TestAbsBackend_CppUTest PUBLIC libTestAbs PRIVATE ${CPPUTEST_LIBRARIES})
target_include_directories(TestAbsBackend_CppUTest PRIVATE "${Include_dir}" PUBLIC "${CPPUTEST_INCLUDEDIR}")
harden(TestAbsBackend_CppUTest)

set_target_properties(TestAbsBackend_CppUTest PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_CppUTest"
	LIBRARY
	COMPONENT "Backend_CppUTest"
)
set("CPACK_DEBIAN_BACKEND_CPPUTEST_PACKAGE_NAME" "libTestAbs-backend-CppUTest")
set("CPACK_RPM_BACKEND_CPPUTEST_PACKAGE_NAME" "libTestAbs-backend-CppUTest")

list(APPEND CPACK_COMPONENTS_ALL "Backend_CppUTest")  # strangely, not populated automatically correctly

# all the libs are static, needed only at compile time
#set("CPACK_DEBIAN_BACKEND_CPPUTEST_PACKAGE_DEPENDS" "CppUTest")
#set("CPACK_RPM_BACKEND_CPPUTEST_PACKAGE_DEPENDS" "CppUTest")

pass_through_cpack_vars()


