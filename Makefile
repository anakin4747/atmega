HEX = bin/main.hex
BINARY = bin/main.bin
CC = avr-gcc
INCLUDE = . include
CFLAGS = -Os -mmcu=atmega328p -DF_CPU=16000000UL -MD
SRC = . src
CFILES = $(foreach D, $(SRC), $(wildcard $(D)/*.c))
HEADERS = $(foreach D, $(INCLUDE), $(wildcard $(D)/*.h))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEP = $(patsubst %.c, %.d, $(CFILES))


$(HEX): $(BINARY)
	avr-objcopy -O ihex -j .text -j .data -R .eeprom $< $@

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(HEX) $(BINARY) $(DEP)

flash: $(HEX)
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:$(HEX):i

-include $(OBJECTS:.o=.d)
