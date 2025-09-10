BOARD?=arduino:avr:uno
PORT?=/dev/ttyACM0
BUILD=build

.PHONY: defaulft lint all flash clean

default: lint all flash clean

lint:
	-cpplint --extensions=ino --filter=-legal/copyright *.ino

all:
	arduino-cli compile --fqbn $(BOARD) --output-dir $(BUILD) ./

flash:
	arduino-cli upload --fqbn $(BOARD) --port $(PORT) --input-dir $(BUILD)

clean:
	rm -r build
