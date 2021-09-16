/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

Console.Clear();
Console.Information(`
  * ATENTION
 
    - The window will not close automatically, this because at the end of the 
    - file is the sentence "PyTurtle.WindowExitOnClick()", therefore if you want 
    - to exit you must click on the window, otherwise if you want the window 
    - to close automatically, just remove the line of 
    - code "PyTurtle.WindowExitOnClick()".
`);

PyTurtle.Initialize();

PyTurtle.WindowTitle('ZendaJS Writed - ZendaJS Python PyTurtle Integration');
PyTurtle.WindowBackgroundColor('light blue');

PyTurtle.Shape('turtle');
PyTurtle.Left(45);
PyTurtle.Forward(50);
PyTurtle.Right(65);
PyTurtle.Circle(150, 350);
PyTurtle.Home();
PyTurtle.PenUp();
PyTurtle.GoTo(-40, 150);
PyTurtle.Write('ZendaJS', 'font=("Arial", 50, "normal")');
PyTurtle.Home();
PyTurtle.Backward(20);

PyTurtle.WindowExitOnClick();

PyTurtle.Execute();