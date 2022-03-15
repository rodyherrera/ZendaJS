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

// We create a file
FileSystem.CreateFile('SomeFile.js');

// Comprobate if file exists
if(FileSystem.FileExists('SomeFile.js'))
    Console.Success('SomeFile.js exists in current directory');
else
    Console.Error('SomeFile.js does not exists in current directory');

// Now we are rename the file
FileSystem.Rename('SomeFile.js', 'SomeTestFile.js');

Console.Log(' = RENAMED = ');

// Verify is the file exists
if(FileSystem.FileExists('SomeTestFile.js'))
    Console.Success('SomeTestFile.js exists in current directory');
else
    Console.Error('SomeTestFile.js does not exists in current directory');

if(FileSystem.FileExists('SomeFile.js'))
    Console.Success('SomeFile.js exists in current directory');
else
    Console.Error('SomeFile.js does not exists in current directory');

// REMOVING
FileSystem.Remove('SomeTestFile.js');