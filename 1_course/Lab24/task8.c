#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Token {
    unsigned type; 
    unsigned value;
    char operation;
};
struct Stack {
    struct Token* nodes;
    unsigned capacity;
    unsigned size;
};
struct Node {
    struct Token element;
    struct Node* right;
    struct Node* left;
};
struct Tree {
    struct Node* root;
};

unsigned f = 0;
//Stack
void init(struct Stack* stack){
    stack->capacity = 2;
    stack->size = 0;
    stack->nodes = (struct Token*)malloc(sizeof(struct Token)*stack->capacity);
};
void push_back(struct Stack* stack, struct Token element){
    if (stack->size == stack->capacity){
        stack->capacity *=2;
        stack->nodes = (struct Token*)realloc(stack->nodes,sizeof(struct Token)*stack->capacity);
    }
    stack->nodes[stack->size++] = element;
}
struct Token pop(struct Stack* stack){
    if (!stack->size){
        struct Token tok;
        return tok;
    }
    return stack->nodes[--stack->size];
}
int peek(struct Stack* stack) {
    if (stack->size == 0) {
        return -1;
    } else if (stack->nodes->type == 1) {
        return stack->nodes[stack->size - 1].value;
    } else if ((stack->nodes->type == 2)||(stack->nodes->type == 2)) {
        return stack->nodes[stack->size - 1].operation;
    } 
}
void PrintStack(struct Stack* stack){
    for (int i=0;i<stack->size;i++){
        if (stack->nodes[i].type == 1) {
            printf("%u",stack->nodes[i].value);
        } else if ((stack->nodes[i].type ==2)||(stack->nodes[i].type ==0)) {
            printf("%c",stack->nodes[i].operation);
        }
    }
    printf("\n");
}
int ctoi(char s){
    if (s>='0' && s<='9'){
        return s-'0';
    }  else if ('a'<=s && s<='z')
        return(s-'a'+10);
}

int priority(char s){
    if (s=='(' || s==')'){
        return 0;
    } else if (s=='+' || s=='-'){
        return 2;
    } else if (s == '/' || s == '*'){
        return 3;
    } else {
        return 4;
    }
}
//------------------------------------------------------------------
void initTree(struct Tree* tree) {
    tree->root = NULL;
}
struct Node* insertnewelement(struct Node* node, struct Stack* stack){
    if (stack->size > 0) {
        if (node == NULL) {
            node = (struct Node*)malloc(sizeof(struct Node));
            if (stack->size>0) node->element = pop(stack);
            node->left = node->right = NULL;
            if (node->element.type == 1 || node->element.type == 0){
                return node;
            }
        }
        if (!node->right || (node->right && node->right->element.type == 1)) {
            node->right = insertnewelement(node->right, stack);
        }
        if (!node->left || (node->left && node->left->element.type == 1)) {
            node->left = insertnewelement(node->left, stack);
        }
        return node;
    }
}
void insert(struct Tree* tree, struct Stack* stack) {
    if (!tree->root){
        tree->root = (struct Node*)malloc(sizeof(struct Node));
        if (stack->size>0) tree->root->element = pop(stack);
        tree->root->right=tree->root->left=NULL;
    }
    if (stack->size > 0) {
        tree->root = insertnewelement(tree->root, stack);
    }
}
void printElement(struct Token element) {
    if (element.type == 1 ) {
        printf("%u",element.value);
    } else printf("%c",element.operation);
}
void printTree(struct Node* node) {
    if(!node->left && !node->right) {
        printElement(node->element);
        return;
    }
    if(node->left) {
        printTree(node->left);
    }
    printElement(node->element);
    if(node->right) {
        printTree(node->right);
    }
}
// //unsigned bypass(struct Node* node,unsigned cnt) {
//      if(!node->left && !node->right) {
//         return cnt;
//     }
//    // printElement(node->element);
//     if(node->right) {
//         if (node->right->element.operation =='^'){
//             if (node->right->left->element.type==1) cnt*=node->right->left->element.value;
//             bypass(node->right,cnt);
//         }
//         if (node->right->element.type==1) cnt*=node->right->element.value;
//     }
//     return cnt;
// }

void printTreeTask(struct Node* node,struct Stack* stack) {
    if(!node->left && !node->right) {
        if (node->element.type==2){
        if (node->element.operation=='^'){
            pop(stack);
            if (node->right->element.value==0) {
              struct Token a;
              a.type=1;
              a.value=1;
              push_back(stack,a);
            } 
            else{
                f=1;
                for (int i=0;i<node->right->element.value;i++){
                   // if ((node->left->left)!=NULL) printf("(");
                    push_back(stack,node->left->element);
                   // if ((node->left->left)!=NULL) printf(")");
                    if (i!=node->right->element.value-1){
                    struct Token element;
                    element.type=2;
                    element.operation = '*';
                    push_back(stack,element);
                    }
                }
            }
        }
        }
       else {
           if (f!=1){
           struct Token v;
           v = node->element;
           push_back(stack, v);}
           else f = 0;
        }
        return;
    }
    if(node->left) {
        printTreeTask(node->left,stack);
    }
    if (node->element.type==2){
        if (node->element.operation=='^'){
            pop(stack);
             if (node->right->element.value==0) 
             {
                struct Token a;
              a.type=1;
              a.value=1;
              push_back(stack,a);
                 f=1;
             }
             else{
                f=1;
                for (int i=0;i<node->right->element.value;i++){
                 //   if ((node->left->left)!=NULL) printf("(");
                    struct Token v;
                    push_back(stack,node->left->element);
                 //   if ((node->left->left)!=NULL) printf(")");
                    if (i!=node->right->element.value-1){ 
                        struct Token element;
                        element.type=2;
                    element.operation = '*';
                    push_back(stack,element);}
                }
            }
    }
    }
    else {
            if (f!=1){
           struct Token v;
           v = node->element;
           push_back(stack, v);}
           else f = 0;
        }
    if (node->element.type==2){
        if (node->element.operation!='^')
        push_back(stack,node->element);
    }
    if(node->right) {
        printTreeTask(node->right,stack);
    }
}
void freez(struct Tree* tree,struct Node* node){
    if (!node->left && !node->right){
        free(node);
        return;
    }
    if (node->left){
        freez(tree,node->left);
    }
    if (node->right){
        freez(tree,node->right);
    }
    free(node);
}
void BinTreeFree(struct Tree* tree){
    if (tree->root->left){
        freez(tree,tree->root->left);
    }
    if (tree->root->right){
        freez(tree,tree->root->right);
    }
    free(tree->root);
}
int main(){
    struct Stack stackoutput;
    struct Stack operation;
    struct Stack outputtask;
    init(&stackoutput);
    init(&operation);
    init(&outputtask);
    char symbol;
    int number = 0;
    _Bool checker = 1;
    symbol = getchar();
    while (checker){
        struct Token element;
        if (symbol!='+' && symbol!='-'&& symbol !='/'&& symbol!='*' && (symbol<'0'||symbol>'9')&& symbol != '(' && symbol != ')' && symbol!='^'){
            element.operation = symbol;
            element.type = 0;
            push_back(&stackoutput,element);
        } else if (symbol>='0' && symbol<='9'){
            while (symbol>='0' && symbol<='9' && symbol!=EOF && symbol!='\n'){
                number*=10;
                number+=ctoi(symbol);
                symbol=getchar();
            }
            element.value = number;
            element.type = 1;
            push_back(&stackoutput,element);
            number=0;
        } 
        if (symbol=='+' || symbol=='-'|| symbol =='/'|| symbol=='*'){
                if ((operation.size==0) || (priority(symbol) > priority(peek(&operation)))){
                    struct Token sign;
                    sign.value = priority(symbol);
                    sign.operation = symbol;
                    sign.type = 2;
                    push_back(&operation,sign);
                } else if (priority(symbol)<=priority(peek(&operation))){
                    struct Token sign;
                    sign.value = priority(peek(&operation));
                    sign.operation = peek(&operation);
                    sign.type = 2;
                    push_back(&stackoutput,sign);
                    if (operation.size>0) pop(&operation);
                    sign.value = priority(symbol);
                    sign.operation = symbol;
                    sign.type = 2;
                    push_back(&operation,sign);
                }
        } else if (symbol == '(') {
                    struct Token sign;
                    sign.value = priority(symbol);
                    sign.operation = symbol;
                    sign.type = 2;
                    push_back(&operation,sign);
        } else if (symbol == ')'){
                while (peek(&operation)!='('){
                    struct Token sign;
                    sign.value = priority(peek(&operation));
                    sign.operation = peek(&operation);
                    sign.type = 2;
                    push_back(&stackoutput,sign);
                    if (operation.size>0) pop(&operation);
                }
                struct Token sign;
                sign.value = priority(peek(&operation));
                sign.operation = peek(&operation);
                sign.type = 2;
                if (operation.size>0) pop(&operation);
        } else if (symbol == '^'){
                if (priority(symbol) >= priority(peek(&operation))){
                    struct Token sign;
                    sign.value = priority(symbol);
                    sign.operation = symbol;
                    sign.type = 2;
                    push_back(&operation,sign);
                } 
        } 
        if ((symbol == EOF) || (symbol=='\n')){
            break;
        }
        symbol=getchar();
    }
    while (operation.size>0){
        struct Token sign;
        sign.value = priority(peek(&operation));
        sign.operation = peek(&operation);
        sign.type = 2;
        push_back(&stackoutput,sign);
        pop(&operation);
    } 
    if (stackoutput.size>0){
    printf("Stack:");
    PrintStack(&stackoutput);
   // PrintStack(&operation);
    struct Tree tree;
    initTree(&tree);
    printf("Tree:");
    insert(&tree,&stackoutput);
    printTree(tree.root);
    printf("\n");
    printf("Task:");
  //  cnt = bypass(tree.root,cnt);
    // printf("%u",cnt);
    printTreeTask(tree.root,&outputtask);
    PrintStack(&outputtask);
    printf("\n");
    BinTreeFree(&tree);
    }
    free(stackoutput.nodes);
    free(operation.nodes);
    free(outputtask.nodes);
}