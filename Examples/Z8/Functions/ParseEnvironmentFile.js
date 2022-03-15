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

// ! Getting data from an .env file, , to the function we 
// ! indicate as the first parameter the address of the file to read.
const Data = ParseEnvironmentFile('.env', {
    // ! The second parameter of the function is optional, but 
    // ! it refers to the options that the reading has, it receives 
    // ! an object with two values, [Comments] and [EmptyLines], both 
    // ! set by default to False, if you set them to True it will be 
    // ! shown In the Data the Comments or the empty Lines in case of 
    // ! the established thing.
    Comments: true, 
    EmptyLines: true 
});

// ! Showing the parsed Data after reading the .env file
// ! => Key => Value
Object.keys(Data).forEach((Key) => Console.Log(Key, '=>', Data[Key]));

// ! Show the author
Console.Log('The author is:', Data.Author);

// ! Show the first comment
Console.Log('The first comment is:', Data.Comment_1);