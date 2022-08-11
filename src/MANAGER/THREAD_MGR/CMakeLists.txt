# Author: Mohd Ramza <mohdramza@yahoo.com>
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
project(project_info)
set(TARGET_SCOPE app PRIVATE)

target_include_directories(${TARGET_SCOPE} includes)

set(SOURCES src/thread_manager.c
)

target_sources(app PRIVATE ${SOURCES})