//program to insert and search in a trie

// C implementation of search and insert operations
// on Trie
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
#define MAX 100

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    
    // isLeaf is true if the node represents
    // end of a word
    bool isLeaf;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
    
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    
    if (pNode)
    {
        int i;
        
        pNode->isLeaf = false;
        
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
    
    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, char *key)
{
    int level;
    int length = strlen(key);
    int index;
    
    struct TrieNode *pCrawl = root;
    
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
        
        pCrawl = pCrawl->children[index];
    }
    
    // mark last node as leaf
    pCrawl->isLeaf = true;
}

// Returns true if key presents in trie, else false

bool find(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        
        if (!pCrawl->children[index])
            return false;
        
        pCrawl = pCrawl->children[index];
    }
    
    return (pCrawl != NULL && pCrawl->isLeaf);
}







void insertFn(struct TrieNode *root)
{
    FILE *fp=fopen("/Users/ankit/Downloads/DS Project/Words_database.txt","r");
    if(fp==NULL)
        printf("Error while opening");
    char word[10];
    char new_word[10];
    int i=0;
    while(fgets(word,10,fp) && feof(fp)==0)
    {
        if(i==241)
            break;
        i++;
        word[strlen(word)-1]='\0';
        strcpy(new_word,word);
        
        
        insert(root,new_word);
        
    }
    fclose(fp);
}






int dfs(struct TrieNode *root, char *dat)
{
    int i;
    char k[100] = {0};
    char a[2] = {0};
    if (root == NULL)
        return 0;
    if (root->isLeaf ==true)
        printf("Match: %s\n", dat);
    for(i = 0; i < 26; ++i)
    {
        strcpy(k, dat);
        a[0] = i + 'a';
        a[1] = '\0';
        strcat(k, a);
        dfs(root->children[i], k);
    }
}

void search(struct TrieNode *root, char *s, char *dat)
{
    int i;
    char l[100] = {0};
    char a[2];
    strcpy(l, dat);
    if (strlen(s) > 0) {
        a[0] = s[0];
        a[1] = '\0';
        if(root->children[a[0]-'a'] != NULL)
        {
            strcat(dat, a);
            search(root->children[a[0]-'a'], s+1, dat);
        }
        else
            printf("No Match");
    }
    else
    {
        if (root->isLeaf==true)
            printf("Match: ");
        for (i = 0; i < 26; ++i)
        {
            strcpy(l, dat);
            a[0] = i + 'a';
            a[1] = '\0';
            strcat(l, a);
            dfs(root->children[i], l);
        }
    }
}

int main(void)
{
    
    int i=0;
    struct TrieNode *root = getNode();
    int choice;
    char dat[100]="";
    char search_key[10];
    
    
    insertFn(root);
    char s[20];
    printf("1. Search in Dictionary\n");
    printf("2. Find Matching Words\n");
    printf("3. To Exit\n");
    scanf("%d",&choice);
    while (choice!=3)
    {
       
        
        if(choice==1)
        {
            printf("Enter word to search in the Trie\n");
            scanf("%s",search_key);
            if(find(root,search_key))
                printf("Word Found\n");
            else
                printf("Word Not Found\n");
            
            
        }
        else if(choice==2)
        {
            
            printf("Enter prefix\n");
            scanf("%s",s);
            
            printf("Words Matching with prefix %s \n",s);
            search(root,s,dat);
            memset(dat,0,sizeof(dat));
            
        }
        else
            break;
        
        printf("Enter choice\n");
        scanf("%d",&choice);
        
        
        
    }
   
    
    return 0;
    
    
    
    
}













