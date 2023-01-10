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

// Z8 Math
Object.defineProperties(Math.__proto__, {
    'Factorial': {
        value: function(PositiveNumber){
            return PositiveNumber < 0 ? (() => {
                throw new TypeError('Negative numbers are not allowed!');
            })() : PositiveNumber <= 1 ? 1 : PositiveNumber * Factorial(PositiveNumber - 1);
        },
        writable: false
    },

    'Fibonacci': {
        value: function(MaxIteration){
            const Sequence = [1];
            let CurrentValue = 1, PreviousValue = 0, Iterator = 0;
            if(MaxIteration === 1)
                return Sequence;
            while(Iterator < MaxIteration){
                CurrentValue += PreviousValue;
                PreviousValue = CurrentValue - PreviousValue;
                Sequence.push(CurrentValue);
                Iterator += 1;
            }
            return Sequence;
        },
        writable: false
    },

    'PrimeFactors':{
        value: function(Integer){
            let CloneOfInteger = Integer, Factors = [];
            for(let Iterator = 2; Iterator <= Math.sqrt(CloneOfInteger); Iterator += 1)
                while(CloneOfInteger % Iterator === 0){
                    CloneOfInteger /= Iterator;
                    Factors.push(Iterator);
                }
            if(CloneOfInteger !== 1)
                Factors.push(CloneOfInteger);
            return Factors;
        },
        writable: false
    },

    'IsPrime': {
        value: function(Integer){
            const Boundary = Math.floor(Math.sqrt(Integer));
            for(let Iterator = 2; Integer <= Boundary; Iterator++)
                if(Integer % Iterator == 0)
                    return false;
            return Integer >= 2;
        },
        writable: false
    },

    'IsPowerOfTwo': {
        value: function(Number){
            return (Number & (Number - 1)) === 0;
        },
        writable: false
    },

    'DivideByTwo': {
        value: function(Number){
            return Number >> 1;
        },
        writable: false
    },

    'MultiplyByTwo': {
        value: function(Number){
            return Number << 1;
        },
        writable: false
    },

    'IsEven': {
        value: function(Number){
            return (Number & 1) === 0;
        },
        writable: false
    },

    'IsPositive': {
        value: function(Number){
            // Zero is neither a positive nor a negative number
            if(Number === 0)
                return false;
            // The most significant 32nd bit can be used to determine wether
            // the number is positive
            return ((Number >> 31) & 1) == 0;
        },
        writable: false
    },

    'GetReadableUnitSize': {
        value: function(Bytes, UseUnitSI = false, DecimalPlaces = 1){
            const Thresh = UseUnitSI ? 1000 : 1024;
            if(Math.abs(Bytes) < Thresh)
                return Bytes + ' B';
            const Units = UseUnitSI
                ? ['KB', 'MB', 'GB', 'TB', 'PB', 'EB', 'ZB', 'YB']
                : ['KiB', 'MiB', 'GiB', 'PiB', 'EiB', 'ZiB', 'YiB'];
            let Unit = -1;
            const R = 10 ** DecimalPlaces;
            do{
                Bytes /= Thresh;
                ++Unit;
            }while(Math.round(Math.abs(Bytes) * R) / R >= Thresh && Unit < Units.length - 1);
            return Bytes.toFixed(DecimalPlaces) + ' ' + Units[Unit];
        },
        writable: false
    }
});

// Z8 String
Object.defineProperties(String.prototype, {
    'SubStringCount': {
        value: function(SubString){
            let Counter = 0, Iterator = 0;
            while(true){
                const Result = this.indexOf(SubString, Iterator);
                if(Result !== -1)
                    [Counter, Iterator] = [Counter + 1, Result + 1];
                else
                    return Counter;
            }
        },
        writable: false
    },

    'HammingDistance': {
        value: function(StringToCompare){
            if(this.length !== StringToCompare.length)
                throw new Error('Strings must be of the same length');
            let Distance = 0;
            for(let Iterator = 0; Iterator < this.length; Iterator++)
                if(this[Iterator] !== StringToCompare[Iterator])
                    Distance += 1;
            return Distance;
        },
        writable: false
    },

    'RandomFill': {
        value: function(Length = 32, Characters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'){
            let Result = '';
            for(let Iterator = 0; Iterator < Length; Iterator++)
                Result += Characters.charAt(Math.floor(Math.random() * Length));
            return Result;
        },
        writable: false
    },
});

// Z8 Array
Object.defineProperties(Array.prototype, {
    'LinearSearch': {
        value: function(Value){
            for(let Iterator = 0; Iterator < this.length; Iterator++)
                if(this[Iterator] === Value)
                    return Iterator;
            return -1;
        },
        writable: false
    },

    'InterpolationSearch': {
        value: function(Value){
            // Required sorted an sorted array
            let 
                LeftIndex = 0, 
                RightIndex = this.length - 1;
            while(LeftIndex <= RightIndex){
                const
                    RangeDelta = this[RightIndex] - this[LeftIndex],
                    IndexDelta = RightIndex - LeftIndex,
                    ValueDelta = Value - this[LeftIndex];
                if(ValueDelta < 0)
                    return -1;
                if(!RangeDelta)
                    return this[LeftIndex] === Value ? LeftIndex : -1;
                const MiddleIndex = LeftIndex + Math.floor((ValueDelta * IndexDelta) / RangeDelta);       
                if(this[MiddleIndex] === Value)
                    return MiddleIndex;
                if(this[MiddleIndex] < Value)
                    LeftIndex = MiddleIndex + 1;
                else
                    RightIndex = MiddleIndex - 1;         
            }
            return -1;
        },
        writable: false
    },

    'BinarySearch': {
        value: function(Value){
            let Start = 0, End = this.length -1;
            while(Start <= End){
                let Middle = Math.floor((Start + End) / 2);
                if(Value === this[Middle])
                    return Middle;
                else if(Value > this[Middle])
                    Start = Middle + 1;
                else if(Value < this[Middle])
                    End = Middle - 1;
            }
            return -1;
        },
        writable: false
    },

    'Average': {
        value: function(){
            return this.reduce((Accumulator, Value) => Accumulator + Value) / this.length;
        },
        writable: false
    },

    'MaximumValue': {
        value: function(){
            return Math.max(...this);
        },
        writable: false
    },

    'MinimumValue': {
        value: function(){
            return Math.min(...this);
        },
        writable: false
    },

    'InsertionSort': {
        value: function(){
            for(let Iterator = 0; Iterator < this.length; Iterator++)
                for(let SubIterator = Iterator - 1; SubIterator > -1; SubIterator--)
                    if(this[SubIterator + 1] < this[SubIterator])
                        [this[SubIterator + 1], this[SubIterator]] = [this[SubIterator], this[SubIterator + 1]];
            return this;
        },
        writable: false
    },

    'SelectionSort': {
        value: function(){
            let Minimum;
            for(let Iterator = 0; Iterator < this.length; Iterator++){
                Minimum = Iterator;
                for(let SubIterator = Iterator + 1; SubIterator < this.length; SubIterator++)
                    if(this[SubIterator] < this[Minimum])
                        Minimum = SubIterator;
                if(Minimum !== Iterator)
                    [this[Iterator], this[Minimum]] = [this[Minimum], this[Iterator]];
            }
            return this;
        },
        writable: false
    },

    'BubbleSort': {
        value: function(){
            let Break;
            do{
                Break = false;
                for(let Iterator = 0; Iterator < this.length; Iterator++)
                    if(this[Iterator] > this[Iterator + 1]){
                        let Buffer = this[Iterator];
                        this[Iterator] = this[Iterator + 1];
                        this[Iterator + 1] = Buffer;
                        Break = true;
                    }
            }while(Break);
            return this;
        },
        writable: false
    },

    'Shuffle': {
        value: function(){
            let Length = this.length;
            while(Length){
                const Index = Math.floor(Math.random() * Length--);
                [this[Length], this[Index]] = [this[Index], this[Length]];
            }
            return this;
        },

        writable: false
    },
});

// Z8 Cryptography
const CaesarCipher = {
    DEFAULT_ALPHABET: 'abcdefghijklmnopqrstuvwxyz'.split(''),
    GetCipherMap: (Alphabet, Shift) => {
        return Alphabet
          .reduce((CharactersMap, CurrentCharacter, CharacterIndex) => {
            const CharactersMapClone = {...CharactersMap};
            let EncryptedCharacterIndex = (CharacterIndex + Shift) % Alphabet.length;
            if(EncryptedCharacterIndex < 0) 
                EncryptedCharacterIndex += Alphabet.length;
            CharactersMapClone[CurrentCharacter] = Alphabet[EncryptedCharacterIndex];
            return CharactersMapClone;
          }, {});
      },
    Encrypt: (Str, Shift, Alphabet = CaesarCipher.DEFAULT_ALPHABET) => {
        const CipherMap = CaesarCipher.GetCipherMap(Alphabet, Shift);
        return Str
            .toLowerCase()
            .split('')
            .map((Character) => CipherMap[Character] || Character)
            .join('');
    },
    Decrypt: (EncryptedStr, Shift, Alphabet = CaesarCipher.DEFAULT_ALPHABET) => {
        const CipherMap = CaesarCipher.GetCipherMap(Alphabet, -Shift);
        return EncryptedStr
            .toLowerCase()
            .split('')
            .map((Character) => CipherMap[Character] || Character)
            .join('');
    }
};

const Base64 = {
    Encode: (Str) => {
        if(/([^\u0000-\u00ff])/.test(Str))
            throw new Error('Can not base64 encode non-ASCII characters.');
        let
            Digits = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/',
            Cur, Prev, ByteNum, Result = [], Iterator = 0;
        while(Iterator < Str.length){
            Cur = Str.charCodeAt(Iterator);
            ByteNum = Iterator % 3;
            switch(ByteNum){
                case 0:
                    Result.push(Digits.charAt(Cur >> 2));
                    break;
                case 1:
                    Result.push(Digits.charAt((Prev & 3) << 4 | (Cur >> 4)));
                    break;
                case 2:
                    Result.push(Digits.charAt((Prev & 0x0f) << 2 | (Cur >> 6)));
                    Result.push(Digits.charAt(Cur & 0x3ff));
                    break;
            }
            Prev = Cur;
            Iterator++;
        }
        if(ByteNum == 0){
            Result.push(Digits.charAt((Prev & 3) << 4));
            Result.push('==');
        }else if(ByteNum == 1){
            Result.push(Digits.charAt((Prev & 0x0f) << 2));
            Result.push('=');
        }
        return Result.join('');
    },
    Decode: (Str) => {
        Str = Str.replace(/\s/g,'');
        let
            Digits = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/',
            Cur, Prev, DigitNum, Result = [], Iterator = 0;
        Str = Str.replace(/=/g, '');
        while(Iterator < Str.length){
            Cur = Digits.indexOf(Str.charAt(Iterator));
            DigitNum = Iterator % 4;
            switch(DigitNum){
                case 1:
                    Result.push(String.fromCharCode(Prev << 2 | Cur >> 4));
                    break;
                case 2:
                    Result.push(String.fromCharCode((Prev & 0x0f) << 4 | Cur >> 2));
                    break;
                case 3:
                    Result.push(String.fromCharCode((Prev & 3) << 6 | Cur));
                    break;
            }
            Prev = Cur;
            Iterator++;
        }
        return Result.join('');
    }
};

// Z8 Data Structures
class Stack{
    #Items = [];
    Push = (Item) => this.#Items.unshift(Item);
    Pop = () => this.#Items.shift();
    IsEmpty = () => this.#Items.length === 0;
    Clear = () => this.#Items.length = 0;
    Peek = () => this.#Items[0];

    get Length(){
        return this.#Items.length;
    }
};

class Queue{
    #Items = [];
    EnQueue = (Item) => this.#Items.push(Item);
    DeQueue = () => this.#Items.shift();
    Peek = () => this.#Items[0];
    IsEmpty = () => this.#Items.length === 0;
    Clear = () => this.#Items.length = 0;

    get Length(){
        return this.#Items.length;
    }
};

// Z8 Functions
const ParseEnvironmentFile = (Filename, Options = { Comments: false, EmptyLines: false }) => { 
    const Content = FileSystem.QuickReadFile(Filename);
    const EnvironmentObject = {};
    let NewLineCount = 0;
    let CommentsCount = 0;
    Content
        .split('\n')
        .map((Line) => {
            if(Options.Comments && Line.startsWith('#')){
                CommentsCount += 1;
                return [`Comment_${CommentsCount}`, Line];
            }
            if(Line)
                return Line.split('=').map(KeyValue => KeyValue.trim());
            if(Options.EmptyLines){
                NewLineCount += 1;
                return [`EmptyLine_${NewLineCount}_`, ''];
            }
            return [''];
        })
        .filter((Item) => Item.length > 1)
        .forEach((Item) => EnvironmentObject[Item[0]] = Item[1]);
    return EnvironmentObject;
};

const SetTimeout = (Callback, Milliseconds) => Timeout(Milliseconds, 0, Callback);
const SetInterval = (Callback, Milliseconds) => Timeout(0, Milliseconds, Callback);