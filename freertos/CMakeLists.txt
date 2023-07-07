if (TARGET tinyusb_device)
add_executable(freertos_test
        ./src/main.c
        )
add_subdirectory(kernel)
# pull in common dependencies
include_directories(kernel/custom)
include_directories(kernel/include)
include_directories(kernel/portable/GCC/ARM_CM0)
target_link_libraries(freertos_test pico_stdlib hardware_adc pico_multicore)
target_link_libraries(freertos_test freertos_multi_core_lib)


pico_enable_stdio_usb(freertos_test 1)
pico_enable_stdio_uart(freertos_test 0)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(freertos_test)

# add url via pico_set_program_url
example_auto_set_url(freertos_test)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building hello_usb because TinyUSB submodule is not initialized in the SDK")
endif()