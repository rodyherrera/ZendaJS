// Showing all the arguments with which the file was called.
Console.Log(
    System.Arguments()
);

// For example, if you...
// ./Zenda examples/arguments.js argument_one argument_two --argument_three....
// system.arguments() = [examples/arguments.js, argument_one, argument_two, --arghument_three]