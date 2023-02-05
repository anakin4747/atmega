HEX = bin/main.hex
BINARY = bin/main.bin
CC = avr-gcc
INCLUDE = include
CFLAGS = -Og -g -mmcu=atmega328p -DF_CPU=16000000UL -MD -Wall -Wextra
SRC = src
CFILES = $(foreach D, $(SRC), $(wildcard $(D)/*.c))
HEADERS = $(foreach D, $(INCLUDE), $(wildcard $(D)/*.h))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))
DEP = $(patsubst %.c, %.d, $(CFILES))


$(HEX): $(BINARY)
	avr-objcopy -O ihex -j .text -j .data $< $@

$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJECTS) $(HEX) $(BINARY) $(DEP)

flash: $(HEX)
	avrdude -v -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:$(HEX)

-include $(OBJECTS:.o=.d)
