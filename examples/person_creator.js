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

console.setStyle('bold');

var
    name = console.input('Name -> '),
    last_name = console.input('Last name -> '),
    age = console.input('Age -> '),
    country = console.input('Country -> '),
    person = new Person(
        name, last_name, age, country, person,
    );

console.setColor('red');

console.log(`
== INFORMATION ==
${console.getColor('yellow')}
 - -> Name <${person.GetName()}>
 - -> Last name <${person.GetLastName()}>
 - -> Age <${person.GetAge()}>
 - -> Country <${person.GetCountry()}>
${console.getColor('red')}
== INFORMATION ==
`);

console.setStyle('normal');

var clear_console = console.input('Do you want clear console?[y/N]: ');

if(clear_console.toLowerCase() == 'y') console.clear();

console.log('Remember drink water!');