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

// By calling the GetCPU method that provides the System object, this 
// method will return an object with data that is relevant about the 
// CPU of the machine that is executing the file.
const CPUInfo = System.GetCPU();

// Extracting instructions that may or may not be supported by the machine's processor.
// This is honestly not very relevant, but there are cases and cases.
const {
    S3DNow, 
    S3DNowExtended, 
    MMX, 
    MMXExtended, 
    SSE, 
    SSE2, 
    SSE3, 
    SSSE3, 
    SSE4A, 
    SSE41, 
    SSE42, 
    AES,
    AVX, 
    AVX2, 
    AVX512, 
    AVX512F, 
    AVX512CD, 
    AVX512PF,
    AVX512ER, 
    AVX512VL, 
    AVX512BW, 
    AVX512BQ, 
    AVX512DQ,
    AVX512Ifma, 
    AVX512Vbmi, 
    HLE, 
    BMI1, 
    BMI2, 
    ADX,
    MPX, 
    SHA, 
    PreFetchWT1, 
    FMA3, 
    FMA4, 
    XOP, 
    RDRand,
    x64, 
    x87FPU
} = CPUInfo.InstructionSetSupported;

// Showing the information
Console.Log(`\
: CPU Information 

: <General>
:: Frequency: ${CPUInfo.GetFrequency} Hz
:: Model Name: ${CPUInfo.GetModelName}
:: Vendor ID: ${CPUInfo.GetVendorID}
:: Architecture: ${CPUInfo.GetArchitecture}
:: Endianness: ${CPUInfo.GetEndianness}

: <Cores>
:: Logical Cores: ${CPUInfo.Cores.GetLogicals}
:: Physical Cores: ${CPUInfo.Cores.GetPhysicals}
:: Packages: ${CPUInfo.Cores.GetPackages}

: <Instructions set supported>
:: Support S3DNow: ${S3DNow}
:: Support S3DNowExtended: ${S3DNowExtended}
:: Support MMX: ${MMX}
:: Support MMXExtended: ${MMXExtended}
:: Support SSE: ${SSE}
:: Support SSE2: ${SSE2}
:: Support SSE3: ${SSE3}
:: Support SSSE3: ${SSSE3}
:: Support SSE4A: ${SSE4A}
:: Support SSE41: ${SSE41}
:: Support SSE42: ${SSE42}
:: Support AES: ${AES}
:: Support AVX: ${AVX}
:: Support AVX2: ${AVX2}
:: Support AVX512: ${AVX512}
:: Support AVX512F: ${AVX512F}
:: Support AVX512CD: ${AVX512CD}
:: Support AVX512PF: ${AVX512PF}
:: Support AVX512ER: ${AVX512ER}
:: Support AVX512VL: ${AVX512VL}
:: Support AVX512BW: ${AVX512BW}
:: Support AVX512BQ: ${AVX512BQ}
:: Support AVX512DQ: ${AVX512DQ}
:: Support AVX512Ifma: ${AVX512Ifma}
:: Support AVX512Vbmi: ${AVX512Vbmi}
:: Support HLE: ${HLE}
:: Support BMI1: ${BMI1}
:: Support BMI2: ${BMI2}
:: Support ADX: ${ADX}
:: Support MPX: ${MPX}
:: Support SHA: ${SHA}
:: Support PreFetchWT1: ${PreFetchWT1}
:: Support FMA3: ${FMA3}
:: Support FMA4: ${FMA4}
:: Support XOP: ${XOP}
:: Support RDRand: ${RDRand}
:: Support x64: ${x64}
:: Support x87FPU: ${x87FPU}
`);

// Showing data about CPU Cache
for(let Iterator = 0; Iterator < 3; Iterator++){
    const Cache = CPUInfo.Caches[Iterator];
    Console.Log(`\
: Cache Data [N° ${Iterator + 1}]
:: Size: ${Cache.GetSize}
:: Line Size: ${Cache.GetLineSize}
:: Associativity: ${Cache.GetAssociativity}
:: Type: ${Cache.Type}    
`);
}