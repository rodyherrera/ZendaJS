// Using native function of Zenda
var OperativeSystem = system.platform();

console.log(OperativeSystem);

// Using sleep for wait and execute instructions after wait
console.log('Showing network interface in next 5 seconds...');
sleep(5);

// Executin command by OS
if(OperativeSystem.startsWith('WIN')){

    // Running command
    system.exec('ipconfig');

}else{

    // If not OS == WIN(Windows), is probably derived from UNIX.

    // Ipconfig for UNIX OS == ifconfig

    system.execute('ifconfig');

}