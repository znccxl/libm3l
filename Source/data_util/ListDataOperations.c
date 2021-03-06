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
 *     Function FunctionsArrays.c
 *
 *     Date: 2012-07-06
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
#include "FunctionsPrt.h"
#include "internal_format_type.h"
#include "ListDataOperations.h"

/*
 * function get index of 1D array from n-dimensional array
 */
lmsize_t m3l_get_ind(lmsize_t ndim, lmsize_t *ind,  lmsize_t *dim)
{
	lmsize_t ret_ind, tmp,k,l;
	
	ret_ind = 0;
	for (k=0; k<ndim-1; k++){
		
		tmp = 1;
		
		for (l=k+1; l<ndim; l++)
			tmp = tmp*dim[l];
		
		ret_ind = ret_ind + ind[k]*tmp;
		
	}
	ret_ind = ret_ind + ind[ndim-1];
	
	return ret_ind;
}

/*
 * function get index of 1D array from 4-dimensional array
 */
lmsize_t m3l_get_4nd(lmsize_t i, lmsize_t j, lmsize_t k, lmsize_t l,  lmsize_t jm, lmsize_t km, lmsize_t lm)
{
	lmsize_t ret_ind; 	
 	ret_ind = i*jm*km*lm+j*km*lm+k*lm+l;
	
	return ret_ind;
}

/*
 * function get index of 1D array from 3-dimensional array
 */
lmsize_t m3l_get_3ind(lmsize_t i, lmsize_t j, lmsize_t k, lmsize_t jm, lmsize_t km)
{
	lmsize_t ret_ind; 	
 	ret_ind = i*jm*km+j*km+k;
	
	return ret_ind;
}

/*
 * function get index of 1D array from 2-dimensional array
 */
lmsize_t m3l_get_2ind(lmsize_t i, lmsize_t j, lmsize_t jm)
{
	lmsize_t ret_ind; 	
 	ret_ind = i*jm+j;
	
	return ret_ind;
}

/*
 * function gives pointer on ->data.# depending on the List type
 * function is of void * type 
 */
void *m3l_get_data_pointer(node_t *Lnode)
{
	node_t *TmpNode;
/*
 * if list is DIR, return NULL
 * if list is LINK, set TmpNode to link target node (Lnode->child)
 * otherwise set TmpNode = Lnode
 */
	TmpNode = Lnode;
	
	if(strncmp(Lnode->type, "LINK",4) == 0)
		TmpNode = Lnode->child;
	
	if(strncmp( TmpNode->type,"DIR",3) == 0)
		return NULL;
	
	if (strncmp(TmpNode->type,"LD",2) == 0){  /* long double */
		return (void *)TmpNode->data.ldf;
	}
	else if(strncmp(TmpNode->type,"D",1) == 0){  /* double */
		return (void *)TmpNode->data.df;
	}
	else if(strncmp(TmpNode->type,"F",1) == 0){  /* float */
		return (void *)TmpNode->data.f;
	}
/*
 * chars
 */
	else if (strncmp(TmpNode->type,"SC",2) == 0){  /* signed char */
		return (void *)TmpNode->data.sc;
	}
	else if(strncmp(TmpNode->type,"UC",2) == 0){  /* unsigned char */
		return (void *)TmpNode->data.uc;
	}
	else if(strncmp(TmpNode->type,"C",1) == 0){  /* char */
		return (void *)TmpNode->data.c;
	}
/*
 * integers
 */
	else if(strncmp(TmpNode->type,"ULLI",4) == 0){  /* unsigned long long  int */
		return (void *)TmpNode->data.ulli;
	}
	else if(strncmp(TmpNode->type,"SLLI",4) == 0){  /* signed long long  int */
		return (void *)TmpNode->data.slli;
	}
	else if(strncmp(TmpNode->type,"LLI",3) == 0){  /* long long int */
		return (void *)TmpNode->data.lli;
	}
	else if(strncmp(TmpNode->type,"ULI",3) == 0){  /* unsigned long int */
		return (void *)TmpNode->data.uli;
	}
	else if(strncmp(TmpNode->type,"USI",3) == 0){  /* unsigned short int */
		return (void *)TmpNode->data.usi;
	}
	else if(strncmp(TmpNode->type,"SI",2) == 0){  /* short int */
		return (void *)TmpNode->data.si;
	}
	else if(strncmp(TmpNode->type,"UI",2) == 0){  /* unsigned int */
		return (void *)TmpNode->data.ui;
	}
	else if(strncmp(TmpNode->type,"LI",2) == 0){  /* long  int */
		return (void *)TmpNode->data.li;
	}
	else if(strncmp(TmpNode->type,"I",1) == 0){  /* int */
		return (void *)TmpNode->data.i;
	}
/*
 * counters
 */
	else if(strncmp(TmpNode->type,"ST",2) == 0){  /* lmsize_t */
		return (void *)TmpNode->data.st;
	}
	else if(strncmp(TmpNode->type,"PTRDF",1) == 0){  /* ptrdf_t */
		return (void *)TmpNode->data.ptrdf;
	}
	
	return NULL;
}

/* 
 * return dimensions of the node
 */
lmsize_t *m3l_get_List_dim(node_t *List){
	
	node_t *TmpNode;
	
	TmpNode = List;
	
	if(strncmp(TmpNode->type, "LINK",4) == 0)
		TmpNode = List->child;
	
	return TmpNode->fdim;
}
/* 
 * calculate and return total dimensions 
 */
lmsize_t m3l_get_List_totdim(node_t *List){

	lmsize_t tot_dim, i;
	node_t *TmpNode;
	
	TmpNode = List;
	
	if(strncmp(TmpNode->type, "LINK",4) == 0)
		TmpNode = List->child;
	
	if(strncmp( TmpNode->type,"DIR",3) == 0)
		return -1;

	tot_dim = 1;
		
	if(TmpNode->ndim == 1)
		return TmpNode->fdim[0];
	else{
		for(i=0; i<TmpNode->ndim; i++)
			tot_dim = tot_dim*TmpNode->fdim[i];
		return tot_dim;
	}
}
/* 
 * return number of dimensions
 */
lmsize_t m3l_get_List_ndim(node_t *List){
	return List->ndim;
}
/* 
 * return list type 
 */
lmchar_t *m3l_get_List_type(node_t *List){
	return List->type;
}
/* 
 * return list name
 */
lmchar_t *m3l_get_List_name(node_t *List){
	return List->name;
}

/*
 * number of founds
 */
lmsize_t m3l_get_Found_number(find_t *Founds){
	return Founds->founds;
}
/* 
 * pointer to list of found nodes
 */
node_t *m3l_get_Found_node(find_t *Founds, lmsize_t i){
	return Founds->Found_Nodes[i]->List;
}
/* 
 * return no_malloc option value
 */
lmchar_t m3l_get_List_no_malloc(node_t *List){
	
	node_t *TmpNode;
	TmpNode = List;
	
	if(strncmp(TmpNode->type, "LINK",4) == 0)
		TmpNode = TmpNode->child;
	
	if(strncmp( TmpNode->type,"DIR",3) == 0)
		return 'e';
	
	
	return TmpNode->no_malloc;
}

void *m3l_detach_data_from_List(node_t **List, opts_t *Popts)
{
/*
* Function detaches the data set from the list. 
* It specifies --no_malloc='n' so that when the list is freed the 
* data.[type] structure is not freed. 
* Function return the pointer to data structure
* 
* If node is Link, it gives warning
*/
	node_t  *RetNode=NULL;
	
	if(strncmp((*List)->type, "LINK",4) == 0){
		Warning("m3l_detach_data_from_List: Can not detach LINK type list");
		return NULL;
	}
/*  
 * set --no_malloc option in the node
 */
	if( (RetNode = m3l_get_data_pointer( *List )) != NULL){
		(*List)->no_malloc = 'n';
		return RetNode;
	}
	else{
		return NULL;
	}
}

lmint_t m3l_attach_data_to_List(node_t **Lnode, opts_t *Popts){
/*
* Function attaches an array to the list. 
* This means it will specify --no_malloc='\0' so that when the list is freed the 
* data.[type] structure will be freed to.
* Function return the pointer to data structure
*/

/*  
 * set --no_malloc option in the node
 */
	if(strncmp((*Lnode)->type, "LINK",4) == 0){
		Warning("m3l_attach_data_to_List: Can not attach LINK type list");
		return -1;
	}

	if( m3l_get_data_pointer( *Lnode ) != NULL){
		(*Lnode)->no_malloc = '\0';
		return 1;
	}
	else
		return 0;
}

lmint_t m3l_RenameList(node_t *Lnode, lmchar_t *newname, opts_t *Popts){
	
	lmsize_t len;
	len = strlen(newname);
	if(len > MAX_NAME_LENGTH){
		Warning("m3l_RenameList: Node name not malloced");
		return -1;
	}
	
	if(Lnode != NULL){

		if(Lnode->name == NULL){
			Warning("m3l_RenameList: Node name not malloced");
			return -1;
		}
		
		bzero(Lnode->name, MAX_NAME_LENGTH);

		if( snprintf( Lnode->name, len,"%s", newname) < 0){
			Perror("m3l_RenameList: snprintf");
			return -1;
		}
		Lnode->name[len] = '\0';
		
		return 1;
	}
	return 0;
}

lmint_t m3l_chmod(node_t *Lnode, lmint_t ap, opts_t *Popts){

	if(Lnode != NULL){
		
		if(ap > 0){
			Warning("Wrong mode");
			return -2;
		}
		Lnode->ap = ap;
	}
	else
		return -1;
}
// node_t *m3l_reallocNode(node_t **Lnode, opts_t *Popts){
// /*
//  * function reallocates node
//  */
// 	
// }
