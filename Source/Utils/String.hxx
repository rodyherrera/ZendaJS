/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Utils/String.hxx: File containing methods to facilitate working with Strings.
 *
 * This file contains methods that work and manipulate Strings, whose 
 * methods are used in all of Zenda's anatomy.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static inline string StringToUpper(string String);
static inline string StringToLower(string String);
static string RandomString(unsigned short int Length);
static string StringStartAt(string String, unsigned int Position);
static string StringEndAt(string String, unsigned int Position);
static vector<string> SplitString(const string &str, const string &delim);
static string StringStartEndAt(string String, unsigned int StartPosition, unsigned int EndPosition);

static string RandomString(unsigned short int Length){
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q',
    'r','s','t','u','v','w','x',
    'y','z'};
    string ran = "";
    for (unsigned short int i = 0; i < Length; i++) 
        ran=ran + letters[rand() % 26];
    return ran;
}

static inline string StringToLower(string String){
    transform(String.begin(), String.end(), String.begin(), ::tolower);
    return String;
}

static inline string StringToUpper(string String){
    transform(String.begin(), String.end(), String.begin(), ::toupper);
    return String;
}

static string StringStartAt(string String, unsigned int Position){
    string Buffer;
    while(String[Position])
        Buffer += String[Position], Position++;
    return Buffer;
}

static string StringEndAt(string String, unsigned int Position){
    string Buffer;
    while(String[Position])
        Buffer += String[Position], Position--;
    return Buffer;
}

static string StringStartEndAt(string String, unsigned int StartPosition, unsigned int EndPosition){
    string Buffer;
    while( (String[StartPosition]) && (StartPosition <= EndPosition) )
        Buffer += String[StartPosition], StartPosition++;
    return Buffer;
}

static inline string StringLeftTrim(const string &String, string TrimCharacters = " \n\r\t\f\v"){
	size_t Start = String.find_first_not_of(TrimCharacters);
	return (Start == string::npos) ? "" : String.substr(Start);
}

static inline string StringRightTrim(const string &String, string TrimCharacters = " \n\r\t\f\v"){
	size_t End = String.find_last_not_of(TrimCharacters);
	return (End == string::npos) ? "" : String.substr(0, End + 1);
}

static inline string StringTrim(const string &String, string LeftTrimCharacters = " \n\r\t\f\v", string RightTrimCharacters = " \n\r\t\f\v"){
	return StringRightTrim(StringLeftTrim(String, LeftTrimCharacters), RightTrimCharacters);
}

static vector<string> SplitString(const string &str, const string &delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do{
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(StringTrim(token));
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}