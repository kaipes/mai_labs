#include <stdio.h>
enum State {Finish=0, DiagDown, MoveUp, MoveDown, MoveMirrorDown, MoveMirrorUp, DiagUp, Start};
enum State nextState(enum State current, unsigned i, unsigned j, unsigned n);