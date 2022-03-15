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

const Countries = new Queue();

Countries.EnQueue('Chile');
Countries.EnQueue('Russia');
Countries.EnQueue('Poland');

// Since 3 values ​​have been added to the queue, their length should be 3
Console.Log('Length of queue =>', Countries.Length);

// We remove the last element of the cake, its length should now be 2.
Countries.DeQueue();

Console.Log('Length of queue =>', Countries.Length);

// Queue.IsEmpty() checks if the length of the stack is equal to 0, that 
// is, if the stack has no items, this works and it will 
// return a true, otherwise a false.
if(Countries.IsEmpty())
    Console.Log('Queue is empty.')
else
    Console.Log('Queue is not empty.');

// Queue.Peek() returns the last element of the Queue.
Console.Log('Peek =>', Countries.Peek());

// Queue.Clear() Reove all data from the Queue
Countries.Clear();

// After eliminating if we verify that the Queue is 
// empty, the .Clear method should return true, as if 
// the length of the Queue is verified, it should be 0.
if(Countries.IsEmpty())
    Console.Log('Queue is empty.')
else
    Console.Log('Queue is not empty.');
