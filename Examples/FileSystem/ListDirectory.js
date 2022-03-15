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

// Listing directory files
// Usage -> FileSystem.ListDirectory(Some absolute path)
const Files = FileSystem.ListDirectory(System.CurrentWorkingDirectory());

// This method return an array with all files/directories
Files.forEach((x) => {
    Console.Information(
        x, // Showing the file
        // We comprobate if file is dir or file
        FileSystem.IsDirectory(x) ? '<DIRECTORY>' : '<FILE>' // Showing type
    )
})