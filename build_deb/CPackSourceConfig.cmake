# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "1")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_IFW "OFF")
SET(CPACK_BINARY_NSIS "OFF")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_RPM "0")
SET(CPACK_BINARY_STGZ "OFF")
SET(CPACK_BINARY_STGZ "OFF")
SET(CPACK_BINARY_TBZ2 "OFF")
SET(CPACK_BINARY_TGZ "OFF")
SET(CPACK_BINARY_TGZ "OFF")
SET(CPACK_BINARY_TXZ "OFF")
SET(CPACK_BINARY_TZ "OFF")
SET(CPACK_BINARY_TZ "OFF")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "libraries;headers;applications;tools")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_APPLICATIONS_DESCRIPTION "C/C++ opc ua application server")
SET(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "C++ OPC UA Applications Server")
SET(CPACK_COMPONENT_APPLICATIONS_GROUP "bin")
SET(CPACK_COMPONENT_HEADERS_DESCRIPTION "C/C++ header files used to build opc ua applications")
SET(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ OPC UA Stack Headers")
SET(CPACK_COMPONENT_HEADERS_GROUP "dev")
SET(CPACK_COMPONENT_LIBRARIES_DESCRIPTION "Shared libraries used to build opc ua applications")
SET(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "C++ OPC UA Stack Libraries")
SET(CPACK_COMPONENT_LIBRARIES_GROUP "bin")
SET(CPACK_COMPONENT_TOOLS_DESCRIPTION "C/C++ development tools")
SET(CPACK_COMPONENT_TOOLS_DISPLAY_NAME "OPC UA Stack Tools")
SET(CPACK_COMPONENT_TOOLS_GROUP "dev")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_BIN_PACKAGE_DEPENDS "libboost-system1.54.0, libboost-filesystem1.54.0, libboost-thread1.54.0, libboost-date-time1.54.0, libboost-chrono1.54.0, libboost-regex1.54.0")
SET(CPACK_DEBIAN_DEV_PACKAGE_DEPENDS "libboost-system1.54-dev, libboost-test1.54-dev, libboost-filesystem1.54-dev, libboost-thread1.54-dev, libboost-date-time1.54-dev, libboost-chrono1.54-dev, libboost-regex1.54-dev, OpcUaStack-2-bin (=2.0.1)")
SET(CPACK_DEB_COMPONENT_INSTALL "ON")
SET(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_INSTALLED_DIRECTORIES "/home/huebl/devel_/OpcUaStack/src;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "")
SET(CPACK_NSIS_DISPLAY_NAME "OpcUaStack-2 2.0.1")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "OpcUaStack-2 2.0.1")
SET(CPACK_OUTPUT_CONFIG_FILE "/home/huebl/devel_/OpcUaStack/build_deb/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "info@asneg.de")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/local/share/cmake-3.4/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OpcUaStack - Opc Ua client server application framework")
SET(CPACK_PACKAGE_FILE_NAME "OpcUaStack-2-2.0.1-Source")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "OpcUaStack-2 2.0.1")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "OpcUaStack-2 2.0.1")
SET(CPACK_PACKAGE_NAME "OpcUaStack-2")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "asneg.de")
SET(CPACK_PACKAGE_VERSION "2.0.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "2")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_RESOURCE_FILE_LICENSE "/home/huebl/devel_/OpcUaStack/src/Copyright.txt")
SET(CPACK_RESOURCE_FILE_README "/usr/local/share/cmake-3.4/Templates/CPack.GenericDescription.txt")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/local/share/cmake-3.4/Templates/CPack.GenericWelcome.txt")
SET(CPACK_RPM_PACKAGE_LICENSE "/home/huebl/devel_/OpcUaStack/src/Copyright.txt")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "/home/huebl/devel_/OpcUaStack/src;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/home/huebl/devel_/OpcUaStack/build_deb/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "OpcUaStack-2-2.0.1-Source")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/home/huebl/devel_/OpcUaStack/build_deb/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
