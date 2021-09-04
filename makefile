# /***
# * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
# * Licensed under the MIT license. See LICENSE file in the project root 
# * for full license information.
# *
# * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
# *
# * For related information - https://github.com/rodiihernandezz/ZendaJS/
# *
# * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ****/

CXX = g++
OUTPUT = Zenda
V8 = Libraries/V8
INCLUDES = -I Libraries/Python3.8
FLAGS = -lpython3.8

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
	$(CXX) -I $$INCLUDE $$APP -L $$LIB -l $$OBJ -lstdc++fs -std=c++17 -pthread -o $(OUTPUT) $(INCLUDES) $(FLAGS) -DV8_COMPRESS_POINTERS