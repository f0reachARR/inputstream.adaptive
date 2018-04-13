#pragma once
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

#include <thread>

class CryptoServer
{
public:
  CryptoServer(int port);
  virtual ~CryptoServer();

  void cryptoThreadFunc();

private:

  int m_sockfd;
  int m_port;
  std::thread m_thread;
};

