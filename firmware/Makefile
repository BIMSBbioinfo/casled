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
H_SRC = progs.h
O_FILES = $(subst .c,.o,$(C_SRC))

CFLAGS = -g -mmcu=$(MCU) -O$(OPTLEVEL)  \
	-ffunction-sections -fdata-sections \
	-Wall -DF_CPU=$(F_CPU)

# main target
all: $(TARGET_OUT)

LDFLAGS = -mmcu=${MCU} -Wl,--gc-sections

# TODO: This is only necessary because the avr-toolchain package in
# Guix has a bug.
CFLAGS += -I${HOME}/.guix-profile/avr/include -I.
LDFLAGS += -L${HOME}/.guix-profile/avr/lib/avr5 -L${HOME}/.guix-profile/avr/lib -B${HOME}/.guix-profile/avr/lib

# make output
$(TARGET_OUT): $(O_FILES) $(H_SRC)
	$(CC) $(LDFLAGS) -o $@ $(O_FILES) && \
	$(SIZE) $(TARGET_OUT)

# make binary image
$(TARGET_HEX): $(TARGET_OUT)
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# objects from C files
%.o : %.c $(H_SRC)
	$(CC) $(CFLAGS) -o $@ -c $<

# program target
program: $(TARGET_HEX)
	$(PROG) $(PROGFLAGS) -U flash:w:$(TARGET_HEX)


clean:
	rm -f $(TARGET_HEX) $(TARGET_OUT) $(O_FILES)
