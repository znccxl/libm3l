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
 *     Header file tcpip_socket_IOop.h
 *
 *     Date: 2012-06-24
 * 
 *
 *     Modifications:
 *     Date		Version		Patch number		CLA 
 *
 *
 *     Description
 *
 */



#ifndef __TCPIP_SOCKET_OP_H__
#define __TCPIP_SOCKET_OP_H__

extern int m3l_Client_Sent_to_tcpipsocket(node_t *, const char *, int , char * , ...);
extern node_t *m3l_Client_Send_receive_tcpipsocket(node_t *, const char *, int, char * , ... );
extern node_t *m3l_Client_Receive_send_tcpipsocket(node_t *, const char *, int , char * , ...);
extern node_t *m3l_Client_Receive_tcpipsocket(const char *, int , char *, ...);

extern int m3l_client_send_to_tcpipsocket(node_t *, const char *, int , opts_t *);
extern node_t *m3l_client_send_receive_tcpipsocket(node_t *, const char *, int , opts_t *);
extern node_t *m3l_client_receive_send_tcpipsocket(node_t *, const char *, int , opts_t *);
extern node_t *m3l_client_receive_tcpipsocket(const char *, int, opts_t *);

#endif
