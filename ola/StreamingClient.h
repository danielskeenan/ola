/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * OlaDevice.h
 * Interface to the OLA Client Device class
 * Copyright (C) 2005 Simon Newton
 */

#ifndef OLA_STREAMINGCLIENT_H_
#define OLA_STREAMINGCLIENT_H_

#include <ola/client/StreamingClient.h>

/**
 * @file
 * @brief
 * @deprecated Include <ola/client/StreamingClient.h> instead.
 */

namespace ola {

// For backwards compatability:
typedef ola::client::StreamingClient StreamingClient;

}  // namespace ola
#endif  // OLA_STREAMINGCLIENT_H_
