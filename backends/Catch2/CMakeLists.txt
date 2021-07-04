cpack_add_component(Backend_Catch2
	DISPLAY_NAME "Catch2 backend library"
	DESCRIPTION "Implements a wrapper for Catch2"
)

add_library(TestAbsBackend_Catch2 "${CMAKE_CURRENT_SOURCE_DIR}/Catch2.cpp")
target_link_libraries(TestAbsBackend_Catch2 PUBLIC TestAbs PRIVATE Catch2::Catch2)
target_include_directories(TestAbsBackend_Catch2 PRIVATE "${Include_dir}")
target_compile_definitions(TestAbsBackend_Catch2 PRIVATE "-DTESTABS_BACKEND_EXPORTS")
harden(TestAbsBackend_Catch2)

set_target_properties(TestAbsBackend_Catch2 PROPERTIES
	SOVERSION "${CPACK_PACKAGE_VERSION}"
)

install(TARGETS "TestAbsBackend_Catch2"
	LIBRARY
	COMPONENT "Backend_Catch2"
)
set("CPACK_DEBIAN_BACKEND_CATCH2_PACKAGE_NAME" "libTestAbs-backend-catch2")
set("CPACK_RPM_BACKEND_CATCH2_PACKAGE_NAME" "libTestAbs-backend-catch2")

list(APPEND CPACK_COMPONENTS_ALL "Backend_Catch2")  # strangely, not populated automatically correctly

set("CPACK_DEBIAN_BACKEND_CATCH2_PACKAGE_DEPENDS" "catch2")
set("CPACK_RPM_BACKEND_CATCH2_PACKAGE_DEPENDS" "catch2")

pass_through_cpack_vars()


