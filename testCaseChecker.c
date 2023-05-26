#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define N 10000

typedef struct check{
    char* key;
    char* value;
    char* datatype;
}check;

typedef check* Check;
Check* getInputFromTheFile(char* filename,Check store[]){
    char line[N];
    int count = 0 ;

    FILE *file = fopen(filename,"r");
    if(!file){
        return store;
    }
    while (fgets(line, sizeof(line), file)) {
        int braces = 0;
        int value = 0 ;
        char datatypeD[N] = "";

        char key[N] = "";
        char values[N] = "";
        int keyIterator = 0;
        int valueIterator = 0 ;
        int dataTypeIterator = 0 ;

        int dataType = 0 ;
        for(int i = 0 ; i < strlen(line);i++ ){
            if(line[i] == '('){
                dataType = 1 ;
                braces = 1;
                continue;
            }
            else if(line[i] == ')'){
                dataType = 0;
                braces = 0;
                continue;
            }
            if(dataType == 1){
                datatypeD[dataTypeIterator++] = line[i];
            }
            if(line[i] == ':'){
                value = 1 ;
                continue;
            }
          

            if(!braces){
                if(value == 0){
                    key[keyIterator++] = line[i];
                }
                else{
                    values[valueIterator++] = line[i];
                }
            }

        }
        // printf("\n DataType : %s", datatypeD);
        printf(" Key : %s", values);
        // printf(" , Value : %s\n", values);

        store[count] = (Check)malloc(sizeof(check)); 

        Check newnode = (Check)malloc(sizeof(check));
        newnode -> datatype = (char*)malloc(sizeof(char)*100);
        newnode -> key = (char*)malloc(sizeof(char)*100);
        newnode -> value = (char*)malloc(sizeof(char)*100);

        newnode -> datatype = datatypeD;
        newnode -> value = values;
        newnode -> key = key;

        strcpy(newnode -> datatype , datatypeD);
        strcpy(newnode -> key , key);
        strcpy(newnode -> value , values);

        store[count] = newnode; 
        // store[count] -> key = key;       
        // newnode -> key = "";
        count += 1;
    }
    fclose(file);
    return store;
}

int main(){
    int arr[N] = {0};
    int arr1[N] = {0};
    Check store[N];
    
    getInputFromTheFile("FetchingDocument/Posts/post2",store);
    printf("\n\n");
    for(int i = 0 ; i < 3 ; i++){   
        printf("%s %s ", store[i] -> key, store[i] -> value);
    }
}