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

// Using the GetDistribution method to get the data of the distribution 
// that is being used on the system that is executing the file.
const DistInfo = System.GetDistribution();

// Showing the data on the term.
Console.Log(`\
: Distribution Information
:: Name: ${DistInfo.GetName}
:: Full name: ${DistInfo.GetFullName}
:: Patch: ${DistInfo.GetPatch}
:: Build number: ${DistInfo.GetBuildNumber}
:: Minor: ${DistInfo.GetMinor}
:: Major: ${DistInfo.GetMajor}
`);