CC=arm-none-eabi-gcc
MACH=cortex-m4
FILENAME = filename

SRCS=$(wildcard *.c)
SRC_OBJS=$(patsubst $(SRC)%.c, $(SRC)%.o, $(SRCS))

# RTOS Files
#RTOS=$(wildcard $(RTOS_FILES)*.c)
#RTOS_OBJS=$(patsubst $(RTOS_FILES)%.c, $(RTOS_FILES)%.o, $(RTOS))

#PORT=$(wildcard $(PORT_FILES)*.c)
#PORT_OBJS=$(patsubst $(PORT_FILES)%.c, $(PORT_FILES)%.o, $(PORT))

#HEAP=$(wildcard $(HEAP_FILES)*.c)
#HEAP_OBJS=$(patsubst $(HEAP_FILES)%.c, $(HEAP_FILES)%.o, $(HEAP))

#INC=$(wildcard $(INC_FILES)*.c)
#INC_OBJS=$(patsubst $(INC_FILES)%.c, $(INC_FILES)%.o, $(INC))

# My Includes
L=$(wildcard $(LOGIC_FILES)*.c)
L_OBJS=$(patsubst $(LOGIC_FILES)%.c, $(LOGIC_FILES)%.o, $(L))

C=$(wildcard $(COMPILATION_FILES)*.c)
C_OBJS=$(patsubst $(COMPILATION_FILES)%.c, $(COMPILATION_FILES)%.o, $(C))

LL=$(wildcard $(LOW_LEVEL_FILES)*.c)
LL_OBJS=$(patsubst $(LOW_LEVEL_FILES)%.c, $(LOW_LEVEL_FILES)%.o, $(LL))

OBJS = $(SRC_OBJS) $(L_OBJS) $(LL_OBJS) $(C_OBJS) 
#$(RTOS_OBJS) $(PORT_OBJS) $(HEAP_OBJS) $(INC_OBJS)

SRC = ./
RTOS_FILES = FreeRTOS/
INC_HEADERS = FreeRTOS/include/
PORT_FILES = FreeRTOS/portable/GCC/ARM_CM4F/
HEAP_FILE = FreeRTOS/portable/MemMang/
COMPILATION_FILES = inc/comp_files/
LOW_LEVEL_FILES = inc/low_level/
LOGIC_FILES = inc/logic/
MY_INCLUDES = -I$(COMPILATION_FILES) -I$(LOW_LEVEL_FILES) -I$(LOGIC_FILES)
ALL_INCLUDES = -I$(INC_HEADERS) -I$(PORT_FILES) -I$(HEAP_FILE) -I$(RTOS_FILES) -I$(MY_INCLUDES)

RTOS_KERNEL_L1 = $(RTOS_FILES)croutine.o $(RTOS_FILES)event_groups.o $(RTOS_FILES)list.o
RTOS_KERNEL_L2 = $(RTOS_FILES)queue.o $(RTOS_FILES)stream_buffer.o $(RTOS_FILES)tasks.o $(RTOS_FILES)systemclock.o 
RTOS_KERNEL_L3 = $(RTOS_FILES)timers.o $(PORT_FILES)port.o $(HEAP_FILE)heap_4.o 
RTOS_KERNEL_LINKS = $(RTOS_KERNEL_L1) $(RTOS_KERNEL_L2) $(RTOS_KERNEL_L3)

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -g -std=gnu11 -Wall $(ALL_INCLUDES)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nano.specs -T $(COMPILATION_FILES)stm32f407_ls.ld -Wl,-Map=final.map

all: $(FILENAME).elf
	
#$(FILENAME).elf: $(FILENAME).o $(OBJS) $(RTOS_KERNEL_LINKS)
#	$(CC) $(LDFLAGS) $^ -o $@
	
%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@
	
%.o: $(RTOS_FILES)%.c
	$(CC) $(CFLAGS) $^ -o $@
	
%.o: $(PORT_FILES)%.c
	$(CC) $(CFLAGS) $^ -o $@
	
%.o: $(HEAP_FILE)%.c
	$(CC) $(CFLAGS) $^ -o $@

$(FILENAME).elf: $(FILENAME).o $(COMPILATION_FILES)startup.o $(COMPILATION_FILES)syscalls.o $(RTOS_KERNEL_LINKS) $(LL_OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf *.map $(RTOS_FILES)*.o $(PORT_FILES)*.o $(HEAP_FILE)*.o $(COMPILATION_FILES)*.o $(LOW_LEVEL_FILES)*.o  $(LOGIC_FILES)*.o

load:
	openocd -f board/stm32f4discovery.cfg
