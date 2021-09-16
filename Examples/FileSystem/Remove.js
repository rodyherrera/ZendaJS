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

// We have the remove method, but not only one...

// 1 -> FileSystem.Remove(PATH)
// - Can remove directories with their contents and can
// remove files.

// 2 -> FileSystem.RemoveFile(PATH)
// - Only can remove files

// 3 -> FileSystem.RemoveFolder(Path)
// - Only can remove directories

// Can receive multiple params
// FileSystem.Remove(PATH_ONE, PATH_TWO, PATH_THREE)...
// FileSystem.RemoveFile(PATH_ONE, PATH_TWO, PATH_THREE)...
// FileSystem.RemoveFolder(PATH_ONE, PATH_TWO, PATH_THREE)...

// Testing

// Creating a file and folder
FileSystem.CreateFile('TestOne');
FileSystem.CreateFile('TestTwo');
FileSystem.CreateFile('TestThree');
FileSystem.CreateFile('TestFour');
FileSystem.CreateFile('TestFive');

FileSystem.CreateFolder('FolderOne');
FileSystem.CreateFolder('FolderTwo');
FileSystem.CreateFolder('FolderThree');
FileSystem.CreateFolder('FolderFour');
FileSystem.CreateFolder('FolderFive');

// Deleting a file
FileSystem.RemoveFile('TestOne');

// Deleting multiple files
FileSystem.RemoveFile('TestTwo', 'TestThree');

// Using remove and deleting multiples files
FileSystem.Remove('TestFour', 'TestFive'); 

// Deleting a folder
FileSystem.RemoveFolder('FolderOne');

// Deleting multiple folders
FileSystem.RemoveFolder('FolderTwo', 'FolderThree');

// Using remove and deleting multiples directories
FileSystem.Remove('FolderFour', 'FolderFive');