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

// It allows generating a random string, 
// receives two parameters, these are optional where 
// the first is the length of the string whose default 
// value is 8 and the characters that should be used to generate the string.

var MyString = '';

// Example 1
Console.Log(MyString.RandomFill()); // With default parameters

// Example 2
Console.Log(MyString.RandomFill(12)); // With custom length

// Example 3
const Characters = 'abcABC[]&&()';

Console.Log(MyString.RandomFill(8, Characters)); // Random length and characters