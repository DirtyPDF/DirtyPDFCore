file(GLOB src_SOURCES "*.cpp")
file(GLOB src_HEADERS "${HEADERS_DIR}/*.hpp")

qt5_wrap_cpp(src_HEADERS_MOC ${src_HEADERS})

include_directories(${HEADERS_DIR})

add_library(dirtyPDFCore STATIC ${src_SOURCES} ${src_HEADERS_MOC})
qt5_use_modules(dirtyPDFCore Core Gui)
