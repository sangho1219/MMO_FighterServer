#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32")
#pragma comment(lib, "Winmm")
#include <WinSock2.h> 

#include <stdio.h>

#include "Protocol.h"
#include "SerializationBuffer.h"
#include "CircularBuffer.h"
#include "session.h"
#include "network.h"
#include "character.h"




