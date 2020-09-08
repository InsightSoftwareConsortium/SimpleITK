
add_executable ( SubDimensionProcess SubDimensionProcess.cxx )
target_link_libraries ( SubDimensionProcess ${SimpleITK_LIBRARIES} )

if(NOT BUILD_TESTING)
  return()
endif()

sitk_add_test(NAME CXX.Example.SubDimensionProcess
      COMMAND
      $<TARGET_FILE:SubDimensionProcess>
        DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.SubDimensionProcess.nrrd"
      IMAGE_COMPARE
        "${SimpleITK_TEST_OUTPUT_DIR}/CXX.Example.SubDimensionProcess.nrrd"
        DATA{${SimpleITK_DATA_ROOT}/Baseline/SubDimensionProcess.mha}
        0.01
      )


sitk_add_python_test( Example.SubDimensionProcess
        "${CMAKE_CURRENT_SOURCE_DIR}/SubDimensionProcess.py"
        DATA{${SimpleITK_DATA_ROOT}/Input/OAS1_0001_MR1_mpr-1_anon.nrrd}
        "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.SubDimensionProcess.nrrd"
      IMAGE_COMPARE
        "${SimpleITK_TEST_OUTPUT_DIR}/Python.Example.SubDimensionProcess.nrrd"
        DATA{${SimpleITK_DATA_ROOT}/Baseline/SubDimensionProcess.mha}
      )
