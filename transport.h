#ifndef TRANSPORT_H
#define TRANSPORT_H

#include "cache.h"
#include "remote.h"

struct transport {
	unsigned verbose : 1;
	unsigned fetch : 1;
	struct remote *remote;
	const char *url;

	void *data;

	struct ref *remote_refs;

	const struct transport_ops *ops;
};

#define TRANSPORT_PUSH_ALL 1
#define TRANSPORT_PUSH_FORCE 2

struct transport_ops {
	/**
	 * Returns 0 if successful, positive if the option is not
	 * recognized or is inapplicable, and negative if the option
	 * is applicable but the value is invalid.
	 **/
	int (*set_option)(struct transport *connection, const char *name,
			  const char *value);

	int (*push)(struct transport *connection, int refspec_nr, const char **refspec, int flags);

	int (*disconnect)(struct transport *connection);
};

/* Returns a transport suitable for the url */
struct transport *transport_get(struct remote *remote, const char *url,
				int fetch);

/* Transport options which apply to git:// and scp-style URLs */

/* The program to use on the remote side to receive a pack */
#define TRANS_OPT_RECEIVEPACK "receivepack"

/* Transfer the data as a thin pack if not null */
#define TRANS_OPT_THIN "thin"

/**
 * Returns 0 if the option was used, non-zero otherwise. Prints a
 * message to stderr if the option is not used.
 **/
int transport_set_option(struct transport *transport, const char *name,
			 const char *value);

int transport_push(struct transport *connection,
		   int refspec_nr, const char **refspec, int flags);

int transport_disconnect(struct transport *transport);

#endif
