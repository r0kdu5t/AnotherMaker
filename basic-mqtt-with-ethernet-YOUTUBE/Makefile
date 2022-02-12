BOARD ?= arduino:avr:uno
PORT ?= /dev/ttyS0
VERBOSE=

.PHONY: default all flash clean

default: all flash clean

all:
        arduino-cli compile --fqbn $(BOARD) ./ $(VERBOSE)

flash:
        arduino-cli upload --fqbn $(BOARD) --port $(PORT) $(VERBOSE)

clean:
        rm -r build
