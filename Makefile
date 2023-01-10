# /***
# * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
# * Licensed under the MIT license. See LICENSE file in the project root 
# * for full license information.
# *
# * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
# *
# * For related information - https://github.com/codewithrodi/ZendaJS/
# *
# * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# ****/

CXX = g++
OUTPUT = Zenda
INPUT = Zenda.cxx
INCLUDES = -I Libraries/V8/include -I Libraries/Python3.8 -I Libraries/Misc -I/usr/local/Poco/include 
INCLUDES_LIBS = -L Libraries/V8/lib -L Libraries/Misc/infoware -L/usr/local/Poco/lib -L Libraries/Misc/restclient-cpp
FLAGS = -lv8_monolith -lpython3.8 -linfoware -lPocoNet -lPocoFoundation -lPocoNetSSL -lrestclient-cpp -lcurl -luv

ifeq '$(findstring ;,$(PATH))' ';'
    OperatingSystem := Windows
else
    OperatingSystem := $(shell uname 2>/dev/null || echo Unknown)
    OperatingSystem := $(patsubst CYGWIN%,Cygwin,$(OperatingSystem))
    OperatingSystem := $(patsubst MSYS%,MSYS,$(OperatingSystem))
    OperatingSystem := $(patsubst MINGW%,MSYS,$(OperatingSystem))
endif

ifeq ($(OperatingSystem), Windows)
	FLAGS += -mwindows -L./dll/x64 -lwebview -lWebView2Loader
else ifeq ($(OperatingSystem), Darwin)
	FLAGS += -framework WebKit
else ifeq ($(OperatingSystem), Linux)
	FLAGS += `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.0`
endif

build:
	$(CXX) $(INCLUDES) $(INPUT) $(INCLUDES_LIBS) $(FLAGS) -lstdc++fs -std=c++17 -pthread -o $(OUTPUT) $(INCLUDES) $(FLAGS) -DV8_COMPRESS_POINTERS 
