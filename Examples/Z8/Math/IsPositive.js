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

// This method determines if the number is positive. It is based on the fact 
// that all positive numbers have their leftmost bit to be set to 0. However, if 
// the number provided is zero or negative zero, it should still return false
if(Math.IsPositive(2))
    Console.Log('2 is a positive number!');
else
    Console.Log('2 is not a positive number!');

if(Math.IsPositive(-4))
    Console.Log('-4 is a positive number!');
else
    Console.Log('-4 is not a positive number!');