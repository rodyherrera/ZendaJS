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

// We are create a file and a directory
FileSystem.CreateFile('Test.js');
FileSystem.CreateFolder('Folder');

// Showing the types (Functions return bool type<TRUE>/<FALSE>)
Console.Log('Test.js is file? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is directory? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is blockfile? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is characterfile? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is fifo? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is socket? =>', FileSystem.IsFile('Test.js'));
Console.Log('Test.js is symlink? =>', FileSystem.IsFile('Test.js'));

Console.Log('Folder is file? =>', FileSystem.IsFile('Folder'));
Console.Log('Folder is directory? =>', FileSystem.IsDirectory('Folder'));
Console.Log('Folder is blockfile? =>', FileSystem.IsBlockFile('Folder'));
Console.Log('Folder is characterfile? =>', FileSystem.IsCharacterFile('Folder'));
Console.Log('Folder is fifo? =>', FileSystem.IsFifo('Folder'));
Console.Log('Folder is socket? =>', FileSystem.IsSocket('Folder'));
Console.Log('Folder is symlink? =>', FileSystem.IsSymlink('Folder'));

// Removing
FileSystem.Remove('Folder', 'Test.js')