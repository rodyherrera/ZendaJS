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

UseWebView({
    // ! Set a title for the window.  <Optional / Default = ZendaJS - Default WebView Window Title>
    Title: 'The ZendaJS Github Repository',
    // ! Indicates the website that will be loaded in the window  <Optional / Default = https://github.com/codewithrodi/ZendaJS/>
    Website: 'https://github.com/codewithrodi/ZendaJS/',
    // ! Hint of the window <Optional / Default = Normal>
    // ! [Fixed: the window cannot change its size] 
    // ! [Normal: The window will open with the width and height indicated and may be resizable.]
    // ! [Maximum: The window will open with a minimum height and width and its maximum width and maximum height will be the established when calling the function] 
    // ! [Minimum: The window will open with the minimum resolution indicated, it cannot have a width and height lower than the one indicated]
    Hint: 'Fixed',
    // ! The width of the window <Optional / Default = 800>
    Width: 800,
    // ! Height of the window <Optional / Default = 600>
    Height: 600,
    // ! Javascript code that will be executed when loading the page. <Optional / Default = ''>
    Evaluate: 'console.log("Window loaded!")'
});