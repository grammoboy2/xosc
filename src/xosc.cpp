/***************************************************************************
 *   This file is part of xosc                                   *
 *                                                                         *
 *   Copyright (C) 2013 by Marije Baalman                                  *
 *   nescivi _at_ gmail _dot_ com                                          *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        *
 *   published by the Free Software Foundation; either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <iostream>
#include <lo/lo.h>
#include <string>

#include <cstring>

#include "lo_extensions.h"

// #include "xosctypes.h"

#include "xoscclient.h"
#include "xoschost.h"
#include "xosctag.h"
#include "xosc.h"


using namespace std;

namespace XOsc {

int XOscServer::registerClientHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug ){
 	cout << "[XOscServer:client register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)( lo_address_get_hostname( addr) ) + (string)( lo_address_get_port( addr ) ) + "\n";
  }
  
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
//   string str( argv[2]->s, strnlen( argv[2]->s, 127 ) );
  bool res = server->registerClient( newaddr, argv[1]->i, (string) &argv[2]->s );
  server->sendConfirmation( newaddr, "/XOSC/register/client", res );
  return 0;
}

int XOscServer::registerHostHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
    
  if ( server->postDebug ){
 	cout << "[XOscServer:host register]: " + server->getContent( path, types, argv, argc ) + "from:" + (string)(lo_address_get_hostname( addr) ) + (string) (lo_address_get_port( addr ) ) << "\n";
  }
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  bool res = server->registerHost( addr, (string) &argv[2]->s );
  server->sendConfirmation( newaddr, "/XOSC/register/host", res );
  return 0;
}

// int XOscServer::unregisterClientHandler( handlerArgs )
// {
//   lo_address addr = lo_message_get_source( msg );
//   
//   if ( server->postDebug ){
//  	cout << "[XOscServer:client unregister]: " + server->getContent( path, types, argv, argc ) + "from:", lo_address_get_hostname( addr) + lo_address_get_port( addr ) );
// 	<< "\n";
//   }
//   
//   lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
//   res = unregisterClient( newaddr, argv[1]->i, string (argv[2]->s ) );
//   sendConfirmation( newaddr, "/XOSC/unegister/client", res );
//   return 0;
// }


int XOscServer::queryTagsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryTags] " + server->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: send back info about available tags
    server->sendTagInfo( argv[0]->i ); // TODO: how to retrieve origin address?
    return 0;
}

int XOscServer::queryConnectionsHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
    if ( server->postDebug )
    	cout << "[XOscServer::queryConnections] " + server->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: send back info about existing connections
//     server->sendConnectionInfo( argv[0]->i ); // TODO: how to retrieve origin address?
    return 0;
}

int XOscServer::registerWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::registerWatch] " + server->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: subscribe to connections and tags info
	// - send confirmation
    
    return 0;
}

int XOscServer::unregisterWatchHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    	cout << "[XOscServer::unregisterWatch] " + server->getContent( path, types, argv, argc ) << "\n";
    
  // TODO: unsubscribe to connections and tags info
    	// - send confirmation
    return 0;
}

int XOscServer::subscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  if ( server->postDebug )
     cout << "[XOscServer::subscribe] " + server->getContent( path, types, argv, argc ) << "\n";


    // TODO: subscribe the client to all tags
	// - if no subscriptions yet, create a responder for the tag
	// - subscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}

int XOscServer::unsubscribeHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::unsubscribe] " + server->getContent( path, types, argv, argc ) << "\n";


    // TODO: unsubscribe the client to all tags
	// - if no subscriptions left, remove responder for the tag
	// - unsubscribe this client
	// - if we have connection subscriptions, inform about the new connection
	// - send confirmation
    return 0;
}


int XOscServer::subscribeTagHandler( handlerArgs )
{ 
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  if ( server->postDebug )
    cout << "[XOscServer::subscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

    // TODO: subscribe the client to the tags
	// - if client does not yet exist, create a client
  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  XOscClient * myclient = server->clientExists( argv[1]->i, newaddr );
  if ( myclient == NULL ){
    myclient = server->createNewClient( argv[1]->i, newaddr );
  }
	// - if tag does not yet exist, create a tag, and a responder, even if it has no origin yet
//FIXME   
  string tagname = &argv[2]->s;
  XOscTag * tag = server->tagExists( tagname );
  if ( tag == NULL ){
      tag = server->createNewTag( tagname );
  }
	// - if no subscriptions yet, create a responder for the tag
  if ( !tag->hasSubscriptions() ){
      server->createMethod( tag );
  }
	// - subscribe this client
  tag->addSubscription( myclient );
	// - if we have connection subscriptions, inform about the new connection
  server->sendWatchersConnectionInfo( tag, myclient, true );
	// - send confirmation
  server->sendConfirmation( newaddr, "/XOSC/subscribe/tag", true );
    return 0;
}

int XOscServer::unsubscribeTagHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;
  
  if ( server->postDebug )
    cout << "[XOscServer::unsubscribeTag] " + server->getContent( path, types, argv, argc ) << "\n";

  lo_address newaddr = lo_address_create_from( lo_address_get_hostname( addr ), argv[1]->i  );
  XOscClient * myclient = server->clientExists( argv[1]->i, newaddr );
  if ( myclient == NULL ){
    server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true ); // did not succeed, as this was not a client yet
    return 0;
  }
  string tagname = &argv[2]->s;
  XOscTag * tag = server->tagExists( tagname );
  if ( tag == NULL ){
    // tag did not exist, so we could not be subscribed to it;
    server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true ); // did not succeed, as this was not a client yet
    return 0;
  }
  tag->removeSubscription( myclient );
	// - if we have connection subscriptions, inform about the lost connection
  server->sendWatchersConnectionInfo( tag, myclient, false );
  // tag has no subscriptions left, so remove method
  if ( !tag->hasSubscriptions() ){
    server->deleteMethod( tag );
    return 0;
  }
	// - send confirmation
  server->sendConfirmation( newaddr, "/XOSC/unsubscribe/tag", true );
    return 0;
}


int XOscServer::genericHandler( handlerArgs )
{
  lo_message msg = (lo_message) data;
  lo_address addr = lo_message_get_source( msg );
  XOscServer* server = ( XOscServer* ) user_data;

  string tag = string( path );
  
  if ( server->postDebug )
    cout << "[XOscServer::genericHandler] arbitrary osc tag: " + server->getContent( path, types, argv, argc ) << "\n";
  
  // TODO: 
  //   - store some more info about it? (types?)
  XOscTag * xtag = server->tagExists( tag );
  if ( xtag != NULL ){
     if ( !server->tagCheckAndChangeOrigin( xtag, addr ) ){
        server->sendWatchersTagInfo( xtag );
     } // else, no changes
  } else { // else, create a new tag
      server->createNewTag( tag, addr );
  }
  return 0;
}

// ------------- end basic message interface -----------
  
  
XOscServer::XOscServer( const char *port ) : OSCServer( port )
{
    postDebug = false;
}

// void XOscServer::debug( bool onoff ){
//     postDebug = onoff;
// }

XOscServer::~XOscServer()
{
}

//-------------- basic message interface -----------------

void XOscServer::addBasicMethods()
{
// 	addMethod( "/ping", "is", pingHandler, this );
// 	addMethod( "/error", "ssi", errorHandler, this );
// 	addMethod( "/warn",  "ssi", warnHandler, this );

	addMethod( "/XOSC/register/client",  "is", registerClientHandler, this );    // port, name
// 	addMethod( "/XOSC/unregister/client", "is", unregisterClientHandler, this ); // port, name

	addMethod( "/XOSC/register/host",  "is", registerHostHandler, this );    // port (to send confirm to), name
// 	addMethod( "/XOSC/unregister/host", "is", unregisterHostHandler, this ); // port (to send confirm to), name
	
	addMethod( "/XOSC/register/watch",   "i",  registerWatchHandler, this ); // port to send back to
	addMethod( "/XOSC/unregister/watch",   "i",  unregisterWatchHandler, this ); // port to send back to

	addMethod( "/XOSC/query/tags",  "i",   queryTagsHandler, this ); // port to send back to
	addMethod( "/XOSC/query/tag/connections", "is",   queryConnectionsTagHandler, this ); // port to send back to, tag to query
	addMethod( "/XOSC/query/connections", "i",   queryConnectionsHandler, this ); // port to send back to

	addMethod( "/XOSC/subscribe/tag",   "is",  subscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/subscribe/host",   "isi",  subscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/subscribe/host",   "is",  subscribeHostnameHandler, this ); // port to send back to, host name

	addMethod( "/XOSC/unsubscribe/tag",   "is",  unsubscribeTagHandler, this ); // port to send back to, tag
	addMethod( "/XOSC/unsubscribe/host",   "isi",  unsubscribeHostHandler, this ); // port to send back to, host ip, host port to connect to
	addMethod( "/XOSC/unsubscribe/host",   "is",  unsubscribeHostnameHandler, this ); // port to send back to, host name

	// all tags
	addMethod( "/XOSC/subscribe",   "i",  subscribeHandler, this ); // port to send back to
	addMethod( "/XOSC/unsubscribe",   "i",  unsubscribeHandler, this ); // port to send back to

	addMethod( "/XOSC/connect/tag",   "sis",  connectTagHandler, this ); // host ip, host port to send back to, tag
	addMethod( "/XOSC/connect/tag",   "ss",  connectHostnameTagHandler, this ); // host name to send back to, tag
	addMethod( "/XOSC/disconnect/tag",   "sis",  disconnectTagHandler, this ); // host ip, host port to send back to, tag
	addMethod( "/XOSC/disconnect/tag",   "ss",  disconnectHostnameTagHandler, this ); // host name to send back to, tag

	addMethod( "/XOSC/connect/host",   "sisi",  connectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/host",   "sis",  connectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/connect/host",   "ssi",  connectHostnameHostHandler, this ); // client name, host ip, host port
	addMethod( "/XOSC/connect/host",   "ss",  connectHostnameHostnameHandler, this ); // client name, host name

	addMethod( "/XOSC/disconnect/host",   "sisi",  disconnectHostHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/host",   "sis",  disconnectHostnameHandler, this ); // client host ip, client port, host ip, host port to connect to
	addMethod( "/XOSC/disconnect/host",   "ssi",  disconnectHostnameHostHandler, this ); // client name, host ip, host port
	addMethod( "/XOSC/disconnect/host",   "ss",  disconnectHostnameHostnameHandler, this ); // client name, host name


	// The generic handler must be added last. 
	// Otherwise it would be called instead of the handlers. 
	addMethod( NULL, NULL, genericHandler, this );
}

void XOscServer::sendConfirmation( lo_address targ, const char *path, bool success ){
    lo_message msg = lo_message_new();
    if ( success )
      lo_message_add_true( msg );
    else
      lo_message_add_false( msg );
    sendMessage( targ, path, msg );
    lo_message_free( msg );
}

bool XOscServer::registerClient( lo_address clientAddr, int port, string name ){
  if ( clientExistsAndChangeName( port, clientAddr, name ) ){
      return true; // was already registered
  }
  createNewClient( port, clientAddr, name );
  return true;
}

bool XOscServer::registerHost( lo_address hostAddr, string name ){
  if ( hostExistsAndChangeName( hostAddr, name ) ){
      return true; // was already registered
  }
  createNewHost( hostAddr, name );
  return true;
}


void XOscServer::sendWatchersTagInfo( XOscTag * xtag ){
    // TODO: iterate over watchers and send tag info
}

void XOscServer::sendWatchersConnectionInfo( XOscTag * xtag, XOscClient * client, bool gotconnected ){
    // TODO: iterate over watchers and send tag info
}

XOscTag * XOscServer::tagExists( string name ){
  tagMap::iterator iter = oscTags.find( name );
  if ( iter != oscTags.end() ){
    return iter->second;
  }
  return NULL;
}

bool XOscServer::tagCheckAndChangeOrigin( XOscTag * xtag, lo_address originAddress ){
    if ( xtag->hasOrigin() ){
	if ( xtag->compareOrigin( originAddress ) ){
	  // all good, early return
	  return true;
	}
    }
    XOscHost * myhost;
    // tag had no origin yet, or it was different from what was known, so create one and add it to the list
    myhost = getHost( originAddress );
    xtag->setOrigin( myhost );
    return false;
}

void XOscServer::createNewTag( string name, lo_address originAddress ){
  // TODO: create a new tag instance, and add it to the map
  XOscHost * myhost;
  XOscTag * newtag = new XOscTag( name );
  if ( hostExists( originAddress ) ){
      hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( originAddress ) );
      myhost = iter->second;
  } else {
      myhost = createNewHost( originAddress );
  }
  newtag->setOrigin( myhost );
  newtag->setServer( this );
  oscTags.insert( make_pair( name, newtag ) );
}

XOscTag * XOscServer::createNewTag( string name ){
  // TODO: create a new tag instance, and add it to the map
  XOscTag * newtag = new XOscTag( name );
  newtag->setServer( this );
  oscTags.insert( make_pair( name, newtag ) );
  return newtag;
}

XOscClient * XOscServer::clientExists( int port, lo_address addr ){
  clientMap::iterator iter = oscClients.find( port );
  if ( iter != oscClients.end() ){
    if ( lo_address_issame( addr, *(iter->second->getAddress()) ) ){
      return iter->second;
// 	return true;
    }
  }
  return NULL;
}

bool XOscServer::clientExistsAndChangeName( int port, lo_address addr, string name ){
  clientMap::iterator iter = oscClients.find( port );
  if ( iter != oscClients.end() ){
    if ( lo_address_issame( addr, *(iter->second->getAddress()) ) ){
	iter->second->setName( name );
	return true;
    }
  }
  return false;
}

XOscClient * XOscServer::createNewClient( int port, lo_address addr, string name ){
  XOscClient * newclient = new XOscClient( &addr );
  newclient->setName( name );
  oscClients.insert( make_pair( port, newclient) );
  return newclient;
}

XOscClient * XOscServer::createNewClient( int port, lo_address addr ){
  XOscClient * newclient = new XOscClient( &addr );
//   newclient->setName( name );
  oscClients.insert( make_pair( port, newclient) );
  return newclient;
}

bool XOscServer::hostExists( lo_address addr ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){
    if ( lo_address_issame( addr, *(iter->second->getAddress() ) ) ){
	return true;
    }
  }
  return false;
}


bool XOscServer::hostExistsAndChangeName( lo_address addr, string name ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){
    if ( lo_address_issame( addr, *(iter->second->getAddress()) ) ){
	iter->second->setName( name );
	return true;
    }
  }
  return false;
}

XOscHost * XOscServer::createNewHost( lo_address addr, string name ){
  XOscHost * newhost = new XOscHost( addr );
  newhost->setName( name );
  oscHosts.insert( make_pair( lo_address_get_port_as_int( addr ), newhost ) );
  return newhost;
}

XOscHost * XOscServer::createNewHost( lo_address addr ){
  XOscHost * newhost = new XOscHost( addr );
  oscHosts.insert( make_pair( lo_address_get_port_as_int( addr ), newhost ) );
  return newhost;
}

XOscHost * XOscServer::getHost( lo_address addr ){
  hostMap::iterator iter = oscHosts.find( lo_address_get_port_as_int( addr ) );
  if ( iter != oscHosts.end() ){ 
    if ( lo_address_issame( addr, *( iter->second->getAddress() ) ) ){
	return iter->second;
    }
  }
  return createNewHost( addr );
}

// ------------- flexible message interface ------------

void XOscServer::createMethod( XOscTag * osctag ){
  const char *path = osctag->getTag().c_str();
  addMethod( path, NULL, osctag->messageHandler, osctag );
}

void XOscServer::deleteMethod( XOscTag * osctag ){
  const char *path = osctag->getTag().c_str();
  removeMethod( path, NULL );
}

//-------------- messages to the host -----------------

/*
void XOscServer::querySubscriptions()
{
	sendSimpleMessage( "/query/subscriptions" );
}

void XOscServer::setData( int id, int size, string data[] )
{
	lo_message msg = lo_message_new();
	lo_message_add_int32( msg, port );
	lo_message_add_string( msg, name.data() );
	lo_message_add_int32( msg, id );

	for (int n=0; n<size; n++)
		lo_message_add_string( msg, data[n].data() );

	sendMessage( hostAddress, "/set/data", msg );

	lo_message_free( msg );	
}
*/

//-------------- end messages to the host -----------------
}
