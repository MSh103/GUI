# Replace this with the path you get from `brew info sfml`
ifeq ($(OS), Windows_NT)
	SFML_PATH = D:\\DEV\\SFML64Bit\\SFML-2.6.1\\lib
	INCLUDE_PATH = D:\\DEV\\SFML64Bit\\SFML-2.6.1\\include
endif
ifeq ($(OS), Darwin)
	SFML_PATH = /opt/homebrew/Cellar/sfml/2.6.1
	INCLUDE_PATH = /opt/homebrew/include
endif

# Replace "src" with the name of the folder where all your cpp code is
cppFileNames := $(shell find ./src -type f -name "*.cpp")

all: compile

compile:	
	g++ -std=c++17 $(cppFileNames) -I${INCLUDE_PATH} -o Gui -L$(SFML_PATH)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
