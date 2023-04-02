CC = avr-gcc
HEX = bin/main.hex
BINARY = bin/main.elf
CFLAGS = -g -Os -Wall -mcall-prologues -mmcu=atmega328p -MD
SRC = src
CFILES = $(foreach D, $(SRC), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEP = $(patsubst %.c, %.d, $(CFILES))
ASM = $(patsubst %.c, %.S, $(CFILES))

all: $(HEX)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(CC) $(CFLAGS) -S $< -o $@

$(HEX): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(BINARY)
	avr-objcopy -j .text -j .data -O ihex $(BINARY) $(HEX)
	avr-size $(HEX)

clean:
	rm -f $(OBJECTS) $(ASM) $(BINARY) $(HEX) $(DEP)

flash: $(HEX)
	avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -U flash:w:$(HEX)
	make clean

flash-ArduinoISP:
	avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -U flash:w:.arduinoISP.hex
	make clean

flash-ICSP: $(HEX)
	avrdude -p atmega328p -c stk500v1 -P /dev/ttyUSB0 -b 19200 -U flash:w:$(HEX)
	make clean

fuse:
	avrdude -p atmega328p -c stk500v1 -P /dev/ttyUSB0 -U lock:r:-:h -U lfuse:r:-:h -U hfuse:r:-:h -U efuse:r:-:h

-include $(OBJECTS:.o=.d)

