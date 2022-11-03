cmake_minimum_required (VERSION 3.0)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)
# output directories
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# specify cross compilers and tools
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
#set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_AS arm-none-eabi-as)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(SIZE arm-none-eabi-size)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# project settings
project (bare-metal-arm C ASM)
set(NAME bare-metal-arm)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

set(LINKSCRIPT "${CMAKE_SOURCE_DIR}/src/linkscript.ld")
set(ASMFILES
        src/startup.S)
set(SRCLIST
        src/cstart.c)


add_executable(${NAME}.elf
        ${CMAKE_SOURCE_DIR}/src/cstart.c
        ${CMAKE_SOURCE_DIR}/src/startup.S )

#add_custom_command(
 #       TARGET ${NAME}.elf POST_BUILD
 #       COMMAND ${CMAKE_OBJCOPY} ./${NAME}.elf${CMAKE_EXECUTABLE_SUFFIX} -O binary ./${NAME}.img
 #       COMMAND ${CMAKE_OBJDUMP} -l -S -D ./${NAME}${CMAKE_EXECUTABLE_SUFFIX} > ./${NAME}.asm
 #       WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
 #       COMMENT "Convert the ELF output file to a binary image" )



#add_executable(bare-metal ${SRCLIST} ${ASMFILES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKSCRIPT}")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles -nostdlib -g -Wall")


#add_custom_command(TARGET ${NAME}.elf POST_BUILD COMMAND ${CMAKE_OBJCOPY} -O binary ${NAME}.elf ${NAME}.bin COMMENT "Converting ELF to binary")
