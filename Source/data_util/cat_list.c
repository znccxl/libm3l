
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
 *     Function cat_list.c
 *
 *     Date: 2012-06-12
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




 
#include "libm3l_header.h"
#include "format_type.h"
#include "internal_format_type.h"
#include "format_conversion_spec.h"
#include "FunctionsPrt.h"
#include "cat_list.h"

static lmint_t m3l_cat_data(node_t *, size_t);


static void m3l_PrintListInfo(node_t *, opts_t *);

/*
 * routine writes linked list structure
 */

lmint_t m3l_cat_list(lmint_t call, node_t *List, opts_t *Popts)
{
/*
 * functions print the list or entire tree on screen
 *  - if the specified node is DIR type, it prints all files in that directory
 *  - if specified node is FILE type, it prints only list and its content
 * 
 * upon first call, the value of int call should be set to 1
 *
 * options specifies how much info is going to be print out
 *
 * Upon return function returns:
 *    1 - if sucess
 *    0 of no scenario where and how to add a node was found
 *   -1 if node which is to be added (*List) is NULL
 */
	node_t *Tmpnode, *Tmpcld;
 
	if(List == NULL){
		Warning("WriteData: NULL list");
		return -1;
	}
	
	if(strncmp(List->type, "LINK",4) != 0){
/*
 * List is not linke
 */
 
	if(List->child == NULL ){
/*
 * print node info
 */
			m3l_PrintListInfo(List, Popts);
		}
		else
		{
/*
 * initil call
 */
			m3l_PrintListInfo(List, Popts);
			
			if(call == 1){
				Tmpnode = List->child;
				while(Tmpnode != NULL){
/*
 * if node is list and option specifies it, write the target node data
 */
					if( strncmp(Tmpnode->type, "LINK", 4 ) == 0  && Popts->opt_l == 'l'){
						if(m3l_cat_list(2, Tmpnode->child, Popts) != 0){ /* list is populated by the target list where it points to */
							Warning("Write data problem");
							return -1;
						}
					}
					else{
		
						if(m3l_cat_list(2, Tmpnode, Popts) != 0){
							Warning("Write data problem");
							return -1;
						}
					}
				Tmpnode = Tmpnode->next;
				}
			}
/*
 * recursive call or call with specified parameter 2
 * if -L == --listsubdir go to lower level
 */
			else if(call == 2 && Popts->opt_L == 'L' && strncmp(List->type, "LINK", 4 ) != 0   ){
				Tmpnode = List->child;
				while(Tmpnode != NULL){
					if(m3l_cat_list(2, Tmpnode, Popts) != 0){
						Warning("Write data problem");
						return -1;
					}
					Tmpnode = Tmpnode->next;
				}
			}
		}
		return 0;
	}
	else{
/*
 * list is LINK
 */
		m3l_PrintListInfo(List, Popts);		
		if(Popts->opt_l == 'l'){
/*
 * List Linked list too
 */
			printf("--->");
/* 
 * set Tmp node to link source address
 * and nullify temporarily the next node
 */
			Tmpnode = List->child;

			if(Tmpnode != NULL){
				printf("\n");
/*
 * LINK is not empty link
 */
				Tmpcld = Tmpnode->next;
				Tmpnode->next = NULL;
				
				if(m3l_cat_list(2, Tmpnode, Popts) != 0){
					Warning("Write data problem");
/*
 * restore the previuous state - set next node to its original value
 */
					Tmpnode->next = Tmpcld;
					return -1;
				}
				printf("<---\n");
/*
 * set next node to its original value
 */
				Tmpnode->next = Tmpcld;
			}
			else{
/*
 * LINK is empty link
 */
				printf("empty link ");
				printf("<---\n");
			}
		}
		return 0;
	}
/*
 * if you end up here from whatever reason, return error value
 */
	return -1;
}


void m3l_PrintListInfo(node_t *List, opts_t *Popts)
{
size_t i, maxdim, tabs;
node_t *Tmp;

	if( Popts->opt_s == 'a'){
		if(List->parent == NULL){
			if(Popts->opt_p == 'p'){
				printf("H-%s\t%p\t", List->type, List);
			}
			else
			{
				printf("H-%s\t", List->type);
			}
		}
		else
		{
			if(Popts->opt_p == 'p'){
				printf(" -%s\t%p\t", List->type, List);
			}
			else
			{
				printf(" -%s\t", List->type);
			}
		}
		
		Tmp = List;
		tabs = 0;
		while(Tmp->parent != NULL)
		{
			printf("\t");
			Tmp = Tmp->parent;
			tabs++;
		}
		printf(" %s \t\t %ld\t", List->name, List->ndim);
		if(strncmp(List->type,"DIR",3) != 0 && strncmp(List->type,"LINK",4) != 0 ){
			maxdim = 1;
			for (i=0; i<List->ndim; i++){
				printf("%ld   ", List->fdim[i]);
				maxdim = maxdim * List->fdim[i] ;
			}
			printf("\n");

			for(i=0; i<=tabs+3; i++)
				printf("\t");		
/*
 * decide what type of data is here, at the moment, only integers
 */
			if( m3l_cat_data(List, maxdim) != 0)
				Error("cat_data");
		}
		printf("\n");
	}
	else if (Popts->opt_s == 'd'){
		if(List->parent == NULL){
			if(Popts->opt_p == 'p'){
				printf("H-%s\t%p\t", List->type, List);
			}
			else
			{
				printf("H-%s\t", List->type);
			}
		}
		else
		{
			if(Popts->opt_p == 'p'){
				printf(" -%s\t%p\t", List->type, List);
			}
			else
			{
				printf(" -%s\t", List->type);
			}
		}
		
		Tmp = List;
		while(Tmp->parent != NULL)
		{
			printf("\t");
			Tmp = Tmp->parent;
		}
		printf(" %s \t\t %ld\t", List->name, List->ndim);
		if(strncmp(List->type,"DIR",3) != 0 && strncmp(List->type,"LINK",4) != 0 ){
			for (i=0; i<List->ndim; i++)
				printf("%ld   ", List->fdim[i]);
			}
		printf("\n");
	}
	else if (Popts->opt_s == 'q'){
		printf("%s\t%s\n", List->type, List->name);
	}
	else
	{
		printf("%s\t", List->name);
	}
	return;
}





lmint_t m3l_cat_data(node_t *Tmpnode, size_t tot_dim)
{
	
	size_t i;
	
		if (strncmp(Tmpnode->type,"LD",2) == 0){  /* long double */
			for (i=0; i<tot_dim; i++)
				FCS_C_LD(Tmpnode->data.ldf[i]);
		}
		else if(strncmp(Tmpnode->type,"D",1) == 0){  /* double */
			for (i=0; i<tot_dim; i++)
				FCS_C_D(Tmpnode->data.df[i]);
		}
		else if(strncmp(Tmpnode->type,"F",1) == 0){  /* float */
			for (i=0; i<tot_dim; i++)
				FCS_C_F(Tmpnode->data.f[i]);
		}
/*
 * chars
 */
		else if (strncmp(Tmpnode->type,"SC",2) == 0){  /* signed char */
/*
 * clean buff and make pointer pointing at its beginning
 */
			for (i=0; i<tot_dim; i++)   /* use of while( Tmpnode->data.sc[i++] != 0)  */
				printf("%c", Tmpnode->data.sc[i]);
		}
		else if(strncmp(Tmpnode->type,"UC",2) == 0){  /* unsigned char */
			for (i=0; i<tot_dim; i++)
				printf("%c", Tmpnode->data.uc[i]);
		}
		else if(strncmp(Tmpnode->type,"C",1) == 0){  /* char */
			for (i=0; i<tot_dim; i++) // do not count for '\0' symbol
				printf("%c", Tmpnode->data.c[i]);
		}
/*
 * integers
 */
		else if(strncmp(Tmpnode->type,"ULLI",4) == 0){  /* unsigned long long  int */
			for (i=0; i<tot_dim; i++)
				FCS_C_ULLI(Tmpnode->data.ulli[i]);
		}
		else if(strncmp(Tmpnode->type,"SLLI",4) == 0){  /* signed long long  int */
			for (i=0; i<tot_dim; i++)
				FCS_C_SLLI(Tmpnode->data.slli[i]);
		}
		else if(strncmp(Tmpnode->type,"LLI",3) == 0){  /* signed long long  int */
			for (i=0; i<tot_dim; i++)
				FCS_C_LLI(Tmpnode->data.lli[i]);
		}
		else if(strncmp(Tmpnode->type,"ULI",3) == 0){  /* unsigned long int */
			for (i=0; i<tot_dim; i++)
				FCS_C_ULI(Tmpnode->data.uli[i]);
		}
		else if(strncmp(Tmpnode->type,"USI",3) == 0){  /* unsigned short int */
			for (i=0; i<tot_dim; i++)
				FCS_C_USI(Tmpnode->data.usi[i]);
		}
		else if(strncmp(Tmpnode->type,"SI",2) == 0){  /* short int */
			for (i=0; i<tot_dim; i++)
				FCS_C_SI(Tmpnode->data.si[i]);
		}
		else if(strncmp(Tmpnode->type,"UI",2) == 0){  /* unsigned int */
			for (i=0; i<tot_dim; i++)
				FCS_C_UI(Tmpnode->data.ui[i]);
		}
		else if(strncmp(Tmpnode->type,"LI",2) == 0){  /* long  int */
			for (i=0; i<tot_dim; i++)
				FCS_C_LI(Tmpnode->data.li[i]);
		}
		else if(strncmp(Tmpnode->type,"I",1) == 0){  /* int */
			for (i=0; i<tot_dim; i++)
				FCS_C_I(Tmpnode->data.i[i]);
		}
/*
 * counters
 */
		else if(strncmp(Tmpnode->type,"ST",2) == 0){  /* size_t */
			for (i=0; i<tot_dim; i++)
				FCS_C_ST(Tmpnode->data.st[i]);
		}
		else if(strncmp(Tmpnode->type,"PTRDF",1) == 0){  /* ptrdf_t */
			for (i=0; i<tot_dim; i++)
				FCS_C_PTRDF(Tmpnode->data.ptrdf[i]);
		}
		else
		{
			Error("Unknown type");
			return -1;
		}	
		return 0;
	
}