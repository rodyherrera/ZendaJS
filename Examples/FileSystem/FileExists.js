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

// Creating a file
FileSystem.CreateFile('SomeFile.js');

if(FileSystem.FileExists('SomeFile.js'))
    Console.Log('SomeFile.js exists in current directory');
else
    Console.Log('SomeFile.js does not existsin current directory');

// Removing file
FileSystem.RemoveFile('SomeFile.js');

if(FileSystem.FileExists('SomeFile.js'))
    Console.Log('SomeFile.js exists in current directory');
else
    Console.Log('SomeFile.js does not existsin current directory');