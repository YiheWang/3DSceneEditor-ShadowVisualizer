
if (NOT EXISTS "C:/Users/Yihe Wang/OneDrive/Local/learning resources/NYU/2019 Fall Semes/CS 6533 Interactive Computer Graphics/Final Project/FinalProject/cmake-build-debug/glfw/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: \"C:/Users/Yihe Wang/OneDrive/Local/learning resources/NYU/2019 Fall Semes/CS 6533 Interactive Computer Graphics/Final Project/FinalProject/cmake-build-debug/glfw/install_manifest.txt\"")
endif()

file(READ "C:/Users/Yihe Wang/OneDrive/Local/learning resources/NYU/2019 Fall Semes/CS 6533 Interactive Computer Graphics/Final Project/FinalProject/cmake-build-debug/glfw/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")

foreach (file ${files})
  message(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  if (EXISTS "$ENV{DESTDIR}${file}")
    exec_program("C:/Program Files/JetBrains/CLion 2019.2.4/bin/cmake/win/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    endif()
  elseif (IS_SYMLINK "$ENV{DESTDIR}${file}")
    EXEC_PROGRAM("C:/Program Files/JetBrains/CLion 2019.2.4/bin/cmake/win/bin/cmake.exe" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
                 OUTPUT_VARIABLE rm_out
                 RETURN_VALUE rm_retval)
    if (NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing symlink \"$ENV{DESTDIR}${file}\"")
    endif()
  else()
    message(STATUS "File \"$ENV{DESTDIR}${file}\" does not exist.")
  endif()
endforeach()

