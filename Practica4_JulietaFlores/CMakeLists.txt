cmake_minimum_required(VERSION 3.13)

# Raspberry Pi Pico SDK import
include(pico_sdk_import.cmake)


# Project definition
project(practica4 C CXX ASM)

# SDK initialization
pico_sdk_init()

# Add the executable with ALL the pieces
add_executable(practica4
    main.c             # Entry point
    kernel_drivers.c   # Hardware access
    kernel_service.c   # Dispatcher and task exit
    scheduler.c        # task_create() and schedule()
    svc_handler.s      # Assembly wrapper for interrupts
    pendsv.s           # Assembly context switch

    user_app.c         # Your added tasks
    syscalls.s         # System calls interface
)

# Enable USB serial output
pico_enable_stdio_usb(practica4 1)
pico_enable_stdio_uart(practica4 0)


# Link libraries
target_link_libraries(practica4
    pico_stdlib
    hardware_exception
)

# Generate artifacts (.uf2)
pico_add_extra_outputs(practica4)
