# Variables
MCU=atmega328p
F_CPU=16000000UL
BAUD=9600
AVRDUDE_PORT=/dev/ttyUSB0
AVRDUDE_PROGRAMMER=arduino

CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude

# Flags
CFLAGS=-mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os -Wall -Iinclude
LDFLAGS=-mmcu=$(MCU)

# Files
TARGET=traffic_light_project
SRCDIR=src
INCLUDEDIR=include
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(SOURCES:.c=.o)

# Rules
all: $(TARGET).hex

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -P $(AVRDUDE_PORT) -b $(BAUD) -p $(MCU) -U flash:w:$(TARGET).hex:i

clean:
	rm -f $(OBJECTS) $(TARGET).elf $(TARGET).hex
