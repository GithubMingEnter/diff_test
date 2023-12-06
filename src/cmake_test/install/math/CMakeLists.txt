#查找当前目录下的所有源文件
#将名称保存到DIR_LIB_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

#指定生成库
add_library(MathFunctions MathFunctions.cc)
install(TARGETS MathFunctions DESTINATION lib)
install(FILES MathFunctions.h DESTINATION include)








