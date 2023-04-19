#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Trie{
    int count;
    struct Trie* childNode[26];
}Trie;

void insert(struct Trie **ppTrie, char *word){
    if(*ppTrie == NULL)
        return;
    
    int len = strlen(word);
    Trie* pNode = *ppTrie;

    for(int i = 0; i < len; i++){

        int childIndex  = word[i] - 'a';//Index for a letter in childNode

        if(pNode->childNode[childIndex] == NULL){ //If the letter has not been made
            pNode->childNode[childIndex] = (Trie*)calloc(1, sizeof(Trie));
        }

        pNode = pNode->childNode[childIndex]; //Move the pointer down to the new node
        
    }

     pNode->count++;

}
int numberOfOccurances(struct Trie *pTrie, char *word){ //How many of a word can be found in the data structure
    int len = strlen(word);

    Trie* temp = pTrie;


    for(int i = 0; i < len; i++){
        
        int childIndex = word[i] - 'a';
        
        temp = temp->childNode[childIndex];
    }

    return temp->count;
}
Trie *deallocateTrie(Trie *pTrie){
    
    for(int i = 0; i < 26; i++){
        if(pTrie->childNode[i] == NULL)
            return NULL;
        else
            deallocateTrie(pTrie->childNode[i]);
    }

    free(pTrie);
    return pTrie;
}
int main(void)
{
      //read the number of the words in the dictionary
      // parse line  by line, and insert each word to the trie data structure
      struct Trie* root = calloc(1, sizeof(Trie));

      char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};

      int numWords = sizeof(pWords) / sizeof(pWords[0]);

      

      for(int i = 0; i < numWords; i++){
        insert(&root, pWords[i]);
      } 

      for (int i=0;i<5;i++)
      {
          printf("\t%s : %d\n",pWords[i], numberOfOccurances(root, pWords[i]));
     }
    root = deallocateTrie(root);
    if (root != NULL)
       printf("There is an error in this program\n");
    return 0;
}