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

namespace Zenda::JavaScript::Objects::PyTurtle{
    static inline void Initialize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Forward(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Backward(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Right(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Left(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void GoTo(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetX(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetY(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetHeading(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Home(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Circle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Dot(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Stamp(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ClearStamps(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Undo(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Speed(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Towards(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Distance(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Degress(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void PenDown(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void PenUp(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void PenSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void PenColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void FillColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void BeginFill(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void EndFill(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Reset(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Clear(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ShowTurtle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void HideTurtle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Shape(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ResizeMode(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ShapeSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ShearFactor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Tilt(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void SetTiltAngle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void Mode(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void ShapeTransform(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void BeginPoly(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void EndPoly(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Write(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowBackgroundColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowBackgroundImage(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowClearScreen(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowResetScreen(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowSetWorldCoordinates(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowDelay(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowColorMode(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowTracer(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowUpdate(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowBye(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowExitOnClick(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void WindowTitle(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static inline void ClearCodeBuffer(const v8::FunctionCallbackInfo<v8::Value>& Arguments);
    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments);

    std::string CodeBuffer = "";

    static inline void Initialize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer = R"""(
    from sys import exit
    try:
        import turtle
        Turtle = turtle.Turtle()
        Screen = turtle.Screen()
        Screen.title('ZendaJS - Python Turtle Integration')
    )""";
    }

    static inline void Forward(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Forward needs to receive a parameter that indicates the distance.");
        else{
            v8::String::Utf8Value Distance(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.forward(" + std::string(std::string(*Distance)) + ")";
        }
    }

    static inline void Backward(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Backward needs to receive a parameter that indicates the distance.");
        else{
            v8::String::Utf8Value Distance(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.backward(" + std::string(std::string(*Distance)) + ")";
        }
    }

    static inline void Right(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Right needs to receive a parameter that indicates the angle.");
        else{
            v8::String::Utf8Value Angle(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.right(" + std::string(std::string(*Angle)) + ")";
        }
    }

    static inline void Left(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Left needs to receive a parameter that indicates the angle.");
        else{
            v8::String::Utf8Value Angle(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.left(" + std::string(std::string(*Angle)) + ")";
        }
    }

    static inline void GoTo(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "GoTo needs to receive two parameters where the first is X and the second is Y.");
        else{
            v8::String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Turtle.goto(" + std::string(std::string(*X)) + ", " + std::string(std::string(*Y)) + ")";
        }
    }

    static inline void SetX(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "SetX needs to receive a parameter that indicates the X.");
        else{
            v8::String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.setx(" + std::string(std::string(*X)) + ")";
        }
    }

    static inline void SetY(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "SetY needs to receive a parameter that indicates the Y.");
        else{
            v8::String::Utf8Value Y(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.sety(" + std::string(std::string(*Y)) + ")";
        }
    }

    static inline void SetHeading(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "SetHeading needs to receive a parameter that indicates the heading.");
        else{
            v8::String::Utf8Value Heading(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.setheading(" + std::string(std::string(*Heading)) + ")";
        }
    }

    static inline void Home(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.home()";
    }

    static void Circle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Circle expects to receive at least one of its three parameters which are Radius, Extent, and Steps.");
        else{
            v8::String::Utf8Value Radius(Arguments.GetIsolate(), Arguments[0]);
            std::string StrExtent = "None", StrSteps = "None";
            if(!Arguments[1]->IsUndefined()){
                v8::String::Utf8Value Extent(Arguments.GetIsolate(), Arguments[1]);
                StrExtent = std::string(std::string(*Extent));
            }
            if(!Arguments[2]->IsUndefined()){
                v8::String::Utf8Value Steps(Arguments.GetIsolate(), Arguments[2]);
                StrSteps = std::string(std::string(*Steps));
            }
            CodeBuffer += "\n    Turtle.circle(" + std::string(std::string(*Radius)) + ", " + StrExtent + ", " + StrSteps + ")";
        }
    }

    static inline void Dot(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Dot expects to receive two parameters where the first is the size and the second is the color.");
        else{
            v8::String::Utf8Value Size(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Color(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Turtle.dot(" + std::string(std::string(*Size)) + ", " + std::string(std::string(*Color)) + ")";
        }
    }

    static inline void Stamp(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.stamp()";
    }

    static inline void ClearStamps(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "ClearStamps expects to receive a parameter which indicates the clear stamp.");
        else{
            v8::String::Utf8Value ClearStamp(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.clearstamps(" + std::string(std::string(*ClearStamp)) + ")";
        }
    }

    static inline void Undo(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.undo()";
    }

    static inline void Speed(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Speed expects to receive a parameter which indicates the speed.");
        else{
            v8::String::Utf8Value Speed(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.speed(" + std::string(std::string(*Speed)) + ")";
        }
    }

    static inline void Towards(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Towards needs to receive two parameters where the first is X and the second is Y.");
        else{
            v8::String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Turtle.towards(" + std::string(std::string(*X)) + ", " + std::string(std::string(*Y)) + ")";
        }
    }

    static inline void Distance(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Distance needs to receive two parameters where the first is X and the second is Y.");
        else{        
            v8::String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Turtle.distance(" + std::string(std::string(*X)) + ", " + std::string(std::string(*Y)) + ")";
        }
    }

    static inline void Degress(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Degress expects to receive a parameter which indicates the full circle.");
        else{
            v8::String::Utf8Value FullCircle(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.degress(" + std::string(std::string(*FullCircle)) + ")";
        }
    }

    static inline void PenDown(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.pendown()";
    }

    static inline void PenUp(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.penup()";
    }

    static inline void PenSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "PenSize expects to receive a parameter which indicates the pen size.");
        else{
            v8::String::Utf8Value PenSize(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.pensize(" + std::string(std::string(*PenSize)) + ")";
        }
    }

    static inline void PenColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "PenColor waits at least to receive a parameter indicating its color.");
        else{
            std::string Buffer = "\n    Turtle.color(";
            for(unsigned short int Iterator = 0; Iterator < Arguments.Length(); Iterator++){
                v8::String::Utf8Value Color(Arguments.GetIsolate(), Arguments[Iterator]);
                Buffer += "'" + std::string(std::string(*Color)) + "'";
                if(Iterator + 1 != Arguments.Length())
                    Buffer += ", ";
            }
            Buffer += ")";
            CodeBuffer += Buffer;
        }
    }

    static inline void FillColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "FillColor expects to receive a parameter which indicates the fill color.");
        else{
            v8::String::Utf8Value FillColor(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.fillcolor('" + std::string(std::string(*FillColor)) + "')";
        }
    }

    static inline void BeginFill(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.begin_fill()";
    }

    static inline void EndFill(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.end_fill()";
    }

    static inline void Reset(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.reset()";
    }

    static inline void Clear(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.clear()";
    }

    static inline void ShowTurtle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.showturtle()";
    }

    static inline void HideTurtle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.hideturtle()";
    }

    static inline void Shape(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Shape expects to receive a parameter which indicates the shape.");
        else{
            v8::String::Utf8Value Shape(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.shape('" + std::string(std::string(*Shape)) + "')";
        }
    }

    static inline void ResizeMode(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "ResizeMode expects to receive a parameter which indicates the resize mode.");
        else{
            v8::String::Utf8Value ResizeMode(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.resizemode('" + std::string(std::string(*ResizeMode)) + "')";
        }
    }

    static void ShapeSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "ShapeSize expects to receive at least one parameter of 3 parameters which are StretchWid, StretchLength and Outline.");
        else{
            v8::String::Utf8Value StretchWid(Arguments.GetIsolate(), Arguments[0]);
            std::string StrStretchLength = "None", StrOutline = "None";
            if(!Arguments[1]->IsUndefined()){
                v8::String::Utf8Value StretchLength(Arguments.GetIsolate(), Arguments[1]);
                StrStretchLength = std::string(std::string(*StretchLength));
            }
            if(!Arguments[2]->IsUndefined()){
                v8::String::Utf8Value Outline(Arguments.GetIsolate(), Arguments[2]);
                StrOutline = std::string(std::string(*Outline));
            }
            CodeBuffer += "\n    Turtle.shapesize(" + std::string(std::string(*StretchWid)) + ", " + StrStretchLength + ", " + StrOutline + ")";
        }
    }

    static inline void ShearFactor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "ShearFactor expects to receive a parameter which indicates the shear factor.");
        else{
            v8::String::Utf8Value ShearFactor(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.shearfactor(" + std::string(std::string(*ShearFactor)) + ")";
        }
    }

    static inline void Tilt(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Tilt expects to receive a parameter which indicates the tilt.");
        else{
            v8::String::Utf8Value Tilt(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.tilt(" + std::string(std::string(*Tilt)) + ")";
        }
    }

    static inline void SetTiltAngle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "TiltAngle expects to receive a parameter which indicates the tilt angle.");
        else{
            v8::String::Utf8Value TiltAngle(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.settiltangle(" + std::string(std::string(*TiltAngle)) + ")";
        }
    }

    static inline void Mode(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "TurtleMode expects to receive a parameter which indicates the mode.");
        else{
            v8::String::Utf8Value Mode(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Turtle.mode(" + std::string(std::string(*Mode)) + ")";
        }
    }

    static void ShapeTransform(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "ShapeTransform expects to receive at least 1 of its 4 parameters which are T11, T12, T21 and T22.");
        else{
            v8::String::Utf8Value T11(Arguments.GetIsolate(), Arguments[0]);
            std::string StrT12 = "None", StrT21 = "None", StrT22 = "None";
            if(!Arguments[1]->IsUndefined()){
                v8::String::Utf8Value T12(Arguments.GetIsolate(), Arguments[1]);
                StrT12 = std::string(std::string(*T12));
            }
            if(!Arguments[2]->IsUndefined()){
                v8::String::Utf8Value T21(Arguments.GetIsolate(), Arguments[2]);
                StrT21 = std::string(std::string(*T21));
            }
            if(!Arguments[3]->IsUndefined()){
                v8::String::Utf8Value T22(Arguments.GetIsolate(), Arguments[3]);
                StrT22 = std::string(std::string(*T22));
            }
            CodeBuffer += "\n    Turtle.shapetransform(" + std::string(std::string(*T11)) + ", " + StrT12 + ", " + StrT21 + ", " + StrT12 + ")";   
        }
    }

    static inline void BeginPoly(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.begin_poly()";
    }

    static inline void EndPoly(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Turtle.end_poly()";
    }

    static inline void WindowBackgroundColor(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowBackgroundColor expects to receive a parameter which indicates the background of the window.");
        else{
            v8::String::Utf8Value BackgroundColor(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Screen.bgcolor('" + std::string(std::string(*BackgroundColor)) + "')";
        }
    }

    static void Write(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "Write expects to receive 1 of its 2 parameters where the first the text and the second are the write arguments.");
        else{
            v8::String::Utf8Value Text(Arguments.GetIsolate(), Arguments[0]);
            std::string StrWriteArguments = "None";
            if(!Arguments[1]->IsUndefined()){
                v8::String::Utf8Value WriteArguments(Arguments.GetIsolate(), Arguments[1]);
                StrWriteArguments = std::string(std::string(*WriteArguments));
            }
            CodeBuffer += "\n    Turtle.write('" + std::string(std::string(*Text)) + "', '" + StrWriteArguments + "')";
        }
    }

    static inline void WindowBackgroundImage(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowBackgroundImage expects to receive a parameter which indicates the background image of the window.");
        else{
            v8::String::Utf8Value BackgroundImageLocation(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Screen.bgpic('" + std::string(std::string(*BackgroundImageLocation)) + "')";   
        }
    }

    static inline void WindowClearScreen(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Screen.clearscreen()";
    }

    static inline void WindowResetScreen(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Screen.resetscreen()";
    }

    static inline void WindowSize(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowSize expects to receive two parameters which are Width and Height.");
        else{
            v8::String::Utf8Value Width(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Height(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Screen.screensize(" + std::string(std::string(*Width)) + ", " + std::string(std::string(*Height)) + ")";   
        }
    }

    static inline void WindowSetWorldCoordinates(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) || (Arguments[2]->IsUndefined()) || (Arguments[3]->IsUndefined()))
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowSetWorldCoordinates expects to receive 4 parameters where the first is LLX, the second is LLY, the third is URX and the fourth is URY.");
        else{
            v8::String::Utf8Value LLX(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value LLY(Arguments.GetIsolate(), Arguments[1]);
            v8::String::Utf8Value URX(Arguments.GetIsolate(), Arguments[2]);
            v8::String::Utf8Value URY(Arguments.GetIsolate(), Arguments[3]);
            CodeBuffer += "\n    Screen.setworldcoordinates(" + std::string(std::string(*LLX)) + ", " + std::string(std::string(*LLY)) + ", " + std::string(std::string(*URX)) + ", " + std::string(std::string(*URY)) + ")";
        }
    }

    static inline void WindowDelay(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowBackgroundImage expects to receive a parameter which indicates the window delay.");
        else{
            v8::String::Utf8Value Delay(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Screen.delay(" + std::string(std::string(*Delay)) + ")";
        }
    }

    static inline void WindowColorMode(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowColorMode expects to receive a parameter which indicates the window color mode.");
        else{
            v8::String::Utf8Value ColorMode(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Screen.colormode(" + std::string(std::string(*ColorMode)) + ")";
        }
    }

    static inline void WindowTracer(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowTracer expects to receive two parameters where the first indicates the Tracer and the second the Delay.");
        else{
            v8::String::Utf8Value Tracer(Arguments.GetIsolate(), Arguments[0]);
            v8::String::Utf8Value Delay(Arguments.GetIsolate(), Arguments[1]);
            CodeBuffer += "\n    Screen.tracer(" + std::string(std::string(*Tracer)) + ", " + std::string(std::string(*Delay)) + ")";   
        }
    }

    static inline void WindowUpdate(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Screen.update()";
    }

    static inline void WindowBye(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Screen.bye()";
    }

    static inline void WindowExitOnClick(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += "\n    Screen.exitonclick()";
    }

    static inline void WindowTitle(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        if(Arguments[0]->IsUndefined())
            Zenda::Shortcuts::V8Exception(Arguments.GetIsolate(), "WindowTitle expects to receive a parameter which indicates the window title.");
        else{
            v8::String::Utf8Value Title(Arguments.GetIsolate(), Arguments[0]);
            CodeBuffer += "\n    Screen.title('" + std::string(std::string(*Title)) + "')";
        }
    }

    static inline void ClearCodeBuffer(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        Initialize(Arguments);
    }

    static void Execute(const v8::FunctionCallbackInfo<v8::Value>& Arguments){
        v8::HandleScope Scope(Arguments.GetIsolate());
        CodeBuffer += R"""(
    except KeyboardInterrupt:
        print('\n')
        exit()
    except ModuleNotFoundError:
        print('Please run "python3 Helper.py --runtime.dependencies" in the source code directory')
        exit()
    except Exception as Error:
        print('Error <>.')
        print()
        print(Error)
        )""";
        Py_Initialize();
            PyRun_SimpleString(CodeBuffer.c_str());
        Py_Finalize();
        Initialize(Arguments);
    }
};
