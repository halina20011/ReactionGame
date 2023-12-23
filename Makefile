MCU = attiny24a
F_CPU = 8000000UL
BAUD = 19200

PROGRAMMER = avrisp
CHIP = t24a
PORT = /dev/ttyUSB0

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

FILES = $(wildcard ./src/*.c)
OBJECTS = $(patsubst ./src/%.c, ./build/%.o, $(FILES))
HEADERS = $(patsubst ./src/%.c, ./build/%.h, $(FILES))

CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I.
CFLAGS = -Os -std=gnu99 -Wall -Wextra -Wshadow
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
LDFLAGS = -Wl,-Map,./build/main.map
LDFLAGS += -Wl,--gc-sections

TARGET = -mmcu=$(MCU)

.PHONY: buildDir debug talk build flash readFuses

buildDir:
	mkdir -p build

debug:
	@echo $(FILES)
	@echo $(OBJECTS)
	@echo $(HEADERS)

build/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(TARGET) -c -o $@ $<;

main.elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET) $^ -o ./build/$@

%.hex: %.elf
	$(OBJCOPY) -j .text -j .data -O ihex ./build/$< ./build/$@

build: $(FILES) main.hex

talk:
	$(AVRDUDE) -p $(CHIP) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD)

flash: build
	$(AVRDUDE) -p $(CHIP) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:./build/main.hex

# i - intel hex format
# d - decimal format
# b - binary format
FORMAT = b
readFuses:
	$(AVRDUDE) -p $(CHIP) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -n -U lfuse:r:-:$(FORMAT) -U hfuse:r:-:$(FORMAT)
