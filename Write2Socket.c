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
 *     contact: clibm3l@gmail.com
 * 
 */



/*
 *     Function Write2Socket.c
 *
 *     Author: Adam Jirasek
 *     Date: 2012-06-24
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
 *     Date		Version		Patch number		Author			Descritpion
 *
 */




 
#include "Header.h"
#include "format_type.h"
#include "FunctionsPrt.h"
#include "Write2Socket.h"
#include "format_conversion_spec.h"

static int write_buffer(const char *, int, int, int);
static int write_file_data_intdescprt(node_t *, size_t , int);

char *pc, buffer[MAXLINE];
ssize_t bitcount;

/*
 * routine writes linked list structure to socket
 */
int write_to_socket(int call, node_t *List,  int socket_descrpt)
{
	node_t *Tmpnode, *Tmplist, *Tmpnext, *Tmpprev;
	size_t i, tot_dim, n;
	char buff[MAX_WORD_LENGTH+1];	
/*
 * initial call - nullify counters
 */
	if(call == 1)
		bitcount = 0;
 
	if(List == NULL){
		Warning("WriteData2Socket: NULL list");
		return -1;
	} 
 
	if(List->child == NULL){
/*
 * node does not have children, loop over next nodes
 */
	Tmpnode = List;
/*
 * child does not have children
 *
 *
 * make sure you consider empty DIRs, their -> is NULL
 */
		if(strncmp(Tmpnode->type, "DIR", 3) == 0){
			bzero(buff, sizeof(buff));
			if( (n=snprintf(buff, MAX_WORD_LENGTH,"%s%c%s%c%ld%c",Tmpnode->name, SEPAR_SIGN, Tmpnode->type,SEPAR_SIGN, Tmpnode->ndim, SEPAR_SIGN)) < 0)
    					        Perror("snprintf");
			buff[n] = '\0';
			if( write_buffer(buff, socket_descrpt,0,0) == 0 )
				Error("Writing buffer");
		}
		else
		{
/*
 * write only FILE data, if DIR is empty, it will be written in snippet above
 */
			bzero(buff, sizeof(buff));
			if( (n=snprintf(buff, MAX_WORD_LENGTH,"%s%c%s%c%ld%c",Tmpnode->name, SEPAR_SIGN, Tmpnode->type, SEPAR_SIGN, Tmpnode->ndim, SEPAR_SIGN)) < 0)
    					        Perror("snprintf");
			buff[n] = '\0';
			if( write_buffer(buff, socket_descrpt,0,0) == 0 )
				Error("Writing buffer");
/*
 * get field dimensions
 */
			if(Tmpnode->ndim > 0){
				tot_dim = 1;
				for(i=0; i<Tmpnode->ndim; i++){
						bzero(buff, sizeof(buff));
					if( (n=snprintf(buff, MAX_WORD_LENGTH,"%ld%c",Tmpnode->fdim[i], SEPAR_SIGN)) < 0)
								Perror("snprintf");
					buff[n] = '\0';
					if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
						tot_dim = tot_dim * Tmpnode->fdim[i];
				}
/*
 * write data
 */
				write_file_data_intdescprt(Tmpnode, tot_dim, socket_descrpt);
			}
		}
/*
 * jump to next node
 */
		Tmpnode = Tmpnode->next;
	}
	else	{
/*
 * node has children, it is type DIR, write its head 
 */
		Tmplist = List;
// 		if( strncmp(List->type, "LINK", 4 ) == 0) 
// 			Tmplist = Tmplist ->child;  /* list is populated by the target list where it points to */

		bzero(buff, sizeof(buff));
		if( (n=snprintf(buff, MAX_WORD_LENGTH,"%s%c%s%c%ld%c",Tmplist->name, SEPAR_SIGN, Tmplist->type, SEPAR_SIGN, Tmplist->ndim, SEPAR_SIGN)) < 0)
	              Perror("snprintf");
		buff[n] = '\0';
		if( write_buffer(buff, socket_descrpt,0,0) == 0 )
			Error("Writing buffer");
/*
 * ... and go to its first child. Call write_to_socket recursivelly
 */
		Tmpnode = Tmplist->child;
		while(Tmpnode != NULL){
/*
 * if list is LINK, use the target node (saved in ->child) as a source of data
 */
			if( strncmp(Tmpnode->type, "LINK", 4 ) == 0){    /* NOTE change  */
/*
 * List is link, write the target
 */
				Tmplist=Tmpnode->child;
				if(Tmplist != NULL){
/*
 * save connectivity data and nullify them temporarily
 */
					Tmpnext = Tmplist->next;
					Tmpprev = Tmplist->prev;
					Tmplist->next = NULL;
					Tmplist->prev = NULL;				
					
					if(write_to_socket(2, Tmplist,socket_descrpt) != 0){
/*
 * restore original state
 */
						Tmplist->next = Tmpnext;
						Tmplist->prev = Tmpprev;
						Warning("Write data problem");
						return -1;
					}
/*
 * restore original state
 */
					Tmplist->next = Tmpnext;
					Tmplist->prev = Tmpprev;
				}
				else{
/*
 * empty LINK
 */					
					if(write_to_socket(2, Tmpnode,socket_descrpt) != 0){
						Warning("Write data problem");
						return -1;
					}
				}
			}				
			else{
				if(write_to_socket(2, Tmpnode,socket_descrpt) != 0){
					Warning("Write data problem");
					return -1;
				}
			}
			Tmpnode = Tmpnode->next;
		}
	}
/*
 * SEND LAST DATA TO SOCKET, do not forget to send EOMB instruction if ending initial call (ie call == 1)
 * call write_buffer with force = 1 to force sending the last piece of information
 */
	if(call == 1){
		bzero(buff, sizeof(buff));
		if( (n=snprintf(buff, MAX_WORD_LENGTH,EOFbuff)) < 0)
			Perror("snprintf");
		buff[n] = '\0';
		if( write_buffer(buff, socket_descrpt,1,0) == 0 )
			Error("Writing buffer");
	}
	return 0;
}

/*
 * function writes actual data of the FILE, need to distinguish between the type of field
 */
int write_file_data_intdescprt(node_t *Tmpnode, size_t tot_dim, int socket_descrpt)
{	
	size_t i, n;
	char *pc;
	char buff[MAX_WORD_LENGTH+1];
/*
 * find type of the argument - Floats
 */
		if (strncmp(Tmpnode->type,"LD",2) == 0){  /* long double */
/*
 * loop over all elements of filed
 */
			for (i=0; i<tot_dim; i++){
/*
 * clean buff and write in i-th element of the field
 */
				bzero(buff, sizeof(buff));
				if( (n= FCS_W_LD(Tmpnode->data.ldf[i], SEPAR_SIGN)) < 0){
	      			       	Perror("snprintf");
					return -1;
				}
/*
 * set the last element of the buff to \0 and add buff to buffer
 */
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 ){
					Error("Writing buffer");
					return -1;
				}
			} 
		}
		else if(strncmp(Tmpnode->type,"D",1) == 0){  /* double */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_D(Tmpnode->data.df[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"F",1) == 0){  /* float */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_F(Tmpnode->data.f[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
/*
 * chars, do not serialize, write as they are
 */
		else if (strncmp(Tmpnode->type,"SC",2) == 0){  /* signed char */
/*
 * clean buff and make pointer pointing at its beginning
 */
			pc = (char *)&Tmpnode->data.sc[0];
			if( write_buffer(pc, socket_descrpt,0,1) == 0 )
				Error("Writing buffer");
		}
		else if(strncmp(Tmpnode->type,"UC",2) == 0){  /* unsigned char */
			pc = (char *)&Tmpnode->data.uc[0];
			if( write_buffer(pc, socket_descrpt,0,1) == 0 )
				Error("Writing buffer");
		}
		else if(strncmp(Tmpnode->type,"C",1) == 0){  /* char */
			pc = &Tmpnode->data.c[0];
			if( write_buffer(pc, socket_descrpt,0,1) == 0 )
				Error("Writing buffer");
		}
/*
 * integers
 */
		else if(strncmp(Tmpnode->type,"ULLI",4) == 0){  /* unsigned long long  int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_ULLI(Tmpnode->data.ulli[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"SLLI",4) == 0){  /* signed long long  int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_SLLI(Tmpnode->data.slli[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"LLI",3) == 0){  /* signed long long  int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_LLI(Tmpnode->data.lli[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"ULI",3) == 0){  /* unsigned long int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_ULI(Tmpnode->data.uli[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"USI",3) == 0){  /* unsigned short int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_USI(Tmpnode->data.usi[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"SI",2) == 0){  /* short int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_SI(Tmpnode->data.si[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"UI",2) == 0){  /* unsigned int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_UI(Tmpnode->data.ui[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"LI",2) == 0){  /* long  int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_LI(Tmpnode->data.li[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"I",1) == 0){  /* int */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_I(Tmpnode->data.i[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
/*
 * counters
 */
		else if(strncmp(Tmpnode->type,"ST",2) == 0){  /* size_t */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_ST(Tmpnode->data.st[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else if(strncmp(Tmpnode->type,"PTRDF",1) == 0){  /* ptrdf_t */
			for (i=0; i<tot_dim; i++){
				bzero(buff, sizeof(buff));
				if( (n=FCS_W_PTRDF(Tmpnode->data.ptrdf[i], SEPAR_SIGN)) < 0)
	      			       	Perror("snprintf");
				buff[n] = '\0';
				if( write_buffer(buff, socket_descrpt,0,0) == 0 )
					Error("Writing buffer");
			} 
		}
		else
		{
			Error("Unknown type");
		}					
}
/*
 * function writes add data in buff to buffer
 * when the buffer is full, it is written to socket and 
 * pointer is set at the beginning of the buffer
 */ 
int write_buffer(const char *buff, int sockfd, int force, int add)
{
/*
 * force - parameter forces buffer to be written to 
 * 	socket even if it is not fully used
 * add   - parameter adds separ sing to the end, it is needed when 
 * 	chars are written in
 */

/*
 * NOTE-URGENT - check the algorithm for adding SEPAR_SIGN at the end of buffer, 
 * especially situattion after condition if(bitcount < (MAXLINE-1) && add == 1) when bitcount == MAXLINE-1
 */
	size_t n,i;
     
	while(*buff != '\0'){
		if(bitcount == (MAXLINE-1))
		{
			*(buffer+bitcount) = '\0';
			bitcount = 0;
/*
* SEND TO SOCKET
*/
			if ( (n = write(sockfd,buffer,strlen(buffer))) < 0)
				Perror("write()");
			bzero(buffer, sizeof(buffer));
		}
		*(buffer+bitcount) = *buff++;
		bitcount++;
	}
	
	if(bitcount < (MAXLINE-1) && add == 1){
/*
 * add separ sign 
 * NOTE: make sure that if bitcount here is = MAXLINE-2 and add = force then it adds SEPAR_SIGN here as well
 */
		*(buffer+bitcount) = SEPAR_SIGN;
		bitcount++;
	}
	
	if(bitcount == (MAXLINE-1))
	{
		*(buffer+bitcount) = '\0';
		bitcount = 0;
/*
* SEND TO SOCKET
*/
		if ( (n = write(sockfd,buffer,strlen(buffer))) < 0)
			Perror("write()");
		bzero(buffer, sizeof(buffer));
		
		if(add == 1 ){
/*
 * add separ sign 
 */
			*(buffer+bitcount) = SEPAR_SIGN;
			bitcount++;
		}
	}
	else if(force == 1){
/*
 * this is the end of sending processs, send everything you have in buffer regardless how long it is.
 * The last sequence of the bugger is -EOMB-
 */
		if ( (n = write(sockfd,buffer,strlen(buffer))) < 0)
			Perror("write()");	
	}
	
	return 1;
}	