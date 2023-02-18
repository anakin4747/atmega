# Baremetal Programming on AVR MCUs

To better understand how to program microcontrollers, I am trying to program
AVR series microcontrollers for side projects as well as for my capstone
project.

## Atmega328P

This is the current progress of my Capstone Project.

The goal of my capstone is to add a solar array to the wings of a fixed wing
drone to extend flight time. This code is for the microcontroller that will
control the Max Power Point Tracker (MPPT).

Currently this code uses a timed interrupt to trigger every 250ms to read
3 analog inputs and output a pulse train that would drive the mosfet in the
boost converter of the MPPT.

I have the barebones of the project laid out. The next steps for the project
involve implementing the MPPT P&O algorithm and incorporating a control system
with a PI controller.
