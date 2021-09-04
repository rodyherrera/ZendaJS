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

var FinalFilesLocations = [];

const 
    kExamplesFolderLocation = System.SourceCodeLocation() + '/Examples/',

    ListDetectedFiles = () => {
        Console.Log(' * Files')
        FinalFilesLocations.map((kFile, kFileIndex) => {
            Console.Log(`
 - [${kFileIndex + 1}] - ${SafeFileLength(kFile)}
   => <${FileSystem.QuickFileSize(kFile)} Bytes>
   => <${FileSystem.CountLines(kFile)} Lines of code>
            `);
        })
    },

    DetectExamplesFilesLocation = (Path = kExamplesFolderLocation, DirDecoration = '') => {
        FileSystem.ListDirectory(Path).forEach((File) => {
            const kAbsolutePath = Path + File;
            if(FileSystem.IsDirectory(kAbsolutePath)){
                Console.Warning(`\n * Directory Detected <${File}>\n`);
                Console.Information(` /> Reading directory content to add to the queue.`);
                DetectExamplesFilesLocation(kAbsolutePath, File);
                Console.Success(` /: Directory <${File}> content added to queque!`);
            }else{
                if(File.endsWith('js')){
                    File = DirDecoration + File;
                    Console.Information(`\n * File Decteted <${File}>`);
                    FinalFilesLocations.push(kAbsolutePath);
                    Console.Success(` /: File <${File}> added to queque!`);
                }
            }
            Sleep(1000);
        });
        Console.Clear();
    },

    ExecuteAllDetectedFiles = () => {
        FinalFilesLocations.forEach((File) => {
            Console.Clear();
            Console.Log(` /> Executing ${SafeFileLength(File)} \n`);
            System.Execute(`Zenda run ${File}`);
            Console.Information(`\n [${SafeFileLength(File)}] - Finished.`)
            Sleep(3000);
        });
    },

    SafeFileLength = (File) => {
        return '...' + File.slice(File.length / 2, File.length);
    };

Console.Clear();

Console.Log(
` == DevTool <Run Examples Files> ==

 * Next, all the sample files will be executed.
   - This is useful because you can check 
   - if something is failing, that is, thanks 
   - to this command it is easy to detect 
   - bugs in the commands that Zenda has, this 
   - since the examples folder includes files executing 
   - each of the functions that Zenda has, of So 
   - if something causes an error, it means 
   - that something is wrong and it has to be corrected.

 * For whom?
   - This tool is aimed at developers who are experimenting
   - with the V8 engine and are improving / practicing 
   - their skills with the engine, because they can 
   - create the files they want and modify them 
   - and then run these "Tests" and verify that 
   - everything is fine. This saves you from running 
   - each file one by one to verify that everything is fine.

 /> Detection of example files in the next 7 seconds.
`)

Sleep(7000);

Console.Clear();

Console.Information(' * Detecting example files...');

DetectExamplesFilesLocation();

Console.Success(`
 * The detection of the example files has finished.
 /> Showing detected files:
`)

Console.Success(` * Running files in the next 7 seconds...`);

Sleep(7000);

Console.Log(' * Running files...');

ExecuteAllDetectedFiles();

ListDetectedFiles();