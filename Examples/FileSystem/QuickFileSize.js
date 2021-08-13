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

// Get a file size of current file
// the function returns a size in bytes.
const Size = FileSystem.QuickFileSize('QuickFileSiSze.js'); // If failed return -1(FALSE VALUE)

if(Size != -1)
    Console.Information('Size of "QuickFileSize.js" =>', Size, 'bytes');
else
    Console.Error('An error ocurred trying get size of "QuickFileSize.js"');