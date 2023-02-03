default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -o main.bin main.o
	avr-objcopy -O ihex -R .eeprom main.bin main.hex

flash:
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex

clean:
	rm *.o *.hex *.bin
