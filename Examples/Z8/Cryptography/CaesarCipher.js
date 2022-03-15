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

// CaesarCypher
// Encrypt function receive 3 parameters, 1 optional
// => (Str<Required>, Shift<Required>, Alphabet<Optional>)
// Decrypt function receive 3 parameters, 1 optinal
// => (EncryptedStr<Required>, Shift<Required>, Alphabet<Optional>)

const Name = 'Rodolfo Herrera Hernandez';

// Encrypt the name
const EncryptedName = CaesarCipher.Encrypt(Name, 50);

Console.Log(Name, 'encrypted is:', EncryptedName);

// Decrypt the name
const DecryptedName = CaesarCipher.Decrypt(EncryptedName, 50);

Console.Log(EncryptedName, 'decrypted is:', DecryptedName);