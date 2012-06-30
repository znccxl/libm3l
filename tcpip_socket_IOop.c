
#include "Header.h"
#include "format_type.h"
#include "FunctionsPrt.h"

#include "tcpip_socket_op.h"
#include "tcpip_socket_IOop.h"
#include "Write2Socket.h"
#include "ReadSocket.h"
#include "ln_list.h"

static int send_to_tcpipsocket(node_t *, const char *, int , opts_t *);
static node_t *send_receive_tcpipsocket(node_t *, const char *, int , opts_t *);
static node_t *receive_send_tcpipsocket(node_t *, const char *, int , opts_t *);
static node_t *receive_tcpipsocket(const char *, int, opts_t *);

/*
 * routine Links Slist to Tlist
 */
int Send_to_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, char * Options, ...){

	node_t *List;
	char *word, **opt;
	opts_t *Popts, opts;
	size_t args_num, len,i;
	va_list args;
	int c;
	int option_index;
	
	opts.opt_e = '\0'; opts.opt_a = '\0'; opts.opt_c = '\0';
	
	option_index = 0;
/*
 * get number of options
 */	
	if(Options != NULL){
		va_start(args, Options);
		args_num = 1;
		len = strlen(Options);

		while((word = va_arg(args, char *)) != NULL){
			args_num++;
		}
		va_end(args);
		args_num++;
/*
 * get the values of option, for that, allocate opts ** array
 */
		if ( (opt = (char**)malloc( (args_num)*sizeof(char *) )) == NULL)
			Perror("malloc");
/*
 * get the value of the first argument
 */
		va_start(args, Options);
/*
 * array member [0] will be empty
 */
		if ( (opt[0] = (char *)malloc( sizeof(char) )) == NULL)
				Perror("malloc");
	
 		len = strlen(Options);	
		if ( (opt[1] = (char *)malloc( (len+1) * sizeof(char ) )) == NULL)
				Perror("malloc");
		strncpy(opt[1], Options, len);
		opt[1][len] = '\0';
/*
 * get the value of other arguments
 */	
		for(i=2; i<args_num; i++){
			word = va_arg(args, char *);
			len = strlen(word);
			if ( (opt[i] = (char *)malloc( (len+1)*sizeof(char) )) == NULL)
				Perror("malloc");
			strncpy(opt[i], word, len);
			opt[i][len] = '\0';
		}
/*
 * end args
 */
		va_end(args);
/*
 * get meaning of options
 * first - reset opting = 0 to reinitialize getopt_long
 */
		optind = 0;
		while (1)
		{
			static struct option long_options[] =
			{
				{"clean_empy_links",     no_argument,       0, 'e'},
				{0, 0, 0, 0}
			};
 /*
  * getopt_long stores the option index here. 
  */
			c = getopt_long (args_num, opt, "e", long_options, &option_index);
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

				case 'e':
/*
 * clean empty list
 */
					opts.opt_e = 'e';
				break;
/* 
 * Error, getopt_long already printed an error message
 */
				break;

				default:
				abort ();
			}
		}
/*
 * free array opt **
 */
		for(i=0; i<args_num; i++)
			free(opt[i]);
		free(opt);	
	}
	else
	{
/*
 * no additional options provided
 * get the value of the first argument, as not options are specified the argument is the name to look for
 */
//  		opts.opt_r = 'r';
// 		opts.opt_L = 'L';  NOTE - needs to be specified
	}
/*
 * locate nodes using find function
 */
	Popts = &opts;
	
 	if( send_to_tcpipsocket(Lnode, hostname, portnumber, Popts) < 0){
		return -1;
	}
	else{
		return 1;
	}
}



/*
 * routine Links Slist to Tlist
 */
node_t *Send_receive_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, char * Options, ...)
{

	node_t *List;
	char *word, **opt;
	opts_t *Popts, opts;
	size_t args_num, len,i;
	va_list args;
	int c;
	int option_index;
	
	opts.opt_e = '\0'; opts.opt_a = '\0';
	
	option_index = 0;
/*
 * get number of options
 */	
	if(Options != NULL){
		va_start(args, Options);
		args_num = 1;
		len = strlen(Options);

		while((word = va_arg(args, char *)) != NULL){
			args_num++;
		}
		va_end(args);
		args_num++;
/*
 * get the values of option, for that, allocate opts ** array
 */
		if ( (opt = (char**)malloc( (args_num)*sizeof(char *) )) == NULL)
			Perror("malloc");
/*
 * get the value of the first argument
 */
		va_start(args, Options);
/*
 * array member [0] will be empty
 */
		if ( (opt[0] = (char *)malloc( sizeof(char) )) == NULL)
				Perror("malloc");
	
 		len = strlen(Options);	
		if ( (opt[1] = (char *)malloc( (len+1) * sizeof(char ) )) == NULL)
				Perror("malloc");
		strncpy(opt[1], Options, len);
		opt[1][len] = '\0';
/*
 * get the value of other arguments
 */	
		for(i=2; i<args_num; i++){
			word = va_arg(args, char *);
			len = strlen(word);
			if ( (opt[i] = (char *)malloc( (len+1)*sizeof(char) )) == NULL)
				Perror("malloc");
			strncpy(opt[i], word, len);
			opt[i][len] = '\0';
		}
/*
 * end args
 */
		va_end(args);
/*
 * get meaning of options
 * first - reset opting = 0 to reinitialize getopt_long
 */
		optind = 0;
		while (1)
		{
			static struct option long_options[] =
			{
				{"clean_empy_links",     no_argument,       0, 'e'},
				{0, 0, 0, 0}
			};
 /*
  * getopt_long stores the option index here. 
  */
			c = getopt_long (args_num, opt, "e", long_options, &option_index);
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

				case 'e':
/*
 * clean empty list
 */
					opts.opt_e = 'e';
				break;
/* 
 * Error, getopt_long already printed an error message
 */
				break;

				default:
				abort ();
			}
		}
/*
 * free array opt **
 */
		for(i=0; i<args_num; i++)
			free(opt[i]);
		free(opt);	
	}
	else
	{
/*
 * no additional options provided
 * get the value of the first argument, as not options are specified the argument is the name to look for
 */
//  		opts.opt_r = 'r';
// 		opts.opt_L = 'L';  NOTE - needs to be specified
	}
/*
 * locate nodes using find function
 */
	Popts = &opts;
	
 	if( (List = send_receive_tcpipsocket(Lnode, hostname, portnumber, Popts)) == NULL){
		return (node_t *)NULL;
	}
	else{
		return List;
	}
}



/*
 * routine Links Slist to Tlist
 */
node_t *Receive_send_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, char * Options, ...)
{

	node_t *List;
	char *word, **opt;
	opts_t *Popts, opts;
	size_t args_num, len,i;
	va_list args;
	int c;
	int option_index;
	
	opts.opt_e = '\0'; opts.opt_a = '\0';
	
	option_index = 0;
/*
 * get number of options
 */	
	if(Options != NULL){
		va_start(args, Options);
		args_num = 1;
		len = strlen(Options);

		while((word = va_arg(args, char *)) != NULL){
			args_num++;
		}
		va_end(args);
		args_num++;
/*
 * get the values of option, for that, allocate opts ** array
 */
		if ( (opt = (char**)malloc( (args_num)*sizeof(char *) )) == NULL)
			Perror("malloc");
/*
 * get the value of the first argument
 */
		va_start(args, Options);
/*
 * array member [0] will be empty
 */
		if ( (opt[0] = (char *)malloc( sizeof(char) )) == NULL)
				Perror("malloc");
	
 		len = strlen(Options);	
		if ( (opt[1] = (char *)malloc( (len+1) * sizeof(char ) )) == NULL)
				Perror("malloc");
		strncpy(opt[1], Options, len);
		opt[1][len] = '\0';
/*
 * get the value of other arguments
 */	
		for(i=2; i<args_num; i++){
			word = va_arg(args, char *);
			len = strlen(word);
			if ( (opt[i] = (char *)malloc( (len+1)*sizeof(char) )) == NULL)
				Perror("malloc");
			strncpy(opt[i], word, len);
			opt[i][len] = '\0';
		}
/*
 * end args
 */
		va_end(args);
/*
 * get meaning of options
 * first - reset opting = 0 to reinitialize getopt_long
 */
		optind = 0;
		while (1)
		{
			static struct option long_options[] =
			{
				{"clean_empy_links",     no_argument,       0, 'e'},
				{0, 0, 0, 0}
			};
 /*
  * getopt_long stores the option index here. 
  */
			c = getopt_long (args_num, opt, "e", long_options, &option_index);
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

				case 'e':
/*
 * clean empty list
 */
					opts.opt_c = 'e';
				break;
/* 
 * Error, getopt_long already printed an error message
 */
				break;

				default:
				abort ();
			}
		}
/*
 * free array opt **
 */
		for(i=0; i<args_num; i++)
			free(opt[i]);
		free(opt);	
	}
	else
	{
/*
 * no additional options provided
 * get the value of the first argument, as not options are specified the argument is the name to look for
 */
//  		opts.opt_r = 'r';
// 		opts.opt_L = 'L';  NOTE - needs to be specified
	}
/*
 * locate nodes using find function
 */
	Popts = &opts;
	
 	if( (List = receive_send_tcpipsocket(Lnode, hostname, portnumber, Popts)) == NULL){
		return (node_t *)NULL;
	}
	else{
		return List;
	}
}


node_t *Receive_tcpipsocket(const char *hostname, int portnumber, char * Options, ...)
{

	node_t *List;
	char *word, **opt;
	opts_t *Popts, opts;
	size_t args_num, len,i;
	va_list args;
	int c;
	int option_index;
	
	opts.opt_e = '\0'; opts.opt_a = '\0';
	
	option_index = 0;
/*
 * get number of options
 */	
	if(Options != NULL){
		va_start(args, Options);
		args_num = 1;
		len = strlen(Options);

		while((word = va_arg(args, char *)) != NULL){
			args_num++;
		}
		va_end(args);
		args_num++;
/*
 * get the values of option, for that, allocate opts ** array
 */
		if ( (opt = (char**)malloc( (args_num)*sizeof(char *) )) == NULL)
			Perror("malloc");
/*
 * get the value of the first argument
 */
		va_start(args, Options);
/*
 * array member [0] will be empty
 */
		if ( (opt[0] = (char *)malloc( sizeof(char) )) == NULL)
				Perror("malloc");
	
 		len = strlen(Options);	
		if ( (opt[1] = (char *)malloc( (len+1) * sizeof(char ) )) == NULL)
				Perror("malloc");
		strncpy(opt[1], Options, len);
		opt[1][len] = '\0';
/*
 * get the value of other arguments
 */	
		for(i=2; i<args_num; i++){
			word = va_arg(args, char *);
			len = strlen(word);
			if ( (opt[i] = (char *)malloc( (len+1)*sizeof(char) )) == NULL)
				Perror("malloc");
			strncpy(opt[i], word, len);
			opt[i][len] = '\0';
		}
/*
 * end args
 */
		va_end(args);
/*
 * get meaning of options
 * first - reset opting = 0 to reinitialize getopt_long
 */
		optind = 0;
		while (1)
		{
			static struct option long_options[] =
			{
				{"clean_empy_links",     no_argument,       0, 'e'},
				{0, 0, 0, 0}
			};
 /*
  * getopt_long stores the option index here. 
  */
			c = getopt_long (args_num, opt, "e", long_options, &option_index);
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

				case 'e':
/*
 * clean empty list
 */
					opts.opt_c = 'e';
				break;
/* 
 * Error, getopt_long already printed an error message
 */
				break;

				default:
				abort ();
			}
		}
/*
 * free array opt **
 */
		for(i=0; i<args_num; i++)
			free(opt[i]);
		free(opt);	
	}
	else
	{
/*
 * no additional options provided
 * get the value of the first argument, as not options are specified the argument is the name to look for
 */
//  		opts.opt_r = 'r';
// 		opts.opt_L = 'L';  NOTE - needs to be specified
	}
/*
 * locate nodes using find function
 */
	Popts = &opts;
	
 	if( (List = receive_tcpipsocket(hostname, portnumber, Popts)) == NULL){
		return (node_t *)NULL;
	}
	else{
		return List;
	}
}


/*
 * function opens socket, writes data to it, reads data from it and close the socket
 */
node_t *receive_tcpipsocket(const char *hostname, int portnumber, opts_t *Popts)
{
	node_t *Gnode;
	int socketnr;

	if ( (socketnr =  cli_open_socket("localhost", portnumber)) < 0)
		Error("Could not open socket");
	if( (Gnode = read_socket(socketnr, Popts)) == NULL)
		Error("Error during reading data from socket");
	if( close(socketnr) == -1)
		Perror("close");
/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')
		 ln_cleanemptylinks(&Gnode,  Popts) ;
	
	return Gnode;
}

/*
 * function opens socket, writes data to it and close the socket
 */
int send_to_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, opts_t *Popts)
{
	int socketnr;
/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')
		 ln_cleanemptylinks(&Lnode,  Popts) ;	
	if ( (socketnr =  cli_open_socket("localhost", portnumber)) < 0)
		Error("Could not open socket");
	if ( write_to_socket(1, Lnode,  socketnr) < 0)
		Error("Error during writing data to socket");
	if( close(socketnr) == -1)
		Perror("close");
	
	return 1;
}
/*
 * function opens socket, writes data to it, reads data from it and close the socket
 */
node_t *send_receive_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, opts_t *Popts)
{
	
	
	node_t *Gnode;
	int socketnr;
/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')
		 ln_cleanemptylinks(&Lnode,  Popts) ;

	if ( (socketnr =  cli_open_socket("localhost", portnumber)) < 0)
		Error("Could not open socket");

	if ( write_to_socket(1, Lnode,  socketnr) < 0)
		Error("Error during writing data to socket");
	if( (Gnode = read_socket(socketnr, Popts)) == NULL)
		Error("Error during reading data from socket");
	if( close(socketnr) == -1)
		Perror("close");
/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')
		 ln_cleanemptylinks(&Gnode,  Popts) ;
	
	return Gnode;
}

/*
 * function opens socket, reads data from it , writes data to it and close the socket
 */
node_t *receive_send_tcpipsocket(node_t *Lnode, const char *hostname, int portnumber, opts_t *Popts)
{
	
	
	node_t *Gnode;
	int socketnr;
/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')			
		ln_cleanemptylinks(&Lnode,  Popts) ;

	if ( (socketnr =  cli_open_socket("localhost", portnumber)) < 0)
		Error("Could not open socket");
	if( (Gnode = read_socket(socketnr, Popts)) == NULL)
		Error("Error during reading data from socket");

	if ( write_to_socket(1, Lnode,  socketnr) < 0)
		Error("Error during writing data to socket");
	if( close(socketnr) == -1)
		Perror("close");

/*
 * if required, clean empty links
 */
	if(Popts->opt_e == 'e')
		 ln_cleanemptylinks(&Gnode,  Popts) ;

	
	return Gnode;
}
