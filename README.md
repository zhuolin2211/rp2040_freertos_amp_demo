# rp2040_freertos_smp_demo
移植freerrtos到RP2040平台，支持SMP

编译
复制 freertos文件夹到sdk的pico-examples文件夹下，编辑pico-examples/CMakeLists.txt 
追加 add_subdirectory(freertos)
编译并下载，dem会运行三个任务，LED闪烁任务，温度传感器输出任务，测试任务。查看USB虚拟串口，输出消息（测试发现XCOM无法收到数据，使用mobaxterm可以，应该是picoSDK的bug）。