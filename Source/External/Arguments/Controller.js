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

const CurrentWorkingDirectory = System.CurrentWorkingDirectory();
const SplittedCurrentPath = CurrentWorkingDirectory.split('/');
const MaybeJSON = SplittedCurrentPath[SplittedCurrentPath.length - 1];

export const IfJsonFileExistsDoItOr = ({ IfFileExistsDoIt, IfFileDoesntExistsDoIt }) => {
    if(FileSystem.FileExists(MaybeJSON + '.json'))
        IfFileExistsDoIt({
            JsonContent: JSON.parse(FileSystem.QuickReadFile(MaybeJSON + '.json'))
        });
    else
        IfFileDoesntExistsDoIt({
            Directory: MaybeJSON,
            ItemsOfCurrentDirectory: FileSystem.ListDirectory(CurrentWorkingDirectory)
        });
}

export const SafeStringInConsole = (String) => (
    String.length > 60 ? String.slice(0, 60) + '...' : String
);