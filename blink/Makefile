TARGET=blink
SOURCES=blink.c
DEPS=
COBJ=$(SOURCES:.c=.o)

CC=avr-gcc
OBJC=avr-objcopy
MCU=atmega328p
CFLAGS=-I. -Wall -Os -DF_CPU=16000000UL 
LDFLAGS=

ISPPORT=/dev/ttyACM0
ISPDIR=/home/prateem/Downloads/arduino-1.8.2/hardware/tools/avr
ISP=$(ISPDIR)/bin/avrdude
ISPFLAGS=-c arduino -p $(MCU) -P $(ISPPORT) -b 115200 -C $(ISPDIR)/etc/avrdude.conf
#ISPFLAGS=-c arduino -p $(MCU) -P $(ISPPORT) -b 115200 -C /etc/avrdude.conf 

all: $(TARGET)

%.o: %.c $(DEPS)
	@echo "\tCC" $<			
	$(CC) -mmcu=$(MCU) -c -o $@ $< $(CFLAGS)

$(TARGET): $(COBJ)
	@echo "\tLINKING CC" $<
	$(CC) -mmcu=$(MCU) -o $(TARGET) $(COBJ) $(LDFLAGS)
	$(OBJC) -O ihex -R .eeprom $(TARGET) $(TARGET).hex

clean:
	@echo ========== cleanup ========== 
	rm -rf *.o *.hex $(TARGET)	

read:
	sudo $(ISP) $(ISPFLAGS) -U flash:r:$(TARGET)_backup.hex:i

install:
	sudo $(ISP) $(ISPFLAGS) -U flash:w:$(TARGET).hex
