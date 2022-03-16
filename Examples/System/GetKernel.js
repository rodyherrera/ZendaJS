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

// Getting Kernel information using the GetKernel method.
const KernelInfo = System.GetKernel();

Console.Log(`\
: <Kernel>
:: Variant: ${KernelInfo.GetVariant}
:: Build number: ${KernelInfo.GetBuildNumber}
:: Major: ${KernelInfo.GetMajor}
:: Minor: ${KernelInfo.GetMinor}
:: Patch: ${KernelInfo.GetPatch}
`);