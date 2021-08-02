// Creating an object that will have the messages that will be displayed on the screens.
const Lang = {
    DependenciesWarn: 'The dependencies will be installed in the next 5 seconds...',
    DataAmount: 'How much false data do you want to generate ?: ', 
    SaveInFileQuery: 'Do you want save data in a file?[y/N]: ',
    FileName: 'Enter a file name: ',
};

// Script Class Definition
class FakerGenerator{
    amount_of_data = undefined;

    save_in_file = undefined;

    file_name = undefined;

    Init = () => {
        console.clear();
        console.log(Lang.DependenciesWarn);
    }

    InstallDependencies = () => {
        sleep(5);
        // InstallingFaker library
        system.execute('python3 -m pip install Faker');
    }

    DataInput = () => {
        console.clear();

        this.amount_of_data = parseInt(console.input(Lang.DataAmount)),
        
        this.save_in_file = console.input('\n' + Lang.SaveInFileQuery),

        this.file_name = this.save_in_file.toLowerCase() == 'y' ?
            console.input('\n' + Lang.FileName)
        :
            0;
        
        console.clear();
    }

    // Using PythonString
    DataOutput = () => pythonString(`
from faker import Faker
from faker.providers import internet

fake = Faker(['it_IT', 'en_US'])

data = []

for x in range(${this.amount_of_data}):

    print(f' * - [{x + 1}]')

    tmp = f'''
 * Name - {fake.name()}
 * Job - {fake.job()}
 * Address - {fake.address().splitlines()[0]}
 * Phone Number - {fake.phone_number()}
 * Email - {fake.email()}
 * Company Email - {fake.company_email()}
 * IPV4 - {fake.ipv4()}
    '''

    data.append(tmp);

    print(tmp)

if '${this.save_in_file.toLowerCase()}' == 'y':
    with open('${this.file_name}', 'a') as file:
        for x in data: file.write(x)

print('Remember drink water!')
`);
}

const Faker = new FakerGenerator();

// <INIT>, Clears the screen and informs about 
// the installation of dependencies for the execution of the script.
Faker.Init();

// We install the dependencies by 
// executing a command in the operating system.
Faker.InstallDependencies();

// We ask the cracker for data, how much data does 
// he want to generate? and Do you want to save to file? 
// If so, its respective name, if it does not exist, it is 
// created, if it exists, new content is added.
Faker.DataInput();

// Using Python Code
Faker.DataOutput();