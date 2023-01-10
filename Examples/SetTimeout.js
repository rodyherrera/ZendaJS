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

Console.Log('Wait two seconds to read the magic message...');

// ! The SetTimeout function receives a total of 2 
// ! parameters, where the first corresponds to the callback 
// ! (function) that you want to execute once a certain amount 
// ! of time has passed, expressed in milliseconds, a value 
// ! that corresponds to the second parameter that the function receives.
SetTimeout(() => {
    Console.Log('Hello world');
}, 2000);