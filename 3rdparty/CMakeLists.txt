cmake_minimum_required(VERSION 3.13)



###############################################################################
## 3RD-PARTY
## dependencies for the project
###############################################################################
project(3rdparty LANGUAGES CXX)



###############################################################################
## SETTINGS
## basic 3rd-party settings before use
###############################################################################
# To inherit the top-level architecture when the project is used as a submodule.
SET(PARENT ${PARENT}_CONFIG_READER_3RDPARTY_)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE OFF CACHE BOOL "" FORCE)



###############################################################################
## CONFIGURATION
## 3rd-party submodules configuration
##############################################################################
SET(${PARENT}_JSON_SUBMODULE                        ON CACHE BOOL "" FORCE)



###############################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the 3rd-party configuration
###############################################################################
if (${PARENT}_JSON_SUBMODULE)
    add_subdirectory(Json)
endif()
