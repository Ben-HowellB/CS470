# Makefile for CPU Scheduling Simulator (Lab 3)

CC      = gcc
CFLAGS  = -std=c99 -Wall -O2

.PHONY: all clean

all: SJF_inital RR_inital

SJF_inital: SJF_inital.c
	$(CC) $(CFLAGS) -o SJF_inital SJF_inital.c

RR_inital: RR_inital.c
	$(CC) $(CFLAGS) -o RR_inital RR_inital.c

clean:
	rm -f SJF_inital RR_inital
