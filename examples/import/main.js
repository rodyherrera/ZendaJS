// Static Import
import { SayHelloWithPython, MyVar, MyFunction } from "./examples/import/library.js";

SayHelloWithPython(); // Calling the function from other file =D

Console.Log(MyVar);

MyFunction();

// Dynamic Import
import('./examples/import/library.js')
    .then((module) => {
        module.SayHelloWithPython(); // Calling the function using module parameter =D
    
        Console.Log(module.MyVar);
        
        MyFunction();
    });