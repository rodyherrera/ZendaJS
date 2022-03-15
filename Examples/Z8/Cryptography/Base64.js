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

// Defining a string to encode and decode.
const Name = 'Rodolfo Herrera';

// Encode in Base64
const EncodedName = Base64.Encode(Name);

Console.Log(Name, 'encoded is:', EncodedName);

// Decode Base64
const DecodedName = Base64.Decode(EncodedName);
Console.Log(EncodedName, 'decoded is:', DecodedName);