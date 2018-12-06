
find_package (Boost)

include(CheckIncludeFile)
include(CheckIncludeFileCXX)
include(CheckTypeSize)
include(CheckFunctionExists)

check_include_file (strings.h HAVE_STRINGS_H)
check_include_file_cxx ("boost/smart_ptr.hpp" HAVE_SMART_PTR)
check_type_size (uint16_t HAVE_UINT16_T)
check_function_exists(fcntl HAVE_FCNTL)
