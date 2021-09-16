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

PyTurtle.WindowTitle('Emoji Example - ZendaJS Python PyTurtle Integration');
PyTurtle.WindowBackgroundColor('light blue');

// function for creation of eye
function Eye(Color, Radius){
    PyTurtle.PenDown();
    PyTurtle.FillColor(Color);
    PyTurtle.BeginFill();
    PyTurtle.Circle(Radius);
    PyTurtle.EndFill();
    PyTurtle.PenUp();
}
 
// draw face
PyTurtle.FillColor('yellow');
PyTurtle.BeginFill();
PyTurtle.Circle(100);
PyTurtle.EndFill();
PyTurtle.PenUp();
 
// draw eyes
PyTurtle.GoTo(-40, 120);
Eye('white', 15);
PyTurtle.GoTo(-37, 125);
Eye('black', 5);
PyTurtle.GoTo(40, 120);
Eye('white', 15);
PyTurtle.GoTo(40, 125);
Eye('black', 5);
 
// draw nose
PyTurtle.GoTo(0, 75);
Eye('black', 8);
 
// draw mouth
PyTurtle.GoTo(-40, 85);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Circle(40, 180);
PyTurtle.PenUp();
 
// draw tongue
PyTurtle.GoTo(-10, 45);
PyTurtle.PenDown();
PyTurtle.Right(180);
PyTurtle.FillColor('red');
PyTurtle.BeginFill();
PyTurtle.Circle(10, 180);
PyTurtle.EndFill();
PyTurtle.HideTurtle();

PyTurtle.WindowExitOnClick();

PyTurtle.Execute();