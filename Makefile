CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Wno-unused-parameter
LIBS = `pkg-config --cflags --libs gtk+-3.0` -lpthread -lm

TARGET = kulculator
SOURCE = kulculator.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

deps-debian:
	sudo apt install g++ libgtk-3-dev

deps-fedora:
	sudo dnf install gcc-c++ gtk3-devel

deps-arch:
	sudo pacman -S base-devel gtk3 pkg-config mpg123 ffmpeg

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: deps-ubuntu deps-fedora deps-arch clean run