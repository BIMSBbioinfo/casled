MCU = atmega32
F_CPU = 16000000UL

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size
PROG = avrdude -vv
DEVICE="usb:20:67"
PROGRAMMER=avrispmkii
PROGFLAGS = -c $(PROGRAMMER) -p $(MCU) -P $(DEVICE) -e

TARGET = casled
TARGET_OUT = $(TARGET).out
TARGET_HEX = $(TARGET).hex
TARGET_MAP = $(TARGET).map

# configuration
HEXFORMAT = ihex
OPTLEVEL = s

C_SRC = main.c
O_FILES = $(subst .c,.o,$(C_SRC))

CFLAGS = -mmcu=$(MCU) -O$(OPTLEVEL) -fshort-enums \
	-funsigned-bitfields -funsigned-char -Wall -DF_CPU=$(F_CPU)

# main target
all: $(TARGET_OUT)

LDFLAGS = -mmcu=${MCU} -Wl,--gc-sections
# make output
$(TARGET_OUT): $(O_FILES) $(H_SRC)
	$(CC) $(LDFLAGS) -o $@ $(O_FILES) && \
	$(SIZE) $(TARGET_OUT)

# make binary image
$(TARGET_HEX): $(TARGET_OUT)
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# objects from C files
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# program target
program: $(TARGET_HEX)
	$(PROG) $(PROGFLAGS) -U flash:w:$(TARGET_HEX)


clean:
	rm -f $(TARGET_HEX) $(TARGET_OUT) $(O_FILES)
