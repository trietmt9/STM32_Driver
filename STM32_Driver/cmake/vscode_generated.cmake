# This is converter generated file, and shall not be touched by user
#
# Use CMakeLists.txt to apply user changes
cmake_minimum_required(VERSION 3.22)

# Core MCU flags, CPU, instruction set and FPU setup
set(cpu_PARAMS ${cpu_PARAMS}
    -mthumb

    # Other parameters
    # -mcpu, -mfloat, -mfloat-abi, ...
    -mcpu=cortex-m4
	-mfpu=fpv4-sp-d16
	-mfloat-abi=hard
	
)

# Linker script
set(linker_script_SRC ${linker_script_SRC}
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32f446retx_FLASH.ld
)

# Sources
set(sources_SRCS ${sources_SRCS}
    
	${CMAKE_CURRENT_SOURCE_DIR}/Src/main.c
	${CMAKE_CURRENT_SOURCE_DIR}/Startup/startup_stm32f446retx.s
	${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/stm32f446xx_gpio_driver.c
	${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/stm32f446xx_spi_driver.c
)

# Include directories
set(include_c_DIRS ${include_c_DIRS}
    
	${CMAKE_CURRENT_SOURCE_DIR}/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/Driver/Inc
)
set(include_cxx_DIRS ${include_cxx_DIRS}
    
)
set(include_asm_DIRS ${include_asm_DIRS}
    
)

# Compiler options (adding -O0)
set(compiler_OPTS ${compiler_OPTS} 
	-O0
	-ffast-math     # Enable fast math optimizations
    -fsingle-precision-constant # Treat floating-point constants as float
    -fno-math-errno # Disable error handling for math functions
	)

# Symbols definition
set(symbols_c_SYMB ${symbols_c_SYMB}

)
set(symbols_cxx_SYMB ${symbols_cxx_SYMB}
    
)
set(symbols_asm_SYMB ${symbols_asm_SYMB}
    
)

# Link directories
set(link_DIRS ${link_DIRS}
    
)

# Link libraries
set(link_LIBS ${link_LIBS}
    
)

# Compiler options
set(compiler_OPTS ${compiler_OPTS})

# Linker options
set(linker_OPTS ${linker_OPTS}
	-lm # Link the math library
	)
