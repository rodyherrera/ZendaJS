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

PyTurtle.WindowTitle('Car Example - ZendaJS Python PyTurtle Integration');
PyTurtle.WindowBackgroundColor('light blue');

// Below code for drawing rectangular upper body
PyTurtle.PenColor('#008000');
PyTurtle.FillColor('#008000');
PyTurtle.PenUp();
PyTurtle.GoTo(0,0);
PyTurtle.PenDown();
PyTurtle.BeginFill();
PyTurtle.Forward(370);
PyTurtle.Left(90);
PyTurtle.Forward(50);
PyTurtle.Left(90);
PyTurtle.Forward(370);
PyTurtle.Left(90);
PyTurtle.Forward(50);
PyTurtle.EndFill();
    
// Below code for drawing window and roof
PyTurtle.PenUp();
PyTurtle.GoTo(100, 50);
PyTurtle.PenDown();
PyTurtle.SetHeading(45);
PyTurtle.Forward(70);
PyTurtle.SetHeading(0);
PyTurtle.Forward(100);
PyTurtle.SetHeading(-45);
PyTurtle.Forward(70);
PyTurtle.SetHeading(90);
PyTurtle.PenUp();
PyTurtle.GoTo(200, 50);
PyTurtle.PenDown();
PyTurtle.Forward(49.50);
    
// Below code for drawing two tyres
PyTurtle.PenUp();
PyTurtle.GoTo(100, -10);
PyTurtle.PenDown();
PyTurtle.FillColor('#000000');
PyTurtle.BeginFill();
PyTurtle.Circle(20);
PyTurtle.EndFill();
PyTurtle.PenUp();
PyTurtle.GoTo(300, -10);
PyTurtle.PenDown();
PyTurtle.PenColor('#000000');
PyTurtle.FillColor('#000000');
PyTurtle.BeginFill();
PyTurtle.Circle(20);
PyTurtle.EndFill();
    
PyTurtle.HideTurtle();

PyTurtle.WindowExitOnClick();

PyTurtle.Execute();