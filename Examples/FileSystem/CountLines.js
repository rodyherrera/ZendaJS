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

// We are create the file for count lines
FileSystem.CreateFile('Test.js');

/// Adding Content
FileSystem.QuickWriteFile('Test.js', 
`Line 1
 Line 2
 Line 3
 Line 4
 Line 5
 Line 6
 Line 7
 Line 8
 Line 9
 Line 10
`);

// Now we are count the lines of Test.js file
Console.Information('Test.js file has', FileSystem.CountLines('Test.js'), 'Lines.');
// CountLines maybe return 10:)

// REMOVING
FileSystem.Remove('Test.js');