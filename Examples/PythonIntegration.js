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

const Code = `
# With ZendaJS you can integrate Python in your
# JavaScript programs!

# This is a example simple usage

MESSAGE = str(input('Enter a message: '))

print(f'''

Your message is {MESSAGE} and it contains {len(MESSAGE)} characteres!

''')
`;

// Calling the pythonString function for execute code
PythonString(Code);

// Calling Python File
PythonFile('Examples/PyIntegrationExample.py')

// You need enter exact python file location :)

// Use pythonFancyFile for get better perfomance, u need python in your OS.
PythonFancyFile('Examples/PyIntegrationExample.py')