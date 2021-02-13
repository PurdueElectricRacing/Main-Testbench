project(CAN_Example)
cmake_minimum_required(VERSION 3.10)

include_directories("../inc")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_definitions(-DUNICODE)

if (WIN32)
  add_definitions(-DWINDOWS)
  include_directories("../candle")

  add_executable( can_example main_win.cpp 
    "../src/canframe.cpp" 
    "../candle/candle_ctrl_req.c"
    "../candle/candle.c"
    "../candle/gs_usb.c"
    "../candle/gsusb.c"
    "../candle/WinCan.cpp"
  ) 
  
  target_link_libraries( can_example
    SetupApi
	  winusb
	  Ole32
  )

else()
  include_directories("../socketcan")
  add_executable(can_example main_sc.cpp 
                 "../src/canframe.cpp" 
                 "../socketcan/socketcan_if.cpp")
endif()

