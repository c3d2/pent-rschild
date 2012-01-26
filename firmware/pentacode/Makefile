PROJECT=tuerschild

MCU = atmega328p
MCU_AVRDUDE = atmega328p


FUSE_SETTINGS = -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xfe:m


ifeq ($(OSTYPE),)
OSTYPE      = $(shell uname)
endif
ifneq ($(findstring Darwin,$(OSTYPE)),)
USB_DEVICE = /dev/cu.SLAB_USBtoUART
else
USB_DEVICE = /dev/ttyUSB0
endif


#########################################################################

SRC=$(wildcard *.c apps/*.c)
OBJECTS=$(SRC:.c=.o) 
DFILES=$(SRC:.c=.d) 
HEADERS=$(wildcard *.h)



#  Compiler Options
GCFLAGS = -mmcu=$(MCU) -I. -gstabs -DF_CPU=20000000 -O2 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -Wall -Wstrict-prototypes  -std=gnu99 -MD -MP
LDFLAGS = -mmcu=$(MCU)  

#  Compiler Paths
GCC = avr-gcc
REMOVE = rm -f
SIZE = avr-size
OBJCOPY = avr-objcopy

#########################################################################

all: $(PROJECT).hex Makefile stats

$(PROJECT).hex: $(PROJECT).elf Makefile
	$(OBJCOPY) -R .eeprom -O ihex $(PROJECT).elf $(PROJECT).hex 

$(PROJECT).elf: $(OBJECTS) Makefile
	$(GCC) $(LDFLAGS) $(OBJECTS) -o $(PROJECT).elf

stats: $(PROJECT).elf Makefile
	$(SIZE) $(PROJECT).elf

clean:
	$(REMOVE) $(OBJECTS)
	$(REMOVE) $(PROJECT).hex
	$(REMOVE) $(DFILES)
	$(REMOVE) $(PROJECT).elf

#########################################################################

%.o: %.c Makefile $(HEADERS)
	$(GCC) $(GCFLAGS) -o $@ -c $<

#########################################################################

flash: all
	avrdude -F -p $(MCU_AVRDUDE) -P $(USB_DEVICE) -c stk500v2    -U flash:w:$(PROJECT).hex

fuse:
	avrdude -F -p $(MCU_AVRDUDE) -P $(USB_DEVICE) -c stk500v2    $(FUSE_SETTINGS)

