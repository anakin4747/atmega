# Baremetal Programming on AVR MCUs

To better understand how to program microcontrollers, I am trying to program
AVR series microcontrollers for side projects as well as for my capstone
project.

## Atmega328P

I have attempted several mini programs with the Atmega328P since I have
a couple arduinos laying around. 

But I can never get past what feel like small hurdles.

I want my project to have a good foundation so I am starting the project with
a build system with file structure. But as soon as separate the project into
several files, the program no longer works.

I stripped the project down to the blink example and tried expanding it to
include PWM of the built-in LED. But as soon as the code is split between .c
files it acts up. The built-in LED just blinks 3 times over and over. I believe
the triple blink is caused by the boot loader but I am confused as to what
exactly is happening.

