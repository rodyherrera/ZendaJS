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

//TODO: The SendMail function is not fully developed, not all SMTP servers 
//TODO: share the same configuration, for example the login system, there are 
//TODO: cases where this is not required, or they have different login 
//TODO: methods, this function MUST specify the method of login using 
//TODO: <Username@Password>, in future versions these limitations will be corrected.

// We will create a variable with the name <HasError>, this is 
// because the function returns a boolean if there are NO 
// errors, it will return a string with the message in case there 
// is an error, a string is a true value, so if there is an error 
// the return value of this function will be true, otherwise false.
const HasError = SendMail({
    // 'To' parameter specifies the email address 
    // where you want to send the mail.
    To: 'rodolfitjows@gmail.com',
    // 'From' parameter must contain as value the email 
    // address from which the mail will be sent.
    From: 'admin@codewithrodi.com',
    // 'Subject' parameter will contain the Subject of the 
    // mail, where there are the most relevant words when reading it.
    Subject: 'Sending a email from ZendaJS',
    // 'Content' parameter must contain the content of the email 
    // as a value, depending on its content type, it may vary.
    Content: 'Hello world!',
    // 'ContentType' will indicate the type of content that will be 
    // sent to the server, this will be processed in different ways 
    // depending on its type, usually this can be <text/plain> or <text/html>
    ContentType: 'text/plain; charset=UTF-8',
    // 'SMTP' should contain the necessary information to
    // be able to authenticate and connect to the SMTP server.
    SMTP: {
        // 'Hostname' must contain the server address, it can be an 
        // IP or directly the DNS, for example 
        // <smtp.mysmtpserver.com> or <11.22.33.44>
        Hostname: 'codewithrodi.com',
        // 'Port' must contain an integer value that will be the server port.
        Port: 465,
        // 'Username' must contain the email address or username 
        // that will serve to authenticate the SMTP server and allow 
        // sending, for example <noreply@mydomain.com>
        Username: 'admin@codewithrodi.com',
        // 'Password' must contain the password that will serve 
        // to authenticate the user that was previously indicated 
        // in the previous parameter.
        Password: 'rodolfoxd665'
    }
});

// According to the return of the function initially 
// explained, we will show in the terminal if there is 
// any error or the message was sent successfully.
if(HasError)
    Console.Error('An error occurred while trying to send the email.\nError:', HasError);
else
    Console.Success('The email was sent correctly!');