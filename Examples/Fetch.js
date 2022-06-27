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

Fetch(`https://swapi.dev/api/people/1/`, {
    // ! The second argument that the Fetch 
    // ! function receives is totally optional.
    /*
        Method: '...',
        Body: '...',
        UserAgent: '...',
        CaFilePath: '...',
        CertPath: '...',
        CertType: '...',
        KeyPath: '...',
        KeyPassword: '...',
        Proxy: 'Hostname:Port',
        Timeout: 0,
        Headers: {
            MyHeader: HeaderVal
            ...
        },
        BasicAuth: {
            Username: '...',
            Password: '...'
        },
    */
})
    .then(Console.Log);