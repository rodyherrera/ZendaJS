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

// Static Import
import { SayHelloWithPython, MyVar, MyFunction } from "./Examples/Import/Library.js";

SayHelloWithPython(); // Calling the function from other file =D

Console.Log(MyVar);

MyFunction();

// Dynamic Import
import('./Examples/Import/Library.js')
    .then((module) => {
        module.SayHelloWithPython(); // Calling the function using module parameter =D
    
        Console.Log(module.MyVar);
        
        MyFunction();
    });