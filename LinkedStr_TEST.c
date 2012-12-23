/*
 *     Copyright (C) 2012  Adam Jirasek
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU Lesser General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU Lesser General Public License for more details.
 * 
 *     You should have received a copy of the GNU Lesser General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *     
 *     contact: libm3l@gmail.com
 * 
 */



/*
 *     Function LinkedStr_TEST.c
 *
 *     Date: 2012-07-01
 * 
 * 
 *
 *
 *     Description:
 * 
 *
 *     Input parameters:
 * 
 *
 *     Return value:
 * 
 * 
 *
 *     Modifications:
 *     Date		Version		Patch number		CLA 
 *
 *
 *     Description
 *
 */




/*
 * Array examples
 */
#include "Header.h"
#include "format_type.h"
#include "internal_format_type.h"

#include "IO.h"
#include "Find.h"
#include "Rm.h"
#include "Mount.h"
#include "Umount.h"
#include "Cat.h"
#include "tcpip_socket_IOop.h"
#include "WriteData.h"
#include "FunctionsPrt.h"
#include "Locate.h"
#include "Cp.h"
#include "Mklist.h"
#include "Add.h"


lmint_t main(void) 
{	
    node_t *Gnode=NULL, *RecNode=NULL, *Anode=NULL, *Tmpnode=NULL, *NewList=NULL;
    find_t *Founds=NULL;
    
    lmint_t i, count,countgrp, socketnr, j;

    size_t *dim;
    
    lmchar_t name[255], type[30];
    lmchar_t *pc;
    
    path_t *parsed_path;

    lmint_t  num, wc;
//     lmint_t *ada;
    lmint_t ada[5];
    get_arg_t argsstr;
    
    lmlongdouble_t test1;
    lmdouble_t test2;
    lmfloat_t test3;
    
//     lmchar_t dummy[1];
//     lmdouble_t value = 42.000042; /* or anything else */
//     lmint_t siz;

 /*   
#if defined ENVIRONMENT64
	printf(" 64 bit \n");
#elif defined ENVIRONMENT32
	printf(" 32 bit \n");
#endif*/
	
// 	printf(" %ld   %ld %ld  \n ", sizeof(test1), sizeof(test2), sizeof(test3));
// 	exit(0);
// 	
 

    FILE *fp;
    
    lmchar_t *node_path;
    printf("before Going to Fread1\n");

    printf("Going to Fread1\n");
   
//     printf("%p\n ",  __builtin_return_address(0));  /" gives pointer to return address */

//     siz = snprintf(dummy, sizeof(dummy), "%lf", value);
//     printf("exact length needed to represent 'value' "
//            "(without the '\\0' terminator) is %d.\n", siz);
//         printf("%f\n\n\n", -DBL_MAX);
// 	printf("%d\n", snprintf(NULL, 0, "%.10f", value));
//     exit(0);

	for (j=0; j<1; j++){
		
		printf(" CYCLE %d\n\n", j);

 		if( (Gnode = m3l_Fread("ADA1" , "--clean_empy_links", (lmchar_t *)NULL))  == NULL)
 			Perror("Linked_test: m3l_Fread");
		
// 		m3l_Fwrite(Gnode, "ADA", (lmchar_t *)NULL);
// 		printf("\n\n\n\n");
// 		exit(0);

		
		if(m3l_Cat(Gnode, "--all", "-P", "-L","--links",  "*",   (lmchar_t *)NULL) != 0)
 	                   Error("CatData");
					
		printf("\n\n\n\n");

 		if( (Anode = m3l_Send_receive_tcpipsocket(Gnode, "localhost", 4096, "--encoding" , "IEEE-754",  "--buffering", "MEMCPY", (lmchar_t *)NULL)) == NULL)
// 		if( (Anode = m3l_Send_receive_tcpipsocket(Gnode, "localhost", 4096,  (lmchar_t *)NULL)) == NULL)
		Perror("Send_receive");
		if(m3l_Cat(Anode, "--all", "-P", "-L","--links",  "*",   (lmchar_t *)NULL) != 0)
 	                   Error("CatData");
// exit(0);		
		if(m3l_Umount(&Anode) != 1)
			Perror("m3l_Umount");
		
		
 		if( (Anode = m3l_Fread("TEST.dat", (lmchar_t *)NULL))  == NULL)
 			Perror("Linked_test: m3l_Fread");	
//  		if( (Anode = m3l_Fread("ADA_EMPTYLINK"))  == NULL)
//  			Perror("Linked_test: m3l_Fread");	

 		if(m3l_Cat(Anode, "--all", "-P", "-L", "--links", "*", (lmchar_t *)NULL) != 0)
 	                   Error("CatData");
// exit(0);
	
// 

		
		printf("\n\n\n\n");
		
// 		Send_to_tcpipsocket(Gnode, "localhost", 4096, (lmchar_t *)NULL);

// 		
// 		socketnr =  cli_open_socket("localhost", 4096);
// 		write_to_socket(1, Gnode,  socketnr);
// // 		 RecNode = Send_receive_tcpipsocket(Gnode, "localhost", 4096, (lmchar_t *)NULL);
// 		close(socketnr);
		
// 		printf("printing received node RECNODE \n\n ");
		
// 		 if(m3l_Cat(RecNode, "--recursive", "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 	    	Error("CatData");
		
// // 		
// // 		usleep(10000);
// // 		
// // 		exit(0);
// 		
// 		
// 		
// 		
// 		printf(" Looking for data set\n");
// 		
// 		if( ( Founds = m3l_Find(Gnode, "--recursive" ,"BBB_DATA_DADA", (lmchar_t *)NULL)) == NULL){
// 
// 			printf("No subset found\n"); exit(0);
// 			}
// 		else
// 		{
// 			for(i=0; i < Founds->founds; i++){
// 			printf(" Found name is %s  %p   %s\n", Founds->Found_Nodes[i]->List->name, Founds->Found_Nodes[i]->List, Founds->Found_Nodes[i]->List->type);
// 			}
// 
// 		m3l_DestroyFound(&Founds);
// 
// 		}
// 			
// // 
// // 
// 		if(m3l_Cat(Gnode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 	                   Error("CatData");
// 						
// 		
// 		if(m3l_Umount(&Gnode) != 1)
//                   Perror("m3l_Umount");
// 		
// 		exit(0);
// // 		if(m3l_Umount(&RecNode) != 1)
// //                   Perror("m3l_Umount");
// 				
// 	}
// 		
// 
// 		exit(0);

				
// 		printf("Going to locate %p\n", Gnode);
// 		if( (Founds = m3l_Locate(Gnode, "/main/grid1/boundary", "/*/SV_name_of_grid=CFD_grid/*", "--ignore", (lmchar_t *)NULL)) != NULL){
// 		if( (Founds = m3l_Locate(Gnode, "./grid1/boundary", "/*/SV_name_of_grid=CFD_grid/*", "--ignore", (lmchar_t *)NULL)) != NULL){

//  		if( (Founds = m3l_Locate(Gnode, "/main/grid1/*", "/*/*/*", "--ignore", (lmchar_t *)NULL)) != NULL){
//  		if( (Founds = m3l_Locate(Gnode, "/main/grid1/*", "/*/SV_name_of_grid=CFD_grid/*", "--ignore", (lmchar_t *)NULL)) != NULL){
// //  		if( (Founds = m3l_Locate(Gnode, "/main/*/boundary", "/*/*/*", "--ignore", (lmchar_t *)NULL)) != NULL){
//  		if( (Founds = m3l_Locate(Gnode, "/*/*", "/*/*", "--ignore", (lmchar_t *)NULL)) != NULL){
			
// 			for(i=0; i < Founds->founds; i++){
// 				printf(" Found name is %s  %p   %s\n", Founds->Found_Nodes[i]->List->name, Founds->Found_Nodes[i]->List, Founds->Found_Nodes[i]->List->type);
// 
// 				if( (node_path = m3l_Path(Founds->Found_Nodes[i]->List, NULL)) != NULL){
// 					printf(" m3l_Path is %s \n", node_path);
// 					free(node_path);
// 				}
// 				
// 				 if(m3l_Cat(Founds->Found_Nodes[i]->List, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 					Error("CatData");
// 			}
// 		m3l_DestroyFound(&Founds);
// 		}
// 		else
// 		{
// 			printf(" No founds\n");
// 		}
		
		
// 		printf("Number of removed nodes is %ld\n", m3l_Rm(&Gnode , "/main/grid1/boundary", "/*/SV_name_of_grid=CFD_grid/*",  "--keepheadnode", (lmchar_t *)NULL) );
// 		printf("Number of removed nodes is %ld\n", m3l_Rm(&Gnode , "/main/grid1/boundary", "/*/SV_name_of_grid=CFD_grid/n=2",  "--keepheadnode", (lmchar_t *)NULL) );

			   
//  		m3l_Cp(Gnode, "/main/Additional_directory/Belonging_to_ADDDATA/BBB_DATA_DADA", "/*/*/*/*", &Gnode, "/main/grid3", "/*/*", (lmchar_t *)NULL);   
//  		m3l_Cp(Gnode, "/main/grid1/boundary/name", "/*/SV_name_of_grid=CFD_grid/n=1/*", &Gnode, "/main/grid3", "/*/*", (lmchar_t *)NULL);   
//  		m3l_Cp(Gnode, "/main/Additional_directory/Belonging_to_ADDDATA/BBB_DATA_DADA", "/*/*/*/n=2", &Gnode, "/main/ADA", "/*/*", (lmchar_t *)NULL);   
//     		m3l_Cp(Gnode, "/main/Additional_directory/Belonging_to_ADDDATA/BBB_DATA_DADA", "/*/*/*/*", &Gnode, "/main/grid3/BBDD_NEWName", "/*/*/*", (lmchar_t *)NULL);
// 		m3l_Cp(Gnode, "/main/grid1", "/*/SV_name_of_grid=CSM_grid", &Gnode, "/main/grid1/GRID_grid1", "/*/SV_name_of_grid=CFD_grid/*", (lmchar_t *)NULL);   /* rename node */
// 		m3l_Cp(Gnode, "/main/grid1/name_of_grid", "/*/SV_name_of_grid=CSM_grid/N=name_of_grid", &Gnode, "/main/grid1/name_GRID_grid1", "/*/SV_name_of_grid=CSM_grid/*", (lmchar_t *)NULL); 
// 		m3l_Cp(Gnode, "/main/grid1", "/*/SV_name_of_grid=CSM_grid", &Gnode, "/main/ADD_grid1", "/*/*", (lmchar_t *)NULL);   /* rename node */
// 		m3l_Cp(Gnode, "/main/grid1/boundary", "/*/SV_name_of_grid=CSM_grid/SV_type=Wall", &Gnode, "BouNdaRy", "./*", (lmchar_t *)NULL); 
// 		m3l_Cp(Gnode, "/main/grid1/boundary/type", "/*/SV_name_of_grid=CSM_grid/n=1/n=1", &Gnode, "/main/grid1/boundary/BouNdaRy", "/*/n=1/n=1/*", (lmchar_t *)NULL); 
		m3l_Cp(&Gnode, "/main/grid1/boundary", "/*/*/SV_type=Wall", &Gnode, "BouNdaRy", "./", (lmchar_t *)NULL);
		m3l_Cp(&Gnode,  "/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/SV_name=Wing/*", &Gnode, 
				"/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/SV_name=Fuselage/*", "--add", (lmchar_t *)NULL); 

		
// 		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 			Error("CatData");
		
// 		exit(0);
		
		
//   		m3l_Cp(Anode, "/Main_DATA_Structure/Additional_directory", "/*/*", &Gnode, "/main/grid1/boundary/typeNew", "/*/SV_name_of_grid=CSM_grid/n=2/*", (lmchar_t *)NULL);   /* rename node */

				   
//   		m3l_Cp(Gnode, "/main/grid1/boundary", "/*/SV_name_of_grid=CSM_grid/SV_type=Wall", &Gnode, "/main", "/*", (lmchar_t *)NULL);   


//   		m3l_Mv(&Gnode, "/main/grid1/boundary", "/*/SV_name_of_grid=CSM_grid/SV_type=Wall", &Gnode, "BouNdaRy", "./*", (lmchar_t *)NULL);   /* rename node */
		m3l_Mv(&Gnode, "/main/grid1", "/*/SV_name_of_grid=CSM_grid", &Gnode, "/main/grid1", "/*/SV_name_of_grid=CFD_grid", (lmchar_t *)NULL);   /* rename node */
// 		Mv(&Gnode, "/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/n=1/n=1", &Gnode, "/main/grid1/boundary/type", "/*/SV_name_of_grid=CSM_grid/n=2/n=1", (lmchar_t *)NULL);   /* rename node */
// 		Mv(&Gnode, "/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/n=1/n=1", &Gnode, "/main/grid1/boundary/name_new", "/*/SV_name_of_grid=CSM_grid/n=2/*", (lmchar_t *)NULL);   /* rename node */


//  		m3l_Ln(&Gnode, "/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/n=1/n=1", &Gnode, "/main/grid1/boundary/type", "/*/SV_name_of_grid=CSM_grid/n=2/n=1", (lmchar_t *)NULL);   /* rename node */
//   		m3l_Ln(&Gnode, "/main/grid1/boundary/name", "/*/SV_name_of_grid=CSM_grid/n=1/n=1", &Gnode, "/main/grid1/boundary/typeNew", "/*/SV_name_of_grid=CSM_grid/n=2/*", (lmchar_t *)NULL);   /* rename node */
//  		m3l_Ln(&Gnode, "/main/grid1/boundary", "/*/SV_name_of_grid=CSM_grid/n=1", &Gnode, "/main/grid1/boundary/typeNew", "/*/SV_name_of_grid=CSM_grid/n=2/*", (lmchar_t *)NULL);   /* rename node */
  		m3l_Ln(&Anode, "/Main_DATA_Structure/Additional_directory", "/*/*", &Gnode, "/main/grid1/boundary/typeNewLINK", "/*/SV_name_of_grid=CSM_grid/n=2/*", (lmchar_t *)NULL);   /* rename node */

// 		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 			Error("CatData");
		
		printf(" \n\n\n Copying link \n\n\n");
		m3l_Cp(&Gnode, "/main/grid1/boundary/typeNewLINK", "/*/*/*/*", &Gnode, "/main/grid3", "/*/*", (lmchar_t *)NULL); 
// 		m3l_Cp(Gnode, "/main/grid1/boundary/typeNewLINK", "/*/SV_name_of_grid=CSM_grid/n=1/*", &Gnode, "/main/grid3", "/*/*", (lmchar_t *)NULL); 

		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
			Error("CatData");
		
		
		if( (Founds = m3l_Locate(Anode, "/Main_DATA_Structure/Additional_directory", "/*/*", "--ignore", (lmchar_t *)NULL)) != NULL){
			
			for(i=0; i < Founds->founds; i++){
				printf(" Found name is %s  %p   %s\n", Founds->Found_Nodes[i]->List->name, Founds->Found_Nodes[i]->List, Founds->Found_Nodes[i]->List->type);

				if( (node_path = m3l_Path(Founds->Found_Nodes[i]->List, NULL)) != NULL){
					printf(" m3l_Path is %s \n", node_path);
					free(node_path);
				}
				
				 if(m3l_Cat(Founds->Found_Nodes[i]->List, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
					Error("CatData");
				 
				 printf("Number of links is %d\n", Founds->Found_Nodes[i]->List->lcounter);
				 for(j=0; j < Founds->Found_Nodes[i]->List->lcounter; j++)
					 printf("-  %p\n", Founds->Found_Nodes[i]->List->linknode[j]->List);
			}
		m3l_DestroyFound(&Founds);
		}
		else
		{
			printf(" No founds\n");
		}
		
// 		m3l_Fwrite(Gnode, "ADA", (lmchar_t *)NULL);
// 		printf("\n\n\n\n");

// 		 if(m3l_Cat(Anode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
//  	                   Error("CatData");
// 		
// 		printf("\n\n\n\n");
		
// 		printf("\n\n\n\n");
// 		if(m3l_Cat(Gnode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
// 			Error("CatData");
// 		

		if(m3l_Umount(&Anode) != 1)
			Perror("m3l_Umount");
		
// 		printf("Number of removed nodes is %ld\n", m3l_Rm(&Anode , "/Main_DATA_Structure", "/*", "--clean_empty_refs_to_links",  (lmchar_t *)NULL) );
		
		
		if(m3l_Cat(Anode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
//  	                   Error("CatData");
// 			   exit(0);

		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
			Error("CatData");
		m3l_Fwrite(Gnode, "ADA_EMPTYLINK", (lmchar_t *)NULL);
		printf("\n\n\n\n");
		
// 		Send_to_tcpipsocket(Gnode, "localhost", 4096, (lmchar_t *)NULL);

// 		printf(" Number of empty links is %ld \n", ln_cleanempytlinks(&Gnode,  (opts_t *)NULL) );
		printf(" Number of empty links is %ld \n", m3l_Ln(NULL, NULL, NULL, &Gnode, NULL, NULL, "--clean_empty_refs_to_links", (lmchar_t *)NULL));	
		printf(" Number of empty links is %ld \n", m3l_Ln(NULL, NULL, NULL, &Gnode, NULL, NULL, "--clean_empty_links", (lmchar_t *)NULL));	
		
		printf("\n\n\n\n CLEANING EMPTY LINKS == \n\n\n");


		dim = (size_t *) malloc( 1* sizeof(size_t));
		dim[0] = 10;
// 		if(  (NewList = m3l_Mklist("MADE_LIST", "I", 1, dim, (node_t **)NULL, (const lmchar_t *)NULL, (const lmchar_t *)NULL, (lmchar_t *)NULL)) == 0)
	 	if(  (NewList = m3l_Mklist("MADE_LIST", "I", 1, dim, &Gnode, "/main", "./", (lmchar_t *)NULL)) == 0)
			Error("Mklist");
		free(dim);
		for (i=0; i<10; i++)
 			NewList->data.i[i]=2*i;

 		if(m3l_Cat(NewList,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
 			Error("CatData");
		
// 		Add(&NewList, &Gnode, "/main/grid3", "/*/*", (lmchar_t *)NULL);
// 		Add(&NewList, &Gnode, "/main", "./", (lmchar_t *)NULL);
			
// 		NewList = NULL;
		dim = (size_t *) malloc( 1* sizeof(size_t));
		dim[0] = 5;
// 		ada = (lmint_t *)malloc(5 * sizeof(lmint_t));
		for (i=0; i<5; i++)
 			ada[i]=3*i;
		
		if(  (NewList = m3l_Mklist("MADE_LIST_ADA", "I", 1, dim, &Gnode, "/main", "./", "--no_malloc", (lmchar_t *)NULL)) == 0)
			Error("Mklist");
		free(dim);
// 		for (i=0; i<5; i++)
//  			NewList->data.i[i]=2*i;
 		NewList->data.i = ada;
		
		
		printf("WRITING DATA to socket\n");
// 		printf(" Number of removed nodes is %d\n", m3l_Rm(&Gnode , "/main/EEEE", "/*/*", (lmchar_t *)NULL));
		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
			Error("CatData");

		if( (RecNode = m3l_Send_receive_tcpipsocket(Gnode, "localhost", 4096, "--encoding" , "IEEE-754", "--buffering", "MEMCPY", (lmchar_t *)NULL)) == NULL)
			Perror("Send_receive");
		printf("EXIT WRITING DATA to socket\n");

		if(m3l_Umount(&RecNode) != 1)
			Perror("m3l_Umount");
		

		
		if(m3l_Cat(Gnode,  "--all", "--links", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
			Error("CatData");

		if(m3l_Umount(&Gnode) != 1)
			Perror("m3l_Umount");
		
// 		free(ada);
		
// 		if(m3l_Umount(&Anode) != 1)
// 			Perror("m3l_Umount");	
		
	}
		
		
		exit(0);
		
	
// 		
// 		
// 		exit(0);
// 		
	   
	   
/*	   if( m3l_Fwrite(Gnode,  "ADA_TEST") != 0)
		   Perror("Lin*ked_test: m3l_Fwrite");
		   */
	   
// 	     if( ( Found_Nodes = m3l_Find(Gnode, , "--recursive" ,"Belonging_to_ADDDATA", (lmchar_t *)NULL)) == NULL){
  		if( ( Founds = m3l_Find(Gnode,  "--recursive" ,"boundary", (lmchar_t *)NULL)) == NULL){

			printf("No subset found\n"); exit(0);
		}
		else
		{
			for(i=0; i < Founds->founds; i++){
			printf(" Found name is %s  %p   %s\n", Founds->Found_Nodes[i]->List->name, Founds->Found_Nodes[i]->List, Founds->Found_Nodes[i]->List->type);
			}
	
		m3l_DestroyFound(&Founds);

		}
		
		
		
		printf(" cut data\n");
		if(m3l_Cat(Gnode, "--recursive", "-D", "-P", "BBB_DATA_DADA", (lmchar_t *)NULL) != 0)
			Error("CatData");
		printf("\n\n\n");

	   
	   printf("Number of removed nodes is %ld\n", Rm(&Gnode , "--recursive" , "--ignore", "BBB_DATA_DADA", (lmchar_t *)NULL) );
	   if(m3l_Cat(Gnode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
	                   Error("CatData");
	   
	   
	   	socketnr =  cli_open_socket("localhost", 4096);
		write_to_socket(1, Gnode,  socketnr);
		close(socketnr);
	   
	   
	   if(m3l_Umount(&Gnode) != 1)
                  Perror("m3l_Umount");
  	exit(0);
	   
// 	}
	   
	   
	   
//	   send_to_tcpipsocket(Gnode, "localhost", 4096);
			   
//	    RecNode = send_receive_tcpipsocket(Gnode, "localhost", 4096);
          
	    
	    printf("\n\n\n Umounting \n\n\n");

	    printf("Number of removed nodes is %ld\n", Rm(&Tmpnode , "--recursive" , "--ignore", "BBB_DATA_DADA", (lmchar_t *)NULL) );
//	    if(m3l_Cat(RecNode, "--all", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
	                   Error("CatData");
	    
	    
	    
	   
	/*      socketnr =  cli_open_socket("localhost", 4096);
		write_to_socket(1, Gnode,  socketnr);
	      close(socketnr);
*/

	if(m3l_Umount(&Gnode) != 1)
                  Perror("m3l_Umount");
	if(m3l_Umount(&RecNode) != 1)
                  Perror("m3l_Umount");
    
//	}    
    exit(0);
    
    
    
    for (i=0; i<1000000; i++){
    
/*
 * loop over list and print it
 */
	   printf("\n\n\n m3l_Cat \n\n\n");
   if(m3l_Cat(Gnode, "-D", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
	    	Error("CatData");
	printf("\n\n\n");
   

   
	}


      if(m3l_Umount(&Gnode) != 1)
                  Perror("m3l_Umount");


 //  }
   
   
   	   printf("\n\n\n m3l_Cat \n\n\n");
   if(m3l_Cat(Gnode, "--recursive", "-D", "-P", "BBB_DATA_DADA", (lmchar_t *)NULL) != 0)
	    	Error("CatData");
	printf("\n\n\n");

/*
 * function allocates **find_t pointer, after use must be freed
 */	  
	 printf("Looking for Additional_direcotry node\n");

   if( ( Founds = m3l_Find(Gnode, "Additional_directory", (lmchar_t *)NULL)) == NULL){

	   printf("No subset found\n"); exit(0);
   }
   else
   {
	for(i=0; i < Founds->founds; i++){
		printf(" Found name is %s  %p   %s\n", Founds->Found_Nodes[i]->List->name, Founds->Found_Nodes[i]->List, Founds->Found_Nodes[i]->List->type);
	}
   }
   
   
   	 printf("m3l_Cat Additional_direcotry node\n");

        if(m3l_Cat(Founds->Found_Nodes[0]->List, "-D", "-P", "-L","*", (lmchar_t *)NULL) != 0)
	    	Error("CatData");
	
	printf("writing to socklet\n");
	
	   socketnr =  cli_open_socket("localhost", 4096);
		write_to_socket(1, Founds->Found_Nodes[0]->List,  socketnr);
	   close(socketnr);

   	 printf("Removing Additional_directory node\n");

	Tmpnode = Founds->Found_Nodes[0]->List;

//        printf("Number of removed nodes is %ld\n", Rm(&Tmpnode , "--recursive" , "--ignore", "BBB_DATA_DADA", (lmchar_t *)NULL) );

	printf("Number of removed nodes is %ld\n", Rm(&Founds->Found_Nodes[0]->List , "--recursive" , "*", (lmchar_t *)NULL) );
	
//	if(m3l_Cat(Found_Nodes[0]->List, "-d", "-P", "*", (lmchar_t *)NULL) != 0)
//	    	Error("CatData");

        printf("Freeing memory - number of founds is %ld\n", Founds->founds);
   
	m3l_DestroyFound(&Founds);

   
	printf("\n\n\n m3l_Cat \n\n\n");
	if(m3l_Cat(Gnode, "-D", "-P", "-L", "*", (lmchar_t *)NULL) != 0)
	Error("CatData");
  
  
    printf("\n\n\nRemoving nodes Master head node\n\n\n");

    if(m3l_Umount(&Gnode) != 1)
	    Perror("m3l_Umount");
    
    printf("\n %p", Gnode);
	
  return 0;

}
