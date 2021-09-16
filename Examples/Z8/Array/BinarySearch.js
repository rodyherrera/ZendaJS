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

// Allows you to search a element in array with binary search method
const Numbers = [66, 102, 34, 12, 45, 6, 1, 46, 102, 16];

// If number 102 in the array?
const Is102InArray = Numbers.BinarySearch(102);

// Return index of value if the value exists in the array or return -1 if the value
// does not exists in the array.
if(Is102InArray != -1)
    Console.Log('The number 102 exists in the array in the position ->', Is102InArray);
else
    Console.Log('The number 102 does not exist in the array.');