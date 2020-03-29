/*
 Copyright (c) 2013 Nathan LeRoux
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef _DMNET_H
#define _DMNET_H


// Some xam exports
//SOCKET	NetDll_accept(int Network, SOCKET s, struct sockaddr FAR *addr, int FAR *addrlen);
//int		NetDll_bind(int Network, SOCKET s, const struct sockaddr FAR *name, int namelen);
//int		NetDll_connect(int Network, SOCKET s, const struct sockaddr FAR *name, int namelen);
//int		NetDll_NetDll_closesocket(2, int Network, SOCKET s);
//int		NetDll_getpeername(int Network, SOCKET s, struct sockaddr FAR *name, int FAR *namelen);
//int		NetDll_getsockname(int Network, SOCKET s, struct sockaddr FAR *name, int FAR *namelen);
//int		NetDll_getsockopt(int Network, SOCKET s, int level, int optname, char FAR *optval, int FAR *optlen);
//int		NetDll_listen(int Network, SOCKET s, int backlog);
//int		NetDll_recv(int Network, SOCKET s, char FAR *buf, int len, int flags);
//int		NetDll_recvfrom(int Network, SOCKET s, char FAR *buf, int len, int flags, struct sockaddr FAR *from, int FAR *fromlen);
//int		NetDll_select(int Network, int nfds, fd_set FAR *readfds, fd_set FAR *writefds, fd_set FAR *exceptfds, const struct timeval FAR *timeout);
//int		NetDll_send(int Network, SOCKET s, const char FAR *buf, int len, int flags);
//int		NetDll_sendto(int Network, SOCKET s, const char FAR *buf, int len, int flags, const struct sockaddr FAR *to, int tolen);
//int		NetDll_setsockopt(int Network, SOCKET s, int level, int optname, char FAR *optval, int optlen);
//int		NetDll_shutdown(int Network, SOCKET s, int how);
//SOCKET	NetDll_socket(int Network, int af, int type, int protocol);
//void	NetDll_XnpNoteSystemTime(int Network);

//int		NetDll_WSASend(int Network, SOCKET s, LPWSABUF lpBuffers, DWORD dwBufferCount, LPDWORD lpNumberOfBytesSent, DWORD dwFlags,
//	LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine);


#endif