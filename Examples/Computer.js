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

// Using native function of Zenda
var OperativeSystem = System.Platform();

Console.Log(OperativeSystem);

// Show current working directory/current path/current location
Console.Log(System.CurrentWorkingDirectory());

// Using sleep for wait and execute instructions after wait
Console.Log('Showing network interface in next 5 seconds...');
Sleep(5000);

// Executing command by OS
if(OperativeSystem.startsWith('WIN')){

    // Running command
    System.Execute('ipconfig');

}else{

    // If not OS == WIN(Windows), is probably derived from UNIX.

    // Ipconfig for UNIX OS == ifconfig

    System.Execute('ifconfig');

}