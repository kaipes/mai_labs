#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int answer = 0;

struct Node {

    int value;
    struct Node* right;
    struct Node* left;

};

struct Tree{

    struct Node* root;

};

void init(struct Tree* tree){

    tree->root=NULL;

}

struct Node* InsertNewElement(struct Node* node,int value){

    if (!node){

        node=(struct Node*)malloc(sizeof(struct Node));
        node->value=value;
        node->left=node->right=NULL;
        return node;

    }
    
    if (value < node->value){

        node->left = InsertNewElement(node->left,value);

    } else {

        node->right=InsertNewElement(node->right,value);

    }

    return node;

}

void insert(struct Tree* tree,int value){
    
    if (!tree->root){
      
        tree->root = (struct Node*)malloc(sizeof(struct Node));
        tree->root->value=value;
        tree->root->right=tree->root->left=NULL;
        return;

    }

    tree->root=InsertNewElement(tree->root,value);
}

void PrintTree(struct Node* node){
     if (node == NULL) {

        printf("Tree is empty\n");
        return;

    }

    if (!node->left && !node->right){
    
        printf("%d ",node->value);
        return;

    }
    if (node->left){

        PrintTree(node->left);

    }
    printf("%d ",node->value);
    if (node->right){

        PrintTree(node->right);

    }
}

int degree(const struct Node* const node){

    int count = 0;
    if (node->left!=NULL && node->right!=NULL){

        count = 2;

    } else if ((node->left==NULL && node->right!=NULL)||
    (node->left!=NULL && node->right == NULL)){

        count = 1;

    } else count = 0;

    return count;
}

int checkLevel(const struct Node* const node){
    
    if (!node->left && !node->right){
    
        if (degree(node)==node->value){
    
            answer = answer + 1;
    
        }
    
        return answer;
    }
    if (node->left){
    
        checkLevel(node->left);
    
    }
    if (degree(node)==node->value){
    
        answer+=1;
    
    }
    if (node->right){
    
        checkLevel(node->right);
    
    }
    return answer;
}

struct Node* search(struct Tree* tree,int val){
    
    struct Node* s = tree->root;
    while(s){
    
        if (val > s->value){
    
            s = s->right;
    
        } else if (val < s->value) {
    
            s = s->left;
    
        } else {
    
            return s;
    
        }
    }
    return NULL;
}

struct Node* parentSearch(struct Tree* tree,int val){
    
    struct Node* s = tree->root;
    struct Node* parent;
    while(s){
    
        if (val > s->value){
    
            parent = s;
            s = s->right;
    
        } else if (val < s->value) {
    
            parent = s;
            s = s->left;
    
        } else {
    
            s = parent;
            return s;
    
        }
    }
    return NULL;
}

void checkSearch(struct Tree* tree,int val){
    
    struct Node* check = search(tree,val);
    if (check == NULL) {
    
        printf("Element %d does not belong to the tree\n",val);
    
    } else {
    
        printf("Element %d belong to the tree\n",val);
    
    }
}

struct Node* maximumNode(struct Node* node){
    
    struct Node* r = node;
    while (r->right) {
    
        r = r->right;
    
    }
    return r;
}

void delete(struct Tree* tree,struct Node* val){
    
    if (val->left && val->right) {
    
        struct Node* max = maximumNode(val->left);
        int e = max->value;
        delete(tree,max);
        val->value = e;
        return;
    
    } else if (val->left) {
         
        struct Node* parent = parentSearch(tree,val->value);
        if (val == tree->root){
            tree->root = val -> left;
        } else {
        if (val == parent->left) {
    
            parent->left = val->left;
    
        } else {
    
            parent->right = val->left;
    
        }
        }
    } else if (val->right) {
    
        struct Node* parent = parentSearch(tree,val->value);
        if (val == tree->root){
            tree->root = val->right;
        } else {
        if (val == parent->right) {
    
            parent->right = val->right;
    
        } else {
    
            parent->left = val->right;
    
        }
        }
    } else {
        
        struct Node* parent = parentSearch(tree,val->value);
        if (val == tree->root){
            free(tree->root);
            init(tree);
            return;
        } else {
        if (val == parent->left){
    
            parent->left = NULL;
    
        } else {
    
            parent->right = NULL;
    
        }
    }
    }
    free(val);
}

void deleteElement(struct Tree* tree,int val){
    
    struct Node* s = search(tree,val);
    if (s==NULL){
    
        printf("Element %d is not deleted because it is not in the tree\n",val);
    
    } else {
    
        delete(tree,s);
    
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
    struct Tree tree;
    init(&tree);
    char symbol;
    int number;
    while ((symbol = getchar()) != EOF)
	{
		switch (symbol)
		{
        case '+':
			scanf("%d", &number);
			insert(&tree, number);
			break;
		case '-':
			scanf("%d", &number);
			deleteElement(&tree, number);
			break;
        case '?':
            checkSearch(&tree,number);
            break;
        case 'p':
            printf("Tree: ");
            PrintTree(tree.root);
            printf("\n");
            break;
        case 'f':
            printf("%d\n",checkLevel(tree.root));
            answer = 0;
            break;
        }
        getchar();
    }
    if (tree.root!=NULL) {
            BinTreeFree(&tree);
        }
} 



