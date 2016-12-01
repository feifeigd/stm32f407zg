cmake_minimum_required(VERSION 3.0)

set(CMAKE_SYSTEM_PROCESSOR STM32F407)
set(LOCALAPPDATA "C:/Users/luofei/AppData/Local")
set(BSP_ROOT ${LOCALAPPDATA}/VisualGDB/EmbeddedBSPs/arm-eabi/com.sysprogs.arm.stm32)
set(EFP_BASE ${LOCALAPPDATA}/VisualGDB/EmbeddedEFPs)
set(TESTFW_BASE ${LOCALAPPDATA}/VisualGDB/TestFrameworks)
set(TOOLCHAIN_ROOT d:/SysGCC/arm-eabi)

set(LINK_SCRIPT  ${BSP_ROOT}/STM32F4xxxx/LinkerScripts/STM32F407ZG_flash.lds)

set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mlittle-endian -mfloat-abi=soft -mfpu=fpv4-sp-d16")
SET(CMAKE_C_FLAGS "${MCU_FLAGS} -fno-common -fno-builtin -ffreestanding -Wall ${DEBUG_FLAGS}")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostdlib -mfloat-abi=soft -ffunction-sections -fdata-sections -Wl,-Map,${PROJECT_NAME}.map -Wl,--gc-sections")

SET(CMAKE_CXX_FLAGS "${MCU_FLAGS} -fno-common -fno-builtin -ffreestanding -Wall ${DEBUG_FLAGS}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdlib -mfloat-abi=soft -ffunction-sections -fdata-sections -Wl,-Map,${PROJECT_NAME}.map -Wl,--gc-sections")

SET(CMAKE_EXE_LINKER_FLAGS "${DEBUG_FLAGS} -nostartfiles -T${LINK_SCRIPT}")
add_definitions(-DARM_MATH_CM4 -DSTM32F407ZG -Dstm32_flash_layout -DSTM32F407xx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -DUSE_arm_eabi_gcc_exe)

project(template)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../core
	${CMAKE_CURRENT_SOURCE_DIR}/../fwlib/inc
	${CMAKE_CURRENT_SOURCE_DIR}/../system/delay
	${CMAKE_CURRENT_SOURCE_DIR}/../system/sys
	${CMAKE_CURRENT_SOURCE_DIR}/../system/usart
)

# 相对路径变绝对路径
macro(get_absolute_path target_list)
	set(source_list ${ARGN})
	foreach(f ${source_list})
		get_filename_component(one_file ${f} ABSOLUTE)
		list(APPEND ${target_list} ${one_file})
	endforeach()
endmacro() 

file(GLOB_RECURSE tmp_src ../*.c ../*.cpp ../*.h)
set(src )
get_absolute_path(src ${tmp_src})
file(GLOB_RECURSE filted_src Debug/*.c Debug/*.cpp Debug/*.h Release/*.c Release/*.cpp Release/*.h)

# 过滤生成的文件
foreach(f ${filted_src})
	list(REMOVE_ITEM src ${f})
endforeach()

add_executable(template ${src})
