HEX = ./bin/main.hex
BINARY = ./bin/main.bin
CODEDIRS = ./src
INCDIRS = . ./include/  
CFILES = $(foreach D, $(CODEDIRS), $(wildcard $(D)/*.c))
OBJECTS = $(patsubst %.c, %.o, $(CFILES))

test:
	@echo $(CFILES)

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -o $(BINARY) main.o
	avr-objcopy -O ihex -R .eeprom $(BINARY) $(HEX)

flash:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:$(HEX)

clean:
	rm $(OBJECTS) $(HEX) $(BINARY)
