cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_USE_RELATIVE_PATHS TRUE)
project("TestAbs")
set("PROJECT_DESCRIPTION" "An abstraction layer around C++ testing frameworks")
set("PROJECT_HOMEPAGE_URL" "https://github.com/fileTestSuite/${PROJECT_NAME}.cpp")

set(CPACK_PACKAGE_VENDOR "KOLANICH")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")


set(OUR_CMAKE_MODULES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(OUR_CMAKE_3PARTY_MODULES_DIR "${OUR_CMAKE_MODULES_DIR}/thirdParty")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OUR_CMAKE_MODULES_DIR}" "${OUR_CMAKE_MODULES_DIR}/Boilerplate" "${OUR_CMAKE_MODULES_DIR}/DoxygenUtils" "${OUR_CMAKE_3PARTY_MODULES_DIR}")

include(CPackComponent)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(Boilerplate)

find_package(PkgConfig)

set(LIB_FILE_NAME "${PROJECT_NAME}")

set(Include_dir "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(Include_sub_dir_name "TestAbs")
set(Include_sub_dir "${Include_dir}/${Include_sub_dir_name}")
file(GLOB_RECURSE HDRFILES "${Include_sub_dir}/*.h" "${Include_sub_dir}/*.hpp")

set(LibSource_dir "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BinSource_dir "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(Backends_dir "${CMAKE_CURRENT_SOURCE_DIR}/backends")
set(PackagingTemplatesDir "${CMAKE_CURRENT_SOURCE_DIR}/packaging")



set(CPACK_DEBIAN_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")
set(CPACK_RPM_PACKAGE_NAME "${CPACK_PACKAGE_NAME}")

add_subdirectory("${LibSource_dir}")
add_subdirectory("${Backends_dir}")
add_subdirectory("${BinSource_dir}")


set(CPACK_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_MAINTAINER}")
set(CPACK_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR}")
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_RPM_COMPONENT_INSTALL ON)
set(CPACK_NSIS_COMPONENT_INSTALL ON)
#set(CPACK_DEBIAN_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_RPM_ENABLE_COMPONENT_DEPENDS ON)
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")

include(CPack)
