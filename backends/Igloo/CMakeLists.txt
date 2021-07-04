cpack_add_component(Backend_Igloo
	DISPLAY_NAME "Igloo backend library"
	DESCRIPTION "Implements a wrapper for Igloo"
)

add_library(TestAbsBackend_Igloo "${CMAKE_CURRENT_SOURCE_DIR}/Igloo.cpp")
target_link_libraries(TestAbsBackend_Igloo PUBLIC TestAbs PRIVATE "${IGLOO_LIBRARIES}")
target_include_directories(TestAbsBackend_Igloo PRIVATE "${Include_dir}" PUBLIC "${IGLOO_INCLUDEDIR}")
harden(TestAbsBackend_Igloo)

set_target_properties(TestAbsBackend_Igloo PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_Igloo"
	LIBRARY
	COMPONENT "Backend_Igloo"
)
set("CPACK_DEBIAN_BACKEND_IGLOO_PACKAGE_NAME" "libTestAbs-backend-Igloo")
set("CPACK_RPM_BACKEND_IGLOO_PACKAGE_NAME" "libTestAbs-backend-Igloo")

list(APPEND CPACK_COMPONENTS_ALL "Backend_Igloo")  # strangely, not populated automatically correctly

set("CPACK_DEBIAN_BACKEND_IGLOO_PACKAGE_DEPENDS" "libigloo0")
#set("CPACK_RPM_BACKEND_IGLOO_PACKAGE_DEPENDS" "Igloo")

pass_through_cpack_vars()


