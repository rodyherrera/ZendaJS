/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/codewithrodi/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

#include <iostream>
#include <unistd.h>
#include <thread>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <experimental/filesystem>
#include <uv.h>

uv_loop_t *DEFAULT_LOOP = uv_default_loop();

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <v8.h>
#include <libplatform/libplatform.h>

#include "Source/Global.hxx"
#include "Source/Utils/Shortcuts.hxx"
#include "Source/Utils/Algorithms.hxx"
#include "Source/Utils/Shared.hxx"
#include "Source/Utils/FileSystem.hxx"

#include "Source/Module.hxx"
#include "Source/Engine.hxx"

int main(int argc, char *argv[]){
    Zenda::Engine::Initialize(argc, argv);
    return 0;
}