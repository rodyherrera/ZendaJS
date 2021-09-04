/***
 * Copyright (C) Rodolfo Herrera Hernandez. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root 
 * for full license information.
 *
 * =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
 *
 * Methods/PyTurtle/Methods.hxx: File containing methods for PyTurtle object.
 *
 * Available methods to manipulate and/or interact with the PyTurtle object from JS.
 *
 * For related information - https://github.com/rodiihernandezz/ZendaJS/
 *
 * =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
 ****/

static void PyTurtleWrite(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleForward(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleBackward(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleRight(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleLeft(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleGoTo(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleSetX(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleSetY(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleSetHeading(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleHome(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleCircle(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleDot(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleStamp(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleClearStamps(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleUndo(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleSpeed(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleTowards(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleDistance(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleDegress(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtlePenDown(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtlePenUp(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtlePenSize(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtlePenColor(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleFillColor(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleBeginFill(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleEndFill(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleReset(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleClear(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleShowTurtle(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleHideTurtle(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleShape(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleResizeMode(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleShapeSize(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleShearFactor(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleTilt(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleSetTiltAngle(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleMode(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleShapeTransform(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleBeginPoly(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleEndPoly(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowBackgroundColor(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowBackgroundImage(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowClearScreen(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowResetScreen(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowSize(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowSetWorldCoordinates(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowDelay(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowColorMode(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowTracer(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowUpdate(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowBye(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowExitOnClick(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleWindowTitle(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleExecute(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleClearCodeBuffer(const FunctionCallbackInfo<Value>& Arguments);
static void PyTurtleInitialize(const FunctionCallbackInfo<Value>& Arguments);

string PyTurtleCodeBuffer = "";

static void PyTurtleInitialize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer = R"""(
from sys import exit
try:
    import turtle
    Turtle = turtle.Turtle()
    Screen = turtle.Screen()
    Screen.title('ZendaJS - Python Turtle Integration')
)""";
}

static void PyTurtleForward(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Forward needs to receive a parameter that indicates the distance.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Distance(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.forward(" + string(ToCString(Distance)) + ")";
    }
}

static void PyTurtleBackward(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Backward needs to receive a parameter that indicates the distance.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Distance(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.backward(" + string(ToCString(Distance)) + ")";
    }
}

static void PyTurtleRight(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Right needs to receive a parameter that indicates the angle.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Angle(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.right(" + string(ToCString(Angle)) + ")";
    }
}

static void PyTurtleLeft(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Left needs to receive a parameter that indicates the angle.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Angle(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.left(" + string(ToCString(Angle)) + ")";
    }
}

static void PyTurtleGoTo(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "GoTo needs to receive two parameters where the first is X and the second is Y.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Turtle.goto(" + string(ToCString(X)) + ", " + string(ToCString(Y)) + ")";
    }
}

static void PyTurtleSetX(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "SetX needs to receive a parameter that indicates the X.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.setx(" + string(ToCString(X)) + ")";
    }
}

static void PyTurtleSetY(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "SetY needs to receive a parameter that indicates the Y.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Y(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.sety(" + string(ToCString(Y)) + ")";
    }
}

static void PyTurtleSetHeading(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "SetHeading needs to receive a parameter that indicates the heading.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Heading(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.setheading(" + string(ToCString(Heading)) + ")";
    }
}

static void PyTurtleHome(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.home()";
}

static void PyTurtleCircle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Circle expects to receive at least one of its three parameters which are Radius, Extent, and Steps.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Radius(Arguments.GetIsolate(), Arguments[0]);
        string StrExtent = "None";
        string StrSteps = "None";
        if(!Arguments[1]->IsUndefined()){
            String::Utf8Value Extent(Arguments.GetIsolate(), Arguments[1]);
            StrExtent = string(ToCString(Extent));
        }
        if(!Arguments[2]->IsUndefined()){
            String::Utf8Value Steps(Arguments.GetIsolate(), Arguments[2]);
            StrSteps = string(ToCString(Steps));
        }
        PyTurtleCodeBuffer += "\n    Turtle.circle(" + string(ToCString(Radius)) + ", " + StrExtent + ", " + StrSteps + ")";
    }
}

static void PyTurtleDot(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Dot expects to receive two parameters where the first is the size and the second is the color.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Size(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Color(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Turtle.dot(" + string(ToCString(Size)) + ", " + string(ToCString(Color)) + ")";
    }
}

static void PyTurtleStamp(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.stamp()";
}

static void PyTurtleClearStamps(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "ClearStamps expects to receive a parameter which indicates the clear stamp.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value ClearStamp(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.clearstamps(" + string(ToCString(ClearStamp)) + ")";
    }
}

static void PyTurtleUndo(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.undo()";
}

static void PyTurtleSpeed(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Speed expects to receive a parameter which indicates the speed.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Speed(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.speed(" + string(ToCString(Speed)) + ")";
    }
}

static void PyTurtleTowards(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Towards needs to receive two parameters where the first is X and the second is Y.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Turtle.towards(" + string(ToCString(X)) + ", " + string(ToCString(Y)) + ")";
    }
}

static void PyTurtleDistance(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Distance needs to receive two parameters where the first is X and the second is Y.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{        
        String::Utf8Value X(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Y(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Turtle.distance(" + string(ToCString(X)) + ", " + string(ToCString(Y)) + ")";
    }
}

static void PyTurtleDegress(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Degress expects to receive a parameter which indicates the full circle.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value FullCircle(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.degress(" + string(ToCString(FullCircle)) + ")";
    }
}

static void PyTurtlePenDown(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.pendown()";
}

static void PyTurtlePenUp(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.penup()";
}

static void PyTurtlePenSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "PenSize expects to receive a parameter which indicates the pen size.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value PenSize(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.pensize(" + string(ToCString(PenSize)) + ")";
    }
}

static void PyTurtlePenColor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "PenColor waits at least to receive a parameter indicating its color.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        string Buffer = "\n    Turtle.color(";
        unsigned short int Iterator = 0;
        for(Iterator; Iterator < Arguments.Length(); Iterator++){
            String::Utf8Value Color(Arguments.GetIsolate(), Arguments[Iterator]);
            Buffer += "'" + string(ToCString(Color)) + "'";
            if(Iterator + 1 != Arguments.Length())
                Buffer += ", ";
        }
        Buffer += ")";
        PyTurtleCodeBuffer += Buffer;
    }
}

static void PyTurtleFillColor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "FillColor expects to receive a parameter which indicates the fill color.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value FillColor(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.fillcolor('" + string(ToCString(FillColor)) + "')";
    }
}

static void PyTurtleBeginFill(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.begin_fill()";
}

static void PyTurtleEndFill(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.end_fill()";
}

static void PyTurtleReset(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.reset()";
}

static void PyTurtleClear(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.clear()";
}

static void PyTurtleShowTurtle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.showturtle()";
}

static void PyTurtleHideTurtle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.hideturtle()";
}

static void PyTurtleShape(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Shape expects to receive a parameter which indicates the shape.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Shape(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.shape('" + string(ToCString(Shape)) + "')";
    }
}

static void PyTurtleResizeMode(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "ResizeMode expects to receive a parameter which indicates the resize mode.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value ResizeMode(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.resizemode('" + string(ToCString(ResizeMode)) + "')";
    }
}

static void PyTurtleShapeSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "ShapeSize expects to receive at least one parameter of 3 parameters which are StretchWid, StretchLength and Outline.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value StretchWid(Arguments.GetIsolate(), Arguments[0]);
        string StrStretchLength = "None";
        string StrOutline = "None";
        if(!Arguments[1]->IsUndefined()){
            String::Utf8Value StretchLength(Arguments.GetIsolate(), Arguments[1]);
            StrStretchLength = string(ToCString(StretchLength));
        }
        if(!Arguments[2]->IsUndefined()){
            String::Utf8Value Outline(Arguments.GetIsolate(), Arguments[2]);
            StrOutline = string(ToCString(Outline));
        }
        PyTurtleCodeBuffer += "\n    Turtle.shapesize(" + string(ToCString(StretchWid)) + ", " + StrStretchLength + ", " + StrOutline + ")";
    }
}

static void PyTurtleShearFactor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "ShearFactor expects to receive a parameter which indicates the shear factor.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value ShearFactor(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.shearfactor(" + string(ToCString(ShearFactor)) + ")";
    }
}

static void PyTurtleTilt(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Tilt expects to receive a parameter which indicates the tilt.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Tilt(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.tilt(" + string(ToCString(Tilt)) + ")";
    }
}

static void PyTurtleSetTiltAngle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "TiltAngle expects to receive a parameter which indicates the tilt angle.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value TiltAngle(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.settiltangle(" + string(ToCString(TiltAngle)) + ")";
    }
}

static void PyTurtleMode(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "TurtleMode expects to receive a parameter which indicates the mode.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Mode(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Turtle.mode(" + string(ToCString(Mode)) + ")";
    }
}

static void PyTurtleShapeTransform(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "ShapeTransform expects to receive at least 1 of its 4 parameters which are T11, T12, T21 and T22.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value T11(Arguments.GetIsolate(), Arguments[0]);
        string StrT12 = "None";
        string StrT21 = "None";
        string StrT22 = "None";
        if(!Arguments[1]->IsUndefined()){
            String::Utf8Value T12(Arguments.GetIsolate(), Arguments[1]);
            StrT12 = string(ToCString(T12));
        }
        if(!Arguments[2]->IsUndefined()){
            String::Utf8Value T21(Arguments.GetIsolate(), Arguments[2]);
            StrT21 = string(ToCString(T21));
        }
        if(!Arguments[3]->IsUndefined()){
            String::Utf8Value T22(Arguments.GetIsolate(), Arguments[3]);
            StrT22 = string(ToCString(T22));
        }
        PyTurtleCodeBuffer += "\n    Turtle.shapetransform(" + string(ToCString(T11)) + ", " + StrT12 + ", " + StrT21 + ", " + StrT12 + ")";   
    }
}

static void PyTurtleBeginPoly(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.begin_poly()";
}

static void PyTurtleEndPoly(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Turtle.end_poly()";
}

static void PyTurtleWindowBackgroundColor(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowBackgroundColor expects to receive a parameter which indicates the background of the window.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value BackgroundColor(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Screen.bgcolor('" + string(ToCString(BackgroundColor)) + "')";
    }
}

static void PyTurtleWrite(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "Write expects to receive 1 of its 2 parameters where the first the text and the second are the write arguments.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Text(Arguments.GetIsolate(), Arguments[0]);
        string StrWriteArguments = "None";
        if(!Arguments[1]->IsUndefined()){
            String::Utf8Value WriteArguments(Arguments.GetIsolate(), Arguments[1]);
            StrWriteArguments = string(ToCString(WriteArguments));
        }
        PyTurtleCodeBuffer += "\n    Turtle.write('" + string(ToCString(Text)) + "', '" + StrWriteArguments + "')";
    }
}

static void PyTurtleWindowBackgroundImage(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowBackgroundImage expects to receive a parameter which indicates the background image of the window.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value BackgroundImageLocation(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Screen.bgpic('" + string(ToCString(BackgroundImageLocation)) + "')";   
    }
}

static void PyTurtleWindowClearScreen(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Screen.clearscreen()";
}

static void PyTurtleWindowResetScreen(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Screen.resetscreen()";
}

static void PyTurtleWindowSize(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) )
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowSize expects to receive two parameters which are Width and Height.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Width(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Height(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Screen.screensize(" + string(ToCString(Width)) + ", " + string(ToCString(Height)) + ")";   
    }
}

static void PyTurtleWindowSetWorldCoordinates(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if( (Arguments[0]->IsUndefined()) || (Arguments[1]->IsUndefined()) || (Arguments[2]->IsUndefined()) || (Arguments[3]->IsUndefined()))
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowSetWorldCoordinates expects to receive 4 parameters where the first is LLX, the second is LLY, the third is URX and the fourth is URY.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value LLX(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value LLY(Arguments.GetIsolate(), Arguments[1]);
        String::Utf8Value URX(Arguments.GetIsolate(), Arguments[2]);
        String::Utf8Value URY(Arguments.GetIsolate(), Arguments[3]);
        PyTurtleCodeBuffer += "\n    Screen.setworldcoordinates(" + string(ToCString(LLX)) + ", " + string(ToCString(LLY)) + ", " + string(ToCString(URX)) + ", " + string(ToCString(URY)) + ")";
    }
}

static void PyTurtleWindowDelay(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowBackgroundImage expects to receive a parameter which indicates the window delay.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Delay(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Screen.delay(" + string(ToCString(Delay)) + ")";
    }
}

static void PyTurtleWindowColorMode(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowColorMode expects to receive a parameter which indicates the window color mode.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value ColorMode(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Screen.colormode(" + string(ToCString(ColorMode)) + ")";
    }
}

static void PyTurtleWindowTracer(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowTracer expects to receive two parameters where the first indicates the Tracer and the second the Delay.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Tracer(Arguments.GetIsolate(), Arguments[0]);
        String::Utf8Value Delay(Arguments.GetIsolate(), Arguments[1]);
        PyTurtleCodeBuffer += "\n    Screen.tracer(" + string(ToCString(Tracer)) + ", " + string(ToCString(Delay)) + ")";   
    }
}

static void PyTurtleWindowUpdate(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Screen.update()";
}

static void PyTurtleWindowBye(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Screen.bye()";
}

static void PyTurtleWindowExitOnClick(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += "\n    Screen.exitonclick()";
}

static void PyTurtleWindowTitle(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    if(Arguments[0]->IsUndefined())
        Arguments.GetIsolate()->ThrowException(
            String::NewFromUtf8(
                Arguments.GetIsolate(),
                "WindowTitle expects to receive a parameter which indicates the window title.",
                NewStringType::kNormal
            ).ToLocalChecked()
        );
    else{
        String::Utf8Value Title(Arguments.GetIsolate(), Arguments[0]);
        PyTurtleCodeBuffer += "\n    Screen.title('" + string(ToCString(Title)) + "')";
    }
}

static void PyTurtleClearCodeBuffer(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleInitialize(Arguments);
}

static void PyTurtleExecute(const FunctionCallbackInfo<Value>& Arguments){
    HandleScope Scope(Arguments.GetIsolate());
    PyTurtleCodeBuffer += R"""(
except KeyboardInterrupt:
    print('\n')
    exit()
except ModuleNotFoundError:
    print('Please run "Zenda install-it"')
    exit()
except Exception as Error:
    print('Error <PyTurtle>.')
    print()
    print(Error)
    )""";
    Py_Initialize();
        PyRun_SimpleString(PyTurtleCodeBuffer.c_str());
    Py_Finalize();
    PyTurtleInitialize(Arguments);
}