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

class Person{

    constructor(name, last_name, age, country){
        this.name = name;
        this.name = last_name;
        this.age = age;
        this.country = country;
    }


    // Getters
    GetName = () => this.name;
    GetLastName = () => this.last_name;
    GetAge = () => this.age;
    GetCountry = () => this.country;

};

Console.SetStyle('bold');

var
    name = Console.Input('Name -> '),
    last_name = Console.Input('Last name -> '),
    age = Console.Input('Age -> '),
    country = Console.Input('Country -> '),
    person = new Person(
        name, last_name, age, country, person,
    );

    Console.SetColor('red');

Console.Log(`
== INFORMATION ==
${console.GetColor('yellow')}
 - -> Name <${person.GetName()}>
 - -> Last name <${person.GetLastName()}>
 - -> Age <${person.GetAge()}>
 - -> Country <${person.GetCountry()}>
${Console.GetColor('red')}
== INFORMATION ==
`);

Console.SetStyle('normal');

var clear_console = Console.Input('Do you want clear console?[y/N]: ');

if(clear_console.toLowerCase() == 'y') Console.Clear();

Console.Log('Remember drink water!');