HEX = bin/main.hex
BINARY = bin/main.bin
CC = avr-gcc
INCLUDE = . include
CFLAGS = -Os -mmcu=atmega328p -DF_CPU=16000000UL -MD -Wall -Wextra
SRC = . src
CFILES = $(foreach D, $(SRC), $(wildcard $(D)/*.c))
HEADERS = $(foreach D, $(INCLUDE), $(wildcard $(D)/*.h))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEP = $(patsubst %.c, %.d, $(CFILES))
ASM = $(patsubst %.c, %.s, $(CFILES))


$(HEX): $(BINARY)
	avr-objcopy -O ihex -j .text -j .data $< $@

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

assemble: $(ASM) # Not working

%.s: %.c # Not working
	$(CC) -S -o $@ $< # Not working

clean:
	rm $(OBJECTS) $(HEX) $(BINARY) $(DEP)

flash: $(HEX)
	avrdude -v -C /etc/avrdude.conf -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:$(HEX):i

-include $(OBJECTS:.o=.d)
