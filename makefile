CXX = g++
OUTPUT = Zenda
V8 = libraries/v8
PYTHON_INTEGRATION = -I libraries/python3.8 -lpython3.8

define INCLUDE
	$(V8)/include
endef

define APP
	Zenda.cxx
endef

define LIB
	$(V8)/lib/
endef

define OBJ
	v8_monolith
endef

export INCLUDE
export APP
export LIB
export OBJ

build:
	$(CXX) -I $$INCLUDE $$APP -L $$LIB -l $$OBJ -std=c++0x -pthread -o $(OUTPUT) $(PYTHON_INTEGRATION) -DV8_COMPRESS_POINTERS