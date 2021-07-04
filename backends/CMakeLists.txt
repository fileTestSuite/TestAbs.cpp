
find_package(GTest)
if(GTEST_FOUND)
	option(WITH_GoogleTest ON)
	if(WITH_GoogleTest)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/GoogleTest")
	endif()
endif()

find_package(Catch2)
if(Catch2_FOUND)
	option(WITH_Catch2 ON)
	if(WITH_Catch2)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Catch2")
	endif()
endif()
# component is not allowed for includes!  Headers are installed separately!

pkg_check_modules(IGLOO igloo)
if(IGLOO_FOUND)
	option(WITH_Igloo ON)
	if(WITH_Igloo)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Igloo")
	endif()
endif()

find_package(Boost COMPONENTS unit_test_framework)
if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
	option(WITH_BoostTest ON)
	if(WITH_BoostTest)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/BoostTest")
	endif()
	# Boost.Test https://www.boost.org/doc/libs/1_76_0/libs/test/doc/html/index.html
endif()

pkg_check_modules(UNITTESTPP UnitTest++)
if(UNITTESTPP_FOUND)
	option(WITH_UnitTestPlusPlus ON)
	if(WITH_UnitTestPlusPlus)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/UnitTest++") # unittest++ https://github.com/unittest-cpp/unittest-cpp/wiki
	endif()
endif()

pkg_check_modules(CPPTEST libcpptest)
if(CPPTEST_FOUND)
	option(WITH_CPPTest ON)
	if(WITH_CPPTest)
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CPPTest")
		# cpptest https://github.com/cpptest/cpptest
	endif()
endif()

#find_package(CppUTest)  # broken
pkg_check_modules(CPPUTEST cpputest)  # works
if(CPPUTEST_FOUND)
	option(WITH_CppUTest OFF)
	if(WITH_CppUTest)
		# cpputest https://github.com/cpputest/cpputest
		message(FATAL "cpputest is broken ,relocation R_X86_64_PC32 against symbol `_ZN12SimpleString16stringAllocator_E' can not be used when making a shared object; recompile with -fPIC")
		add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CppUTest")
	endif()
endif()

pass_through_cpack_vars()
