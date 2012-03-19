#ifndef _PSPNET_RESOLVER_H_
#define _PSPNET_RESOLVER_H_

/**
 * Initialize the Resolver Library
 * @return 0 on sucess, < 0 on error.
 */
int sceNetResolverInit(void);

/**
 * Create a Resolver Instance
 * @param rid OUT: Resolver ID
 * @param buf Temporary Buffer
 * @param buflen Length of Temporary Buffer
 * @return 0 on success, < 0 on error
 */
int sceNetResolverCreate(int *rid, void *buf, SceSize buflen);

/**
 * Delete a resolver
 * @param rid - Resolver ID
 * @return 0 on success, < 0 on error
 */
int sceNetResolverDelete(int rid);

/**
 * Resolve Domain to IP Address
 * @param rid Resolver ID
 * @param hostname Domain Name
 * @param addr OUT: IP Address
 * @param timeout Timeout Values
 * @param retry Number of Retries
 * @return 0 on success, < 0 on error
 */
int sceNetResolverStartNtoA(int rid, const char *hostname, uint32_t * addr, unsigned int timeout, int retry);

/**
 * Terminate the Resolver Library
 * @return 0 on success, < 0 on error
 */
int sceNetResolverTerm(void);

#endif

