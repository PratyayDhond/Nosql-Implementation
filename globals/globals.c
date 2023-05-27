
void initGlobals(){
    globals.collection = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.collection)
        exit(EXIT_FAILURE);

    globals.user = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.user)
        exit(EXIT_FAILURE);

    globals.document = (char*) malloc(sizeof(char) * SIZE);
    if(!globals.document)
        exit(EXIT_FAILURE);

    globals.user[0] = '\0';
    globals.document[0] = '\0';
    globals.collection[0] = '\0';

return;
}

void destroyGlobals(){
    if(globals.collection)
        free(globals.collection);
    if(globals.user)
        free(globals.user);
    if(globals.document)
        free(globals.document);
return;
}

