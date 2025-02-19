CC=arm-none-eabi-gcc
MACH=cortex-m4

# CONFIGURE FILENAME:
FILENAME = filename

# File and directory variables
SRC = ./
COMPILATION_FILES = inc/comp_files/
LOW_LEVEL_FILES = inc/low_level/
LOGIC_FILES = inc/logic/
MY_INCLUDES = -I $(COMPILATION_FILES) -I $(LOW_LEVEL_FILES) -I $(LOGIC_FILES)

# Sources and objects
SRCS=$(wildcard *.c)
L=$(wildcard $(LOGIC_FILES)*.c)
C=$(wildcard $(COMPILATION_FILES)*.c)
LL=$(wildcard $(LOW_LEVEL_FILES)*.c)

# $(patsubst pattern, replacement, list)
# patsubst: replaces "pattern" with "repacement" for each "pattern" file in the specified "list".
SRC_OBJS=$(patsubst %.c, %.o, $(SRCS))
L_OBJS=$(patsubst %.c, %.o, $(L))
LL_OBJS=$(patsubst %.c, %.o, $(LL))
C_OBJS=$(patsubst %.c, %.o, $(C))
OBJS = $(SRC_OBJS) $(L_OBJS) $(LL_OBJS) $(C_OBJS) # Object files to link

# Compiler and linker flags
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -g $(MY_INCLUDES) -std=gnu11 -Wall 
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(COMPILATION_FILES)stm32f407_ls.ld -Wl,-Map=final.map

# Targets
all: $(OBJS) $(FILENAME).elf

# Pattern Rule: Tells Make how to compile .c files into .o object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link the object files & create the final binary
$(FILENAME).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	$(RM) *.o $(COMPILATION_FILES)*.o $(LOW_LEVEL_FILES)*.o $(LOGIC_FILES)*.o *.elf *.map

# Calls "make all" before loading
load: all
	openocd -f board/stm32f4discovery.cfg

