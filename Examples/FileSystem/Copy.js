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

// We create a test file
FileSystem.CreateFile('Test.js');

// Now we are create a folder
FileSystem.CreateFolder('Folder');

// Now we are copy file to the created folder
FileSystem.Copy('Test.js', 'Folder');

// Delete old Test.js file
FileSystem.Remove('Test.js');

// GREAT!

// <REMOVING FILES>
FileSystem.Remove('Folder');