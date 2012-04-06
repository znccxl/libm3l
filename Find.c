/*
 * function frees memory of the node 
 * copyright ï¿½ 2012 Adam Jirasek
 */
 
#include "Header.h"
#include "format_type.h"
#include "internal_format_type.h"

#include "Find.h"
#include "FunctionsPrt.h"
#include "Find_Source.h"


extern int optind;
static int verbose_flag;

/*
 * routine finds the list
 */
find_t **Find(node_t *List, size_t *founds, char * Options, ...)
{
	
	find_t **Found_Nodes;
	node_t *Tmp1;
 	char *word, **opt, *search_term, *search_term1;
	opts_t *Popts, opts;
	size_t args_num, len, i;
	va_list args;
	int c;
	int option_index;
	
	char path[256];
	
	*founds = 0;
	option_index = 0;
/*
 * get number of options
 */	
	if(Options == NULL)
		return (find_t **)NULL;

	va_start(args, Options);
	args_num = 1;
	len = strlen(Options);

	while((word = va_arg(args, char *)) != NULL){
		args_num ++;
	}
	va_end(args);
/*
 * get the values of option, for that, allocate opts ** array
 */
	if(args_num > 1){

		if ( (opt = (char**)malloc( (args_num+1)*sizeof(char **) )) == NULL)
			Perror("malloc");
/*
 * get the value of the first argument
 */
		va_start(args, Options);
/*
 * array member [0] will be empty
 */
		if ( (opt[0] = malloc( sizeof(char *) )) == NULL)
				Perror("malloc");
	
 		len = strlen(Options);	
		if ( (opt[1] = malloc( (len+1)*sizeof(char *) )) == NULL)
				Perror("malloc");
		strncpy(opt[1], Options, len);
		opt[1][len] = '\0';
/*
 * get the value of other arguments
 */	
		for(i=2; i<args_num; i++){
			word = va_arg(args, char *);
			len = strlen(word);
			if ( (opt[i] = malloc( (args_num+1)*sizeof(char *) )) == NULL)
				Perror("malloc");
			strncpy(opt[i], word, len);
			opt[i][len] = '\0';
		}
/*
 * get the name to look for
 */
 		search_term1 = va_arg(args, char *);
		search_term = strdup(search_term1);
/*
 * end args
 */
		va_end(args);
/*
 * get meaning of options
 * first - reset opting = 0 to reinitialize getopt_long
 */
		opts.opt_i = '\0'; opts.opt_d = '\0'; opts.opt_f = '\0'; opts.opt_r = '\0'; opts.opt_I = '\0';
		optind = 0;
		while (1)
		{
			static struct option long_options[] =
			{
				{"ignore",     no_argument,    0, 'i'},
				{"DIR",        no_argument,    0, 'd'},
				{"FILE",       no_argument,    0, 'f'},
				{"recursive",  no_argument,    0, 'r'},
				{"IGNORE",  no_argument,       0, 'I'},
				{"NUMBER",  no_argument,       0, 'N'},
				{0, 0, 0, 0}
			}; 
 /*
  * getopt_long stores the option index here. 
  */
			c = getopt_long (args_num, opt, "dfiIrN:", long_options, &option_index);
/*
 * Detect the end of the options 
 */
			if (c == -1)
				break;

			switch (c)
			{
				case 0:
 
					if (long_options[option_index].flag != 0)
						break;
			
					printf ("option %s", long_options[option_index].name);
					if (optarg)
						printf (" with arg %s", optarg);
					printf ("\n");
					break;

				case 'i':
/*
 * ignore case
 */
					opts.opt_i = 'i';
					search_term = StrToLower(search_term);
				break;

				case 'I':
/*
 * ignore case
 */
					opts.opt_I = 'I';
				break;
/*
 * look for DIR only
 */
				case 'd':
					opts.opt_d = 'd';
				break;
/*
 * look for FILE only
 */
				case 'f':
					opts.opt_f = 'f';
				break;
/*
 * look for FILE only
 */
				case 'r':
					opts.opt_r = 'r';
				break;

				case '?':
/* 
 * Error, getopt_long already printed an error message
 */
				break;

				default:
				abort ();
			}
		}
/*
 * check if incompatible options
 */
		if( opts.opt_d == 'd' && opts.opt_f == 'f'){
			Warning("Incompatible options -d -f");
/*
 * free array opt **
 */
			if(args_num > 1){
				for(i=0; i<args_num; i++)
					free(opt[i]);
				free(opt);
			}
			return (find_t **)NULL;
		}
	}
	else
	{
/*
 * no additional options provided
 * get the value of the first argument, as not options are specified the argument is the name to look for
 */
		va_start(args, Options);
		search_term = strdup(Options);
		va_end(args);
	}
/*
 * free array opt **
 */
	if(List == NULL){
		Warning("WriteData: NULL list");
		return (find_t **)NULL;
	}

	Popts = &opts;
/*
 * call find function with specified options
 */
	if( List->child == 0){
		Warning("List in Find is not a DIR or is empty DIR, nothing to look for");
		return (find_t **)NULL;
	}
/* 
 * this function returns back found_t **pointer which has "founds" number of items
 * do not forget to free it when you do not need it
 */
	if ( (Found_Nodes = Find_caller(List, founds, search_term, Popts)) == NULL){
		return (find_t **)NULL;
	}
	else
	{
/*
 * write the values of the find result
 */
		printf(" number of founds is %ld \n", *founds);
		for (i=0; i<*founds; i++){
			printf("Name of found subset is --- pointer is %p\n", Found_Nodes[i]->List);
				
			Tmp1 = Found_Nodes[i]->List;
			
			

			if( snprintf(path, 256,"%s/",Tmp1->name) < 0)
				Perror("snprintf");
			while(Tmp1->parent != NULL){
				if( strncat(path, Tmp1->parent->name, strlen(Tmp1->parent->name)) < 0)
					Perror("strcat");
				if( strncat(path, "/",1) < 0)
					Perror("strcat");
				Tmp1 = Tmp1->parent;
			}
			Tmp1 = Found_Nodes[i]->List;
			printf("reversed path is %s   type is %s\n", path, Tmp1->type); 
		}
	}	
//		if(word != NULL) free(word);
		if(search_term != NULL) free(search_term);

	return Found_Nodes;
}