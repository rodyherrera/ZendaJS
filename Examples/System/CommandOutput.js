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

// System.CommandOutput('Some Command') allows you to get the output of that command if it has one.

// Command to execute: Zenda version, this should return the version of Zenda you are using
const CurrentVersion = System.CommandOutput('Zenda version');

// Display output, we use .trim() <String method> for remove whitespaces.
Console.Log('The current version of ZendaJS is =>', CurrentVersion.trim());