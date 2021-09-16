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

// We create the file
FileSystem.CreateFile('Test.js');

// We add content to the file
FileSystem.QuickWriteFile('Test.js', 'Some content');

// Showing in the console
Console.Information(FileSystem.QuickReadFile('Test.js'));

// Creating a new file in a some folder
FileSystem.CreateFolder('SomeFolder');
FileSystem.CreateFile('SomeFolder/SomeFile.js');

// Copy the Test.js file content to SomeFolder/SomeFile.js
FileSystem.CopyFileContent('Test.js', 'SomeFolder/SomeFile.js');

// Showing the content of SomeFolder/SomeFile.js
Console.Information(FileSystem.QuickReadFile('SomeFolder/SomeFile.js'));

// <REMOVING FILES>
FileSystem.Remove('Test.js', 'SomeFolder')