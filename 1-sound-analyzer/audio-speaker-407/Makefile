CC=arm-none-eabi-gcc
MACH=cortex-m4

# CONFIGURE FILENAME:
FILENAME = audo-speaker

# File and directory variables
SRC = ./
COMPILATION_FILES = ../../407-Comp-Files/
DRIVER_FILES = ../../Drivers/
FREERTOS_SRC = FreeRTOS-Kernel/tasks.c \
               FreeRTOS-Kernel/queue.c \
               FreeRTOS-Kernel/list.c \
               FreeRTOS-Kernel/timers.c \
               FreeRTOS-Kernel/event_groups.c \
               FreeRTOS-Kernel/stream_buffer.c \
               FreeRTOS-Kernel/croutine.c \
               FreeRTOS-Kernel/portable/MemMang/heap_4.c \
               FreeRTOS-Kernel/portable/GCC/ARM_CM4F/port.c 
MY_INCLUDES = -I$(SRC)includes \
			  -I$(COMPILATION_FILES) \
			  -I$(DRIVER_FILES) \
			  -IFreeRTOS-Kernel/include \
              -IFreeRTOS-Kernel/portable/GCC/ARM_CM4F/ \
			  

# Sources and Objects
SRCS=$(FREERTOS_SRC) $(wildcard $(SRC)*.c) $(wildcard $(COMPILATION_FILES)*.c) $(DRIVER_FILES)DAC.c \
	 $(DRIVER_FILES)CAN.c $(DRIVER_FILES)GPIO.c
OBJS = $(SRCS:.c=.o) # Object files to link

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -g $(MY_INCLUDES) -std=gnu11 -Wall 
LDFLAGS= -mcpu=$(MACH) -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard --specs=nano.specs -T $(COMPILATION_FILES)stm32f407_ls.ld -Wl,-Map=final.map
LDLIBS= -lm # For math library functionality

# Targets
all: $(OBJS) $(FILENAME).elf

# Pattern Rule
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link objects into .elf file
$(FILENAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	$(RM) $(OBJS) *.elf *.map

# "make all" then "load"
load: all
	openocd -f board/stm32f4discovery.cfg