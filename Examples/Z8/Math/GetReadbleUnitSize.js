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

// The GetReadbleUnitSize function of the Math object allows 
// you to obtain a readable string that shows the size of something, it 
// receives Bytes as a parameter, whether or not you want to use the SI 
// metrics and the numbers after the decimal.

Console.Log(Math.GetReadableUnitSize(1551859712))  // 1.4 GiB
Console.Log(Math.GetReadableUnitSize(5000, true))  // 5.0 kB
Console.Log(Math.GetReadableUnitSize(5000, false))  // 4.9 KiB
Console.Log(Math.GetReadableUnitSize(-10000000000000000000000000000))  // -8271.8 YiB
Console.Log(Math.GetReadableUnitSize(999949, true))  // 999.9 kB
Console.Log(Math.GetReadableUnitSize(999950, true))  // 1.0 MB
Console.Log(Math.GetReadableUnitSize(999950, true, 2))  // 999.95 kB
Console.Log(Math.GetReadableUnitSize(999500, true, 0))  // 1 MB