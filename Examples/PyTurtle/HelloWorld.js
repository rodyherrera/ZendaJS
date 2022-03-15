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

PyTurtle.WindowTitle('Hello world Example - ZendaJS Python PyTurtle Integration');
PyTurtle.WindowBackgroundColor('#000000');

PyTurtle.PenColor('white');
PyTurtle.PenSize(4);
PyTurtle.Speed(30);

// H word
PyTurtle.PenUp();
PyTurtle.GoTo(-320, 0);
PyTurtle.PenDown();
PyTurtle.Left(90);
PyTurtle.Forward(70);
PyTurtle.PenUp();
PyTurtle.GoTo(-320, 35);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Forward(50);
PyTurtle.PenUp();
PyTurtle.GoTo(-270, 70);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Forward(70);

// E word
PyTurtle.PenUp()
PyTurtle.GoTo(-260, 0)
PyTurtle.PenDown()
PyTurtle.Right(180)
PyTurtle.Forward(70)
PyTurtle.Right(90)
PyTurtle.Forward(35)
PyTurtle.PenUp()
PyTurtle.GoTo(-260, 35)
PyTurtle.PenDown()
PyTurtle.Forward(35)
PyTurtle.PenUp()
PyTurtle.GoTo(-260, 0)
PyTurtle.PenDown()
PyTurtle.Forward(35)

// L word
PyTurtle.PenUp();
PyTurtle.GoTo(-210, 70);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Forward(70);
PyTurtle.Left(90);
PyTurtle.Forward(35);

// L word
PyTurtle.PenUp();
PyTurtle.GoTo(-165, 70);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Forward(70);
PyTurtle.Left(90);
PyTurtle.Forward(35);

// O word
PyTurtle.PenUp();
PyTurtle.GoTo(-90, 70);
PyTurtle.PenDown();

for(let Iterator = 0; Iterator < 25; Iterator++){
    PyTurtle.Right(15);
    PyTurtle.Forward(10);
}

// W word
PyTurtle.PenUp();
PyTurtle.GoTo(-10, 70),
PyTurtle.PenDown();
PyTurtle.Right(55);
PyTurtle.Forward(70);
PyTurtle.Left(150);
PyTurtle.Forward(70);
PyTurtle.Right(155);
PyTurtle.Forward(70);
PyTurtle.Left(150);
PyTurtle.Forward(70);

// O word
PyTurtle.PenUp();
PyTurtle.GoTo(70, 55);
PyTurtle.PenDown();

for(let Iterator = 0; Iterator < 25; Iterator++){
    PyTurtle.Right(15);
    PyTurtle.Forward(10);
}

// R word
PyTurtle.PenUp();
PyTurtle.GoTo(160, 70);
PyTurtle.PenDown(),
PyTurtle.Right(150);
PyTurtle.Forward(70);
PyTurtle.GoTo(160, 70);
PyTurtle.Right(200);

for(let Iterator = 0; Iterator < 20; Iterator++){
    PyTurtle.Right(15);
    PyTurtle.Forward(6);
}

PyTurtle.Left(180);
PyTurtle.Forward(60);

// L word
PyTurtle.PenUp();
PyTurtle.GoTo(220, 70);
PyTurtle.PenDown();
PyTurtle.Right(40);
PyTurtle.Forward(70);
PyTurtle.Left(90);
PyTurtle.Forward(35);

// L word
PyTurtle.PenUp();
PyTurtle.GoTo(290, 70);
PyTurtle.PenDown();
PyTurtle.Right(90);
PyTurtle.Forward(70);
PyTurtle.PenUp();
PyTurtle.GoTo(270, 70);
PyTurtle.PenDown();
PyTurtle.Left(120);

for(let Iterator = 0; Iterator < 15; Iterator++){
    PyTurtle.Right(15);
    PyTurtle.Forward(10);
}

PyTurtle.WindowExitOnClick();

// Executing PyTurtle
PyTurtle.Execute();
