//Rebecca Hanessian
//CS 4280
//P0

#include node.h

struct node *new_node(int x) {
  	struct node *val = (struct node *)calloc(1,sizeof(struct node));
  	printf("Allocating memory now at %p\n", val);
  	val->len = x;
  	val->p_left = val->p_right = NULL;
  	val->num = 0;
  	return val;
}

void insert(int key, struct node **leaf)
{
    if( *leaf == 0 )
    {
        *leaf = (struct node*) calloc(1,  sizeof( struct node ) );
        (*leaf)->len = key;
        /* initialize the children to null */
        (*leaf)->p_left = 0;    
        (*leaf)->p_right = 0;  
    }
    else if(key < (*leaf)->len)
    {
        insert( key, &(*leaf)->p_left );
    }
    else if(key > (*leaf)->len)
    {
        insert( key, &(*leaf)->p_right );
    }
}
/*
struct node* insert(struct node *root, int x)
{
	if (root == NULL) { 
		printf("insert: root=%p, inserting new node for %d\n", root, x);
		struct node *newval = new_node(x);
		printf("new node = %p\n", newval);
		return newval;
	}

  	if (x < root->len)
    	root->p_left = insert(root->p_left, x);
  	else if (x > root->len)
    	root->p_right = insert(root->p_right, x);
	printf("insert: returning %p\n", root);
  	return NULL;//root;
}
*/
struct node* search(struct node *root, int x)
{
    if(root==NULL || root->len==x) {
    	printf("found length %d at %p\n", x, root);
        return root;
    } else if(x<root->len) {
        return search(root->p_left, x);
    } else {
        return search(root->p_right,x);
    }
}

struct node* buildTree(char** inputArray, int length){
	int i;
	struct node* tree = NULL;
	for(i = 0; i < length; i++){
		int len = (int)strlen(inputArray[i]);
		struct node* finding = NULL;
		if (!tree) {
			tree = finding = new_node(len);
			printf("created tree at %p\n", tree);
		} else {
			finding = search(tree, len);
			if (finding == NULL) {
				insert(len, &tree);
				finding = search(tree, len);
				//finding = insert(tree, len);
				printf("inserted new node %p (tree=%p) for length %d\n", finding, tree, len);
			} else {
				printf("found node %p for length %d\n", finding, len);
			}
		}
		finding->value[finding->num++] = strdup(inputArray[i]);
		printf("adding word %s length %d at %p, tree=%p\n", inputArray[i], len, finding, tree);
		if(tree==NULL) {
			printf("setting tree to %p\n", finding);
			tree = finding;
		}
		printf("\n");
	}
	return tree;
}

void printPostorder( struct node *root, int level, FILE* outfile)
{
	if( root != NULL){
		printPostorder(root->p_left, level+1, outfile);
		printPostorder(root->p_right, level+1, outfile);
		fprintf(outfile, "%d\n", root->len);
		for (int i = 0; i < root->num; i++){
			for(int j=0; j<level; j++){
				fprintf(outfile, "  ");
			}
			fprintf(outfile, "%s\n", root->value[i]);	
		}
	}
}

void printPreorder(struct node *root, int level, FILE* outfile)
{
	if( root != NULL) {
		fprintf(outfile, "%d\n", root->len);
		for (int i = 0; i < root->num; i++){
			for(int j=0; j<level; j++){
				fprintf(outfile, "  ");
			}
			fprintf(outfile, "%s\n", root->value[i]);	
		}
		printPreorder(root->p_left, level+1, outfile);
		printPreorder(root->p_right, level+1, outfile);
	}
}

void printInorder(struct node *root, int level, FILE* outfile)
{
    if( root != NULL ) {
        printInorder(root->p_left, level+1, outfile);
        fprintf(outfile, "%d\n", root->len);
        for (int i = 0; i < root->num; i++){
        	for(int j=0; j<level; j++){
				fprintf(outfile, "  ");
			}
			fprintf(outfile, "%s\n", root->value[i]);	
		}
        printInorder(root->p_right, level+1, outfile);
    }
}

int main (int argc, const char *argv[]){
	int counter = 0;
	FILE *input;
	int i;
    char *word[NUM_STRINGS];
	if ( argc > 2 ) 
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
        return -1;
    }
    else if (argc == 1){
    	//read from keyboard
    	printf("Begin inputting strings (end with empty string):");
    	input = stdin;
    }
    else 
    {
    	const char* filename = argv[1];
        FILE *file = fopen( filename, "r" );

        if ( file == 0 )
        {
            printf( "File could not be opened.\n" );
            return -1;
        }
        input = file;
    }
	size_t malloc_size = 500;
	for (i = 0; i < NUM_STRINGS; i++) {
		word[i] = malloc(malloc_size * sizeof(char)); 
		fgets(word[i], malloc_size, input); 
		if (word[i][0] == '\n' || word[i][0] == 0)
			break;
		int len = strlen(word[i]);
		if (len == 0)
			break;
		word[i][len-1] = 0;
		counter++;
	}
	
	struct node* tree = buildTree(word, counter);
	FILE* pre = fopen("outP0.preorder","w");
	FILE* inord = fopen("outP0.inorder","w");
	FILE* post = fopen("outP0.postorder","w");
	printf("Preorder \n");
	printPreorder(tree, 0, pre);
	printf("Inorder \n");
	printInorder(tree, 0, inord);
	printf("Postorder \n");
	printPostorder(tree, 0, post);
	fclose(pre);
	fclose(inord);
	fclose(post);
	
	
	
	word[i] = NULL;
	if (input != stdin)
		fclose(input);
	return 0;

}
