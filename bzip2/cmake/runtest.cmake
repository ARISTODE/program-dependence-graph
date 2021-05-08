get_filename_component (_TEMP "${IN}" NAME_WE)

set (_TEMP_OUT ${_TEMP}.rb2)

execute_process (
  COMMAND ${EXECUTABLE} ${ARGS}
  INPUT_FILE ${IN}
  OUTPUT_FILE ${_TEMP_OUT}
)

execute_process (COMMAND ${COMPARE} ${_TEMP_OUT} ${OUT} RESULT_VARIABLE _RESULT)

if (EXISTS ${_TEMP_OUT})
    file (REMOVE ${_TEMP_OUT})
endif (EXISTS ${_TEMP_OUT})

if (NOT _RESULT EQUAL 0)
  message (SEND_ERROR "Comparison failed")
endif (NOT _RESULT EQUAL 0)
