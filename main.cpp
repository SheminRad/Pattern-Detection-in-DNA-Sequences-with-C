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

//Helper Function
int searchHelper(struct pattern *patterns, int numberOfPatterns, char txt[], char pat[]);

int main(int argc, char *argv[]){
    struct node * head = NULL;
    struct pattern *patterns = NULL;

    // WRITE YOUR CODE HERE
    char filename[80];
    printf("Enter the file path containing the DNA sequences:");
    fflush(stdin);
    scanf("%s",filename);

    strcpy(filename,filename);
    head = readSequences(filename);
//    printf("%s \n",head->sequence);
    int numberOfPatterns;
    printf("Enter the number of patterns:");
    scanf("%d", &numberOfPatterns);

    patterns = (struct pattern*) malloc(sizeof(struct pattern)*numberOfPatterns); // Allocate memory based on the number of
                                                                                        // patterns for patterns array of structure
    for(int i=0; i<numberOfPatterns;i++)
    {
        printf("Enter the pattern:");
        fflush(stdin);
        scanf("%s", patterns[i].p);
    }
    printf("\n");
    searchPatterns(head,patterns,numberOfPatterns);
    sortPatterns(patterns,numberOfPatterns);
    printPatterns(patterns,numberOfPatterns);
    //Freeing the memory after the program is finished
    free(patterns);
    free(head);
    return 0;
}

struct node * readSequences(char filename[]){
    struct node * head = NULL;

    // WRITE YOUR CODE HERE
    FILE *inFile = fopen(filename, "r");
    if (inFile == NULL){
        printf("File could not be opened.\n");
        exit(1);
    }
    printf("DNA Sequences File has been opened successfully!\n");

    // Allocate memory for head node
    head = (struct node*)malloc(sizeof(struct node));
    if(head == NULL)
    {
        printf("Memory allocation failed in readSequences\n");
        exit(1);
    }
    struct node* temp;
    temp = head; // temp node to add the data to
    // linked list without changing the head's place
    while(true)
    {
        char s[81];
        // while it's not end of the file, continue
        if(fscanf(inFile,"%[^\n]\n",s)!=1)
            break;

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
    fclose(inFile);
    return head;
}

void searchPatterns(struct node *head, struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE
    int numberOfPatterns2 = numberOfPatterns;
    for(int i=0;i<numberOfPatterns;i++)
    {
        patterns[i].times = 0; //initialize times for each pattern
        patterns[i].sequences = 0; //initializing sequences for each pattern
    }
    // Outer loop to go over all the patterns that user inputs
    while(numberOfPatterns != 0)
    {
        struct node* text = head;
        // Inner loop to go over all the sequences in the linked list (DNA sequences in the file)
        while(text->next!= NULL)
        {
            char txt[81];
            strcpy(txt,text->sequence);
            char pat[81];
            strcpy(pat,patterns[numberOfPatterns - 1].p); //since we know the number of patterns,
            // we start from the last pattern to first which does not make any difference

            //Rubin Karp Algorithm is declared inside the below function
            int flag = searchHelper(patterns, numberOfPatterns, txt, pat);
            // update pattern's sequences
            if(flag)
                patterns[numberOfPatterns - 1].sequences++;
            text = text->next;
        }
        // go for next pattern
        numberOfPatterns--;
    }
}
int searchHelper(struct pattern *patterns, int numberOfPatterns, char txt[], char pat[])
{
    // Rabin Karp:
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    unsigned int n = strlen(txt); //length of the text
    unsigned int m = strlen(pat); // length of each Pattern
    int q = 11; // given in the assignment
    int d = 4; //given in the assignment
    int h = int(pow(d,m-1)) % q;

    int flag =0; // to detect when a sequence has the pattern
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
                if (txt[i + j] != pat[j]) //comparing each character of pattern with text
                    break;
            }

            // if p == t and pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]
            if (j == m)
            {
                // update the pattern's times
                patterns[numberOfPatterns-1].times++;
                flag = 1;
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
    return flag;
}
void sortPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE
    //CITATION: https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
    // THE CODE BELOW WAS TAKEN FROM THE WEBSITE ABOVE WITH SLIGHT MODIFICATION
    int i, key, j;
    for (i = 1; i < numberOfPatterns; i++)
    {
        key = patterns[i].times;
        j = i - 1;

        /* Move elements of patterns[0..i-1],
           that are less than key,
           to one position ahead of
           their current position */
        while (j >= 0 && patterns[j].times < key)
        {
            // swapping the nodes in the array
            struct pattern temp = patterns[j];
            patterns[j] = patterns[j+1];
            patterns[j+1] = temp;
            j = j - 1;
        }
        patterns[j + 1].times = key;
    }

}

void printPatterns(struct pattern *patterns, int numberOfPatterns){

    // WRITE YOUR CODE HERE
    int i;
    for (i = 0; i < numberOfPatterns; i++)
        printf("%s is detected %d times in %d sequences\n",patterns[i].p ,patterns[i].times, patterns[i].sequences);
    printf("\n");
}