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

// QuickWriteFile
FileSystem.QuickWriteFile('Test.js', 'Hello');

FileSystem.WriteFile('Test.js', (Error, OldContent) => {
    if(Error){
        Console.Error('An error ocurred while trying write in "Test.js" file.');
        return;
    }
    Console.Information('The old content of "Test.js" is', OldContent);

    // The new content for add to the file is returned value of this function
    return " world from ZendaJS";
});

// Reading a file
const Content = FileSystem.QuickReadFile('Test.js');
Console.Information('New content', Content)

// Removing
FileSystem.Remove('Test.js');