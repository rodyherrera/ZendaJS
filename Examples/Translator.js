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

// OpenDeyim Public API
// https://github.com/codewithrodi/opendeyim/
// www.opendeyim.codewithrodi.com
const ENDPOINT = 'https://deyimapi.codewithrodi.com/api/v1/translate';

(async function(){
    while(true){
        const TextToTranslate = Console.Input('Enter a text to translate into English: ');
        try{
            const Response = await Fetch(ENDPOINT, {
                Method: 'POST',
                Body: JSON.stringify({
                    Query: TextToTranslate,
                    Target: 'en',
                    Source: 'auto',
                    Format: 'text'
                }),
                Headers: { 'Content-Type': 'application/json' }
            });
            Console.Log('=>', JSON.parse(Response.Body).Data.TranslatedText, '\n')
        }catch(Error){
            Console.Error(Error);
        }
    }
}());
