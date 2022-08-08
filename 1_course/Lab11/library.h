enum State {Start=0,FirstDigit,SecondDigit,EndUnNum,Letter};
enum State prog(enum State currentState,char currentSymbol);
void conclusion(char c,char d);