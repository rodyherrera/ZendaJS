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
INPUT = Zenda.cxx
V8 = Libraries/V8
INCLUDES = -I Libraries/V8/include -I Libraries/Python3.8
INCLUDES_LIBS = -L Libraries/V8/lib
FLAGS = -lv8_monolith -lpython3.8

build:
	$(CXX) $(INCLUDES) $(INPUT) $(INCLUDES_LIBS) $(FLAGS) -lstdc++fs -std=c++2a -pthread -o $(OUTPUT) $(INCLUDES) $(FLAGS) -DV8_COMPRESS_POINTERS