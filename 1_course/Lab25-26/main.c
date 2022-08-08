#include "queue.h"
int main(){
    struct Queue queue;
    init(&queue);
    char symbol;
    int number;
    while ((symbol = getchar()) != EOF){
		switch (symbol){
        case '+':
            symbol = getchar();
			scanf("%d", &number);
            struct Token element;
            element.value= number;
			push_back(&queue, element);
            break;
		case '-':
			pop_front(&queue);
			break;
        case '?':
            isempty(&queue);
            break;
        case '#':
            procedure(&queue);
            break;
        case 'p':
            printqueue(&queue);
            break;
        case 'f':
            bubblesort(&queue);
            break;
        getchar();
        }
    }
    free(queue.nodes);
}