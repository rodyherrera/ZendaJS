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

// Allows you to search a element in array with interpolation search method
const Numbers = [66, 102, 34, 12, 45, 6, 1, 46, 102, 16];

// The method required a sorted array
const SortedNumbers = Numbers.SelectionSort();

// If number 16 in the array?
const Is16InArray = SortedNumbers.InterpolationSearch(16);

Console.Log('Sorted Array =>', SortedNumbers);

if(Is16InArray != -1)
    Console.Log('Number 16 exists in the array in the position =>', Is16InArray);
else
    Console.Log('Number 16 does not exists in the array.');