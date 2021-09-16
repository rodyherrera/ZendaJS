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

PyTurtle.WindowTitle('Adidas Logo Example - ZendaJS Python PyTurtle Integration');
PyTurtle.Speed(30);

PyTurtle.WindowSize(1000, 1000);
PyTurtle.WindowSetWorldCoordinates(-200, -150, 200, 250);
PyTurtle.WindowTracer(0, 0);
PyTurtle.BeginFill();
PyTurtle.Circle(100, 90, 200);
PyTurtle.Right(270);
PyTurtle.Circle(100, 90, 200);
PyTurtle.EndFill();
PyTurtle.PenUp();
PyTurtle.GoTo(-10, 0);
PyTurtle.PenDown();
PyTurtle.SetHeading(45);
PyTurtle.BeginFill();
PyTurtle.Circle(100, 90, 200);
PyTurtle.Right(270);
PyTurtle.Circle(100, 90, 200);
PyTurtle.EndFill();
PyTurtle.PenUp();
PyTurtle.GoTo(-20,0);
PyTurtle.PenDown();
PyTurtle.SetHeading(90);
PyTurtle.BeginFill();
PyTurtle.Circle(100, 90, 200);
PyTurtle.Right(270);
PyTurtle.Circle(100, 90, 200);
PyTurtle.EndFill();
PyTurtle.PenSize(20);
PyTurtle.PenUp();
PyTurtle.PenColor('#FFFFFF');
PyTurtle.GoTo(-200, 56);
PyTurtle.PenDown();
PyTurtle.Forward(400);
PyTurtle.PenSize(20);
PyTurtle.PenUp();
PyTurtle.PenColor('#FFFFFF');
PyTurtle.GoTo(-200, 40);
PyTurtle.PenDown();
PyTurtle.Forward(400);
PyTurtle.PenSize(20);
PyTurtle.PenUp();
PyTurtle.PenColor('#FFFFFF');
PyTurtle.GoTo(-200, 24);
PyTurtle.PenDown();
PyTurtle.Forward(400);
PyTurtle.WindowUpdate();

PyTurtle.WindowExitOnClick();

PyTurtle.Execute();