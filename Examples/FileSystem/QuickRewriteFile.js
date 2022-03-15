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
FileSystem.CreateFile('Test.js');

// Adding a content
FileSystem.QuickRewriteFile('Test.js', 'Some Content')

// Rewriting in a file
FileSystem.QuickRewriteFile('Test.js', 'New Content'); // Maybe bool

// Showing the content
const Content = FileSystem.QuickReadFile('Test.js');

Console.Log(Content);

// Removing
FileSystem.Remove('Test.js');