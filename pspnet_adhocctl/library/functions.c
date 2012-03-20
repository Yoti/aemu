#include "common.h"

/**
 * Resolve IP to MAC
 * @param ip Peer IP Address
 * @param mac OUT: Peer MAC
 * @return 0 on success or... ADHOC_NO_ENTRY
 */
int _resolveIP(uint32_t ip, SceNetEtherAddr * mac)
{
	// Get Local IP Address
	union SceNetApctlInfo info; if(sceNetApctlGetInfo(PSP_NET_APCTL_INFO_IP, &info) == 0)
	{
		// Convert IP Address to Numerical Display
		uint32_t _ip = 0; sceNetInetInetAton(info.ip, &_ip);
		
		// Local IP Address Requested
		if(ip == _ip)
		{
			// Return MAC Address
			*mac = _parameter.bssid.mac_addr;
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Lock
	_acquirePeerLock();
	
	// Peer Reference
	SceNetAdhocctlPeerInfo * peer = _friends;
	
	// Iterate Peers
	for(; peer != NULL; peer = peer->next)
	{
		// Found Matching Peer
		if(peer->ip_addr == ip)
		{
			// Copy Data
			*mac = peer->mac_addr;
			
			// Multithreading Unlock
			_freePeerLock();
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Unlock
	_freePeerLock();
	
	// Peer not found
	return ADHOC_NO_ENTRY;
}

/**
 * Resolve MAC to IP
 * @param mac Peer MAC Address
 * @param ip OUT: Peer IP
 * @return 0 on success or... ADHOC_NO_ENTRY
 */
int _resolveMAC(SceNetEtherAddr * mac, uint32_t * ip)
{
	// Local MAC Requested
	if(memcmp(&_parameter.bssid.mac_addr, mac, sizeof(SceNetEtherAddr)) == 0)
	{
		// Get Local IP Address
		union SceNetApctlInfo info; if(sceNetApctlGetInfo(PSP_NET_APCTL_INFO_IP, &info) == 0)
		{
			// Return IP Address
			sceNetInetInetAton(info.ip, ip);
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Lock
	_acquirePeerLock();
	
	// Peer Reference
	SceNetAdhocctlPeerInfo * peer = _friends;
	
	// Iterate Peers
	for(; peer != NULL; peer = peer->next)
	{
		// Found Matching Peer
		if(memcmp(&peer->mac_addr, mac, sizeof(SceNetEtherAddr)) == 0)
		{
			// Copy Data
			*ip = peer->ip_addr;
			
			// Multithreading Unlock
			_freePeerLock();
			
			// Return Success
			return 0;
		}
	}
	
	// Multithreading Unlock
	_freePeerLock();
	
	// Peer not found
	return ADHOC_NO_ENTRY;
}

/**
 * Get First Peer List Element
 * @return First Internal Peer List Element
 */
SceNetAdhocctlPeerInfo * _getInternalPeerList(void)
{
	// Return First Peer List Element
	return _friends;
}