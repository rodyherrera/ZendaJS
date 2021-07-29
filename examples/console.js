// Using SETTERS

console.setBackground('black');
console.log('Zenda');

console.setBackground('red');
console.log('Zenda');

console.setBackground('green');
console.log('Zenda');

console.setBackground('yellow');
console.log('Zenda');

console.setBackground('blue');
console.log('Zenda');

console.setBackground('beige');
console.log('Zenda');

console.setBackground('white');
console.log('Zenda');

// Reseting all styles[background - color - styles]
console.setStyle('normal');

console.setStyle('end');
console.log('Zenda');

console.setStyle('bold');
console.log('Zenda');

console.setStyle('italic');
console.log('Zenda');

console.setStyle('url');
console.log('Zenda');

console.setStyle('blink');
console.log('Zenda')

console.setStyle('blink2');
console.log('Zenda');

console.setStyle('selected');
console.log('Zenda');

// Reseting all styles[background - color - styles]
console.setStyle('normal');

console.setColor('black')
console.log('Zenda');

console.setColor('red');
console.log('Zenda');

console.setColor('green');
console.log('Zenda');

console.setColor('yellow');
console.log('Zenda');

console.setColor('blue');
console.log('Zenda');

console.setColor('violet');
console.log('Zenda');

console.setColor('beige');
console.log('Zenda');

console.setColor('white');
console.log('Zenda');

console.setColor('grey');
console.log('Zenda');

// Reseting all styles[background - color - styles]
console.setStyle('normal');

// Using GETTERS -> Create for use in console.log or string.

// Example
console.log(`
${console.getStyle('bold')}
${console.getColor('white')}
${console.getBackground('yellow')}
Zenda`);

// Reseting all styles[background - color - styles]
console.setStyle('normal');

// Multiple values
console.log('Remember', 'drink', 'water', '<3');

// Clear
// console.clear();

// Input
var answer = console.input('Enter your name: ');
console.log('Your name is ' + answer);