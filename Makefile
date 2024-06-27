SFML_PATH := 
INCLUDE_PATH := 

ifeq ($(OS), Windows_NT)
	SFML_PATH := D:\\DEV\\SFML64Bit\\SFML-2.6.1\\lib
	INCLUDE_PATH := D:\\DEV\\SFML64Bit\\SFML-2.6.1\\include
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		SFML_PATH := /usr/lib
		INCLUDE_PATH := /usr/include
	endif
	ifeq ($(UNAME_S), Darwin)
		SFML_PATH := /opt/homebrew/Cellar/sfml/2.6.1/lib
		INCLUDE_PATH := /opt/homebrew/include
	endif
endif

# Replace "src" with the name of the folder where all your cpp code is
cppFileNames := $(shell find ./src -type f -name "*.cpp")

all: compile

compile:	
ifeq ($(OS), Windows_NT)
	# For Windows
	g++ -std=c++17 $(cppFileNames) -I$(INCLUDE_PATH) -o Gui -L$(SFML_PATH) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lwinmm -lgdi32 -lole32 -lwinpthread -IC:\\msys64\\usr\\include\\win32 -LC:\\msys64\\usr\\lib\\win32
else
	# For Mac OSX
	g++ -std=c++17 $(cppFileNames) -I$(INCLUDE_PATH) -o Gui -L$(SFML_PATH) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -framework CoreFoundation
endif
