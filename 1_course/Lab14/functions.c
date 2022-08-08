#include <stdio.h>
#include "library.h"
enum State nextState(enum State current, unsigned i, unsigned j, unsigned n)
{
    enum State newState;
    switch(current){

        case Start:
        {
            if (i==0 && n!=1) {

                newState = DiagDown;

            } else {

                newState = Finish;
            }
            break;
        }

        case DiagDown:
        {   
            if (j==n-1 && i!=0) {

                newState = MoveUp;

            } else if (i==n-1 && j!=n-1) {

                newState = MoveMirrorUp;
            } else {

                newState = DiagDown;

            }
            break;
        }
        case DiagUp:
        {
            if (j==0 && i!=n-1){

                newState = MoveDown;

            } else if (i==0){

                newState = MoveMirrorDown;

            } else {

                newState = DiagUp;
            }
            break;
        }
        case MoveDown:
        {   
            if ((i==n-1 && j==0)||(i==0)){

                newState = MoveMirrorUp;

            } else if (j==0 && i!=n-1) {
                newState = DiagDown;
            }
            break;
        }
        case MoveUp:
        {
            if (i==0){

                newState = MoveMirrorDown;

            } else if (j==n-1){

                newState = DiagUp;
            }
            break;
        }
        case MoveMirrorUp:
        {   
            if  (i==0 && j!=n-1){

                newState = DiagDown;

            } else {

                newState = Finish;

            }
            break;
        }
        case MoveMirrorDown:
        {   
            if (i==n-1 && j!=0){

                newState = DiagUp;

            } else {
                newState = Finish;
            }
            break;
        }
    }
    return newState;
}