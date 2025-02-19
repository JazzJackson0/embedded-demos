CC=arm-none-eabi-gcc
MACH=cortex-m4

#CONFIGURE FILENAME:
FILENAME = filename

#If Using: Add to FILE_LINKS 
LOW_LEVEL = $(LOW_LEVEL_FILES)file1.o $(LOW_LEVEL_FILES)file2.o 
#If Using: Add to FILE_LINKS 
LOGIC = $(LOGIC_FILES)file1.o $(LOGIC_FILES)file2.o 
#If Using: Add to FILE_LINKS 
COMPILATION = $(COMPILATION_FILES)startup.o $(COMPILATION_FILES)syscalls.o

FILE_LINKS = $(COMPILATION) $(LOW_LEVEL_FILES) $() 

COMPILATION_FILES = inc/comp_files/
LOW_LEVEL_FILES = inc/low_level/
LOGIC_FILES = inc/logic/
MY_INCLUDES = -I$(COMPILATION_FILES) -I$(LOW_LEVEL_FILES) -I$(LOGIC_FILES)

CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -g -std=gnu11 -Wall $(MY_INCLUDES)
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft --specs=nano.specs -T $(COMPILATION_FILES)stm32f407_ls.ld -Wl,-Map=final.map

all: $(FILENAME).o final.elf

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@

final.elf: $(FILENAME).o $(FILE_LINKS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf *.map

load:
	openocd -f board/stm32f4discovery.cfg
