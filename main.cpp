#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
    char sequence[81];
    struct node *next;
};

struct pattern{
    char p[81];
    int times;
    int sequences;
};

struct node * readSequences(char filename[]);
void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns);
void sortPatterns(struct pattern *patterns, int numberOfPatterns);
void printPatterns(struct pattern *patterns, int numberOfPatterns);

int main(int argc, char *argv[]){
    struct node * head = NULL;
    struct pattern *patterns = NULL;

    // WRITE YOUR CODE HERE

    return 0;
}

struct node * readSequences(char filename[]){
    struct node * head = NULL;

    // WRITE YOUR CODE HERE

    return head;
}

void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE

}

void sortPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE

}

void printPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE

}