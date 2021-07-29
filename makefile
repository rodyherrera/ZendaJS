CXX = g++
V8 = libraries/v8
PYTHON_INTEGRATION = -I libraries/python3.8 -lpython3.8

define INCLUDE
	$(V8)/include
endef

define APP
	Zenda.cxx
endef

define LIB
	$(V8)/out/x64.release/obj/
endef

define OBJ
	v8_monolith
endef

export INCLUDE
export APP
export LIB
export OBJ

build:
	$(CXX) -I $$INCLUDE $$APP -L $$LIB -l $$OBJ -std=c++0x -pthread -o Zenda $(PYTHON_INTEGRATION)