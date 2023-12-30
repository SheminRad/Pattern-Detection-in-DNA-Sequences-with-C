#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    char filename[80];
    strcpy(filename,"DNAsequences.txt");
    head = readSequences(filename);
    printf("%s \n",head->sequence);
    head = head->next;
    printf("%s \n",head->sequence);
    int numberOfPatterns = 2;
    patterns = (struct pattern*) malloc(sizeof(struct pattern)*numberOfPatterns); // Allocate memory based on the number of
                                                                                        // patterns for patterns array of structure
    for(int i=0; i<numberOfPatterns;i++)
    {
        printf("Enter the pattern: ");
        scanf("%s",patterns[i].p);
    }
    printf("%s \n",patterns[0].p);
    searchPatterns(head,patterns,numberOfPatterns);
    //Freeing the memory after the program is finished
    free(patterns);
    free(head);
    return 0;
}

struct node * readSequences(char filename[]){
    struct node * head = NULL;

    // WRITE YOUR CODE HERE
    // Allocate memory for head node
    head = (struct node*)malloc(sizeof(struct node));
    if(head == NULL)
    {
        printf("Memory allocation failed in readSequences\n");
        exit(1);
    }
    struct node* temp = head; // temp node to add the data to
                            // linked list without changing the head's place

    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    printf("DNA Sequences File has been opened successfully!\n");
    // while it's not end of the file continue
    while(!feof(inFile))
    {
        char s[81];
        fscanf(inFile,"%[^\n]\n",s);

        // Copy the sequence from file to linked list
        strcpy(temp->sequence, s);
        temp->next = (struct node*)malloc(sizeof(struct node));
        if(temp->next == NULL)
        {
            printf("Memory allocation failed in readSequences\n");
            exit(1);
        }

        // Move to the next node
        temp = temp->next;
    }
    return head;
}

void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE
    struct node* text = head;
    int numberOfPatterns2 = numberOfPatterns;
    while(text!=NULL)
    {
        while(numberOfPatterns2!=0)
        {
            // Rabin Karp:
            int p = 0; // hash value for pattern
            int t = 0; // hash value for txt
            char txt[81];
            strcpy(txt,text->sequence);
            unsigned int n = strlen(txt); //length of the text
            char pat[81];
            strcpy(pat,patterns[numberOfPatterns2-1].p); //since we know the number of patterns,
                                                                    // we start from the last pattern to first
            patterns[numberOfPatterns2-1].times = 0; //initialize times for each pattern
            patterns[numberOfPatterns2-1].sequences = 0; //initializing sequences for each pattern

            unsigned int m = strlen(pat); // length of each Pattern
            int q = 11; // given in the assignment
            int d = 4; //given in the assignment
            int h = int(pow(d,m-1)) % q;
            //CITATION: https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
            // THE CODE BELOW WAS TAKEN FROM THE WEBSITE ABOVE WITH SLIGHT MODIFICATION
            for(int i=0; i< m; i++)
            {
                p = (d * p + pat[i])%q;
                t = (d * t + txt[i])%q;
            }
            // Slide the pattern over text one by one
            for (int i = 0; i <= n - m; i++) {
                int j;
                // Check the hash values of current window of text
                // and pattern. If the hash values match then only
                // check for characters one by one
                if (p == t) {
                    /* Check for characters one by one */
                    for (j = 0; j < m; j++) {
                        if (txt[i + j] != pat[j])
                            break;
                    }

                    // if p == t and pat[0...M-1] = txt[i, i+1,
                    // ...i+M-1]
                    if (j == m)
                    {
                        // update the pattern's times
                        patterns[numberOfPatterns2-1].times++;
                    }
                }

                // Calculate hash value for next window of text:
                // Remove leading digit, add trailing digit
                if (i < n - m) {
                    t = (d * (t - txt[i] * h) + txt[i + m]) % q;

                    // We might get negative value of t, converting
                    // it to positive
                    if (t < 0)
                        t = (t + q);
                }
            }
            // update pattern's sequences
            patterns[numberOfPatterns2-1].sequences++;
            printf("times: %d \n",patterns[numberOfPatterns2-1].times);
            printf("sequences: %d \n",patterns[numberOfPatterns2-1].sequences);
            // go for next pattern
            numberOfPatterns2--;
        }
        // go for next sequence
        numberOfPatterns2 = numberOfPatterns;
        text = text->next;
    }

}
void searchHelper()
{

}
void sortPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE

}

void printPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE

}