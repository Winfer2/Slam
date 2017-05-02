project(ba_demo)
cmake_minimum_required(VERSION 2.8)
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall --verbose")
FIND_PACKAGE(Eigen3 REQUIRED)
FIND_PACKAGE(CSparse REQUIRED)
FIND_PACKAGE(SuiteSparse)
FIND_PACKAGE(Cholmod REQUIRED)
FIND_PACKAGE(G2O REQUIRED)
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${EIGEN_INCLUDE_DIRS}
  ${CSPARSE_INCLUDE_DIR}
  ${SUITESPARSE_INCLUDE_DIRS}
  ${Cholmod_INCLUDE_DIR}
  ${G2O_INCLUDE_DIR}
  /usr/include/suitesparse
  /usr/include/eigen3
)
LIST(APPEND G2O_LIBS
  cxsparse
  cholmod
  g2o_cli g2o_ext_freeglut_minimal g2o_simulator
  g2o_solver_slam2d_linear g2o_types_icp g2o_types_slam2d
  g2o_core g2o_interface g2o_solver_csparse g2o_solver_structure_only
  g2o_types_sba g2o_types_slam3d g2o_csparse_extension
  g2o_opengl_helper g2o_solver_dense g2o_stuff
  g2o_types_sclam2d g2o_parser g2o_solver_pcg
  g2o_types_data g2o_types_sim3
)
aux_source_directory(. DIR_SRCS)
add_executable(ba_demo ${DIR_SRCS})
target_link_libraries(ba_demo
${G2O_LIBS}
)
