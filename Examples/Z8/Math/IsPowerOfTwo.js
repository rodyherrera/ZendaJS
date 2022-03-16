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

// This method checks if a number provided is power of two. It uses the following property. 
// Let's say that PowerNumber is a number that has been formed as a power of two (i.e. 2, 4, 8, 16 etc.). 
// Then if we'll do & operation between PowerNumber and PowerNumber - 1 it will return 0 (in case if 
// number is power of two).
for(let Iterator = 1; Iterator <= 20; Iterator++)
    Console.Log(`Is ${Iterator} power of 2?:`, Math.IsPowerOfTwo(Iterator));