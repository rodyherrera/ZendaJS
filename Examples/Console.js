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

// Using SETTERS
Console.SetBackground('black');
Console.Log('Zenda');

Console.SetBackground('red');
Console.Log('Zenda');

Console.SetBackground('green');
Console.Log('Zenda');

Console.SetBackground('yellow');
Console.Log('Zenda');

Console.SetBackground('blue');
Console.Log('Zenda');

Console.SetBackground('beige');
Console.Log('Zenda');

Console.SetBackground('white');
Console.Log('Zenda');

// Reseting all styles[background - color - styles]
Console.SetStyle('normal');

Console.SetStyle('end');
Console.Log('Zenda');

Console.SetStyle('bold');
Console.Log('Zenda');

Console.SetStyle('italic');
Console.Log('Zenda');

Console.SetStyle('url');
Console.Log('Zenda');

Console.SetStyle('blink');
Console.Log('Zenda')

Console.SetStyle('blink2');
Console.Log('Zenda');

Console.SetStyle('selected');
Console.Log('Zenda');

// Reseting all styles[background - color - styles]
Console.SetStyle('normal');

Console.SetColor('black')
Console.Log('Zenda');

Console.SetColor('red');
Console.Log('Zenda');

Console.SetColor('green');
Console.Log('Zenda');

Console.SetColor('yellow');
Console.Log('Zenda');

Console.SetColor('blue');
Console.Log('Zenda');

Console.SetColor('violet');
Console.Log('Zenda');

Console.SetColor('beige');
Console.Log('Zenda');

Console.SetColor('white');
Console.Log('Zenda');

Console.SetColor('grey');
Console.Log('Zenda');

// Reseting all styles[background - color - styles]
Console.SetStyle('normal');

// Using GETTERS -> Create for use in Console.Log or string.

// Example
Console.Log(`
${Console.GetStyle('bold')}
${Console.GetColor('white')}
${Console.GetBackground('yellow')}
Zenda`);

// Reseting all styles[background - color - styles]
Console.SetStyle('normal');

// Multiple values
Console.Log('Remember', 'drink', 'water', '<3');

// Clear
// Console.clear();

// Input
var answer = Console.Input('Enter your name: ');
Console.Log('Your name is ' + answer);

Console.Success('Success');
Console.Information('Information');
Console.Error('Error');
Console.Warning('Warning');