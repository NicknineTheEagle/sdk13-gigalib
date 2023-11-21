#ifndef ECON_NETWORKING_H
#define ECON_NETWORKING_H
#ifdef _WIN32
#pragma once
#endif

#ifdef PROTOBUF_USE_DLLS
#undef PROTOBUF_USE_DLLS
#endif


#ifdef _WIN32
// hack because theres no macro for DEBUG that i can find
// feel free to PR to add it to vpc if you know of one
#ifdef DEBUG
    //#pragma comment( lib, "../shared/sdk13-gigalib/bin/libprotobufd.lib" )
#else

    #pragma comment( lib, "../shared/sdk13-gigalib/bin/libprotobuf.lib" )
#endif
#endif



#define OVERRIDE override

#include "steam/isteamclient.h"
#include "steam/isteamnetworking.h"
#include "tier1/mempool.h"
#include "inetchannelinfo.h"

#include <tier0/valve_minmax_off.h>
#include "messages.pb.h"
#include <tier0/valve_minmax_on.h>


typedef uint32 MsgType_t;

#define SERVER_TIMEOUT	20

#define svc_EconMsg	35	// Horrible magic number, but 32 appears to be the last real message
						// 36 is the maximum index as it's encoded in just 6 bits

/* Peer To Peer connection definitions */
const int k_nInvalidPort = INetChannelInfo::TOTAL;
const int k_nClientPort = INetChannelInfo::TOTAL + 1; // Client <-> Client port
const int k_nServerPort = INetChannelInfo::TOTAL + 2; // Client <-> Server port

//-----------------------------------------------------------------------------
// Purpose: Interface for sending economy data over the wire to clients
//-----------------------------------------------------------------------------
abstract_class INetworking
{
public:
	virtual bool Init( void ) = 0;
	virtual void Shutdown( void ) = 0;
	virtual void Update( float frametime ) = 0;
#if defined(GAME_DLL)
	virtual void OnClientConnected( CSteamID const &id ) = 0;
	virtual void OnClientDisconnected( CSteamID const &steamID ) = 0;
#endif
	virtual bool SendMessage( CSteamID const &targetID, MsgType_t eMsg, void *pubData, uint32 cubData ) = 0;
	virtual void RecvMessage( CSteamID const &remoteID, MsgType_t eMsg, void const *pubData, uint32 const cubData ) = 0;
};

extern INetworking *g_pNetworking;


#endif
