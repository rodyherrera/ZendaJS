/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

// We create a two directories, empty and not empty
FileSystem.CreateFolder('TestOne', 'TestTwo');

FileSystem.CreateFile('TestTwo/File.js');

// Comprobate if TestOne is empty and if TestTwo is empty
if(FileSystem.IsEmptyDirectory('TestOne'))
    Console.Error('TestOne directory is empty.');
else
    Console.Success('TestOne directory is not empty.');

if(FileSystem.IsEmptyDirectory('TestTwo'))
    Console.Error('TestTwo directory is empty.');
else
    Console.Success('TestTwo directory is not empty.');

// <REMOVING>
FileSystem.Remove('TestOne', 'TestTwo');