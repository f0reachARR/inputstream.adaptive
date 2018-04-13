/*
*      Copyright (C) 2018 peak3d
*      https://github.com/peak3d
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  <http://www.gnu.org/licenses/>.
*
*/

#include "crypto_session_jni.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "jni/src/MediaDrm.h"
#include "jni/src/UUID.h"
#include "jni/src/Log.h"

CryptoServer::CryptoServer(int port)
  : m_sockfd(socket(AF_INET, SOCK_STREAM, 0))
  , m_port(port)
  , m_thread(&CryptoServer::cryptoThreadFunc, this)
{
}

CryptoServer::~CryptoServer()
{
  close(m_sockfd);
  m_sockfd = -1;
  m_thread.join();
}

void CryptoServer::cryptoThreadFunc()
{
  Log(0,"Starting CryptoServer thread");
  struct sockaddr_in serv_addr, cli_addr;
  char buffer[256];

  if (m_sockfd < 0)
    return;

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(m_port);
  if (bind(m_sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
  {
    close(m_sockfd);
    m_sockfd = -1;
    Log(2,"Error binding CryptoServer listener on port %d", m_port);
    return;
  }

  listen(m_sockfd,5);

  while (true)
  {
    int clilen = sizeof(cli_addr);
    int newsockfd = accept(m_sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0)
      break;

    int n = read(newsockfd,buffer,255);
    if (n > 0)
    {


    }
    close(newsockfd);
  }
  Log(0,"Leaving CryptoServer thread");
}
