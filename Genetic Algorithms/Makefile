all: build

.PHONY: build run clean help

build: DNA.cpp DNA.hpp Population.cpp Population.hpp main.cpp
	@g++ -O3 -Ofast -Os -o genetics *.cpp

run:
	@./genetics

clean:
	@rm genetics

help:
	@echo "Not implemented yet. Coming soon."
