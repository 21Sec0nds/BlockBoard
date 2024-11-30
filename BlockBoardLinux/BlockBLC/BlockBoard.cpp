#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

using namespace std;

Display* display;

char RandomKey;
char lastKeyPressed;
char RandomNum;
int ExitCount = 0;

int WindowX(){
    Screen* screen = DefaultScreenOfDisplay(display);
    return screen->width;
}

int WindowY(){
    Screen* screen = DefaultScreenOfDisplay(display);
    return screen->height;
}


void BlockMouseMs(){
    while(ExitCount < 2){
        XWarpPointer(display,None,DefaultRootWindow(display), 0,0,0,0,WindowX() / 2,WindowY() / 2);
        XFlush(display);
        this_thread::sleep_for(chrono::milliseconds(2));
    }
}

void CaptureKeyboard(){
    Window root = DefaultRootWindow(display);
    XEvent event;
    XGrabKeyboard(display,root,True,GrabModeAsync,GrabModeAsync,CurrentTime);

    while(ExitCount < 2){
        XNextEvent(display, &event);
        if(event.type == KeyPress){
            char buffer[32];
            KeySym keysym;
            XLookupString(&event.xkey,buffer,sizeof(buffer),&keysym,NULL);
            lastKeyPressed = buffer[0];
            cout << lastKeyPressed << "pressed Down" << endl;

            if (lastKeyPressed == RandomKey || lastKeyPressed == RandomNum){
                ExitCount++;
            }else
            {
                break;
            }
            
        }
    }
    XUngrabKeyboard(display,CurrentTime);
}

int main(){

    srand(static_cast<unsigned int>(time(0)));
    display = XOpenDisplay(NULL);

    if(!display){
        cerr << "Unable to open X display"<< endl;
        return 1;
    }

    thread mouserThread(BlockMouseMs);
    mouserThread.detach();

    const string Alphabet[26] = {
        "Alfa", "Bravo", "Charlie", "Delta", "Echo", "Foxtrot", "Golf", "Hotel", "India", "Juliett",
        "Kilo", "Lima", "Mike", "November", "Oscar", "Papa", "Quebec", "Romeo", "Sierra", "Tango", 
        "Uniform", "Victor", "Whiskey", "X-ray", "Yankee", "Zulu"
    };


    const char KeyCharArray[26] ={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

    const char NumArray[10] = {'1','2','3','4','5','6','7','8','9','0'};

    RandomNum = NumArray[rand() % 10];
    int SameRand = rand() % 26;
    RandomKey = KeyCharArray[SameRand];

    cout << "Your Key:" <<
    RandomKey << endl <<
    "With next number:" <<
    RandomNum << endl <<
    "Key word:" <<
    Alphabet[SameRand] << endl
    << RandomKey <<
    RandomNum << endl;

    CaptureKeyboard();

    XCloseDisplay(display);
    return 0;
}