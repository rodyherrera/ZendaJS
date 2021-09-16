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

export const Project = {
    JsonAnatomy: {
        Project: {
            Name: '',
            Version: '1.0.0',
            Description: '',
            Website: '',
            CreationDate: new Date()
        },
    
        Author: {
            Name: '',
            Email: '',
            Website: ''
        },
    
        Commands: {
            Start: 'Zenda run Index.js'
        }
    },

    CreateInCurrentDirectory: () => (
        FileSystem.CreateFolder(Project.JsonAnatomy.Project.Name)
    ),

    CreateFolderInside: (FolderName) => (
        FileSystem.CreateFolder(`${Project.JsonAnatomy.Project.Name}/${FolderName}`)
    ),

    CreateFileInside: (File) => (
        FileSystem.CreateFile(`${Project.JsonAnatomy.Project.Name}/${File}`)
    ),

    WriteFileInside: (File, Content) => (
        FileSystem.QuickRewriteFile(`${Project.JsonAnatomy.Project.Name}/${File}`, Content)
    ),

    SetValueToEmptyJsonAnatomyValues: () => {
        Object.keys(Project.JsonAnatomy).forEach((Key) => {
            Object.keys(Project.JsonAnatomy[Key]).forEach((Value) => {
                if(Project.JsonAnatomy[Key][Value].length == 0)
                    Project.JsonAnatomy[Key][Value] = `${Value} of ${Key} is empty.`;
            });
        });
    },

    InitializeProjectPackages: () => {
        FileSystem.Copy(`${System.SourceCodeLocation()}/Source/External/Project/Packages/`, `${Project.JsonAnatomy.Project.Name}/Packages/`);
    },

    LoadJson: () => (
        FileSystem.QuickRewriteFile(
            `${Project.JsonAnatomy.Project.Name}/${Project.JsonAnatomy.Project.Name}.json`, 
            JSON.stringify(Project.JsonAnatomy, null, '\t')
        )
    )
};