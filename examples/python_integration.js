const code = `
# With ZendaJS you can integrate Python in your
# JavaScript programs!

# This is a example simple usage

MESSAGE = str(input('Enter a message: '))

print(f'''

Your message is {MESSAGE} and it contains {len(MESSAGE)} characteres!

''')
`;

// Calling the pythonString function for execute code
pythonQuickString(code);

// Calling Python File
pythonQuickFile('examples/PyIntegrationExample.py')

// You need enter exact python file location :)

// Use pythonFancyFile for get better perfomance, u need python in your OS.
pythonFancyFile('examples/PyIntegrationExample.py')