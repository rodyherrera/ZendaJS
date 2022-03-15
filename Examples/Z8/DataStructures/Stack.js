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

const Countries = new Stack();

Countries.Push('Chile');
Countries.Push('Russia');
Countries.Push('Poland');

// Since 3 values ​​have been added to the stack, their length should be 3
Console.Log('Length of stack =>', Countries.Length);

// When eliminating the last element of the stack, its length will now be 2
Countries.Pop(); // Last element of stack

Console.Log('Length of stack =>', Countries.Length);

// Stack.IsEmpty() checks if the length of the stack is equal to 0, that 
// is, if the stack has no items, this works and it will 
// return a true, otherwise a false.
if(Countries.IsEmpty())
    Console.Log('Stack is empty.');
else
    Console.Log('Stack is not empty');

// Stack.Peek() returns the last element of the stack.
Console.Log('Peek =>', Countries.Peek()); // Canada

// Stack.Clear() Remove all data from the stack.
Countries.Clear();

// After eliminating if we verify that the stack is 
// empty, the .Clear method should return true, as if 
// the length of the Stack is verified, it should be 0.
if(Countries.IsEmpty())
    Console.Log('Stack is empty.');
else
    Console.Log('Stack is not empty');