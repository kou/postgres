/*-------------------------------------------------------------------------
 *
 * copyapi.h
 *	  API for COPY TO handlers
 *
 *
 * Portions Copyright (c) 1996-2024, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/commands/copyapi.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef COPYAPI_H
#define COPYAPI_H

#include "executor/tuptable.h"
#include "nodes/execnodes.h"

/* This is private in commands/copyto.c */
typedef struct CopyToStateData *CopyToState;

/*
 * API structure for a COPY TO format implementation.   Note this must be
 * allocated in a server-lifetime manner, typically as a static const struct.
 */
typedef struct CopyToRoutine
{
	NodeTag		type;

	/*
	 * Called when COPY TO is started to set up the output functions
	 * associated with the relation's attributes reading from.  `finfo` can be
	 * optionally filled to provide the catalog information of the output
	 * function.  `atttypid` is the OID of data type used by the relation's
	 * attribute.
	 */
	void		(*CopyToOutFunc) (CopyToState cstate, Oid atttypid,
								  FmgrInfo *finfo);

	/*
	 * Called when COPY TO is started.
	 *
	 * `tupDesc` is the tuple descriptor of the relation from where the data
	 * is read.
	 */
	void		(*CopyToStart) (CopyToState cstate, TupleDesc tupDesc);

	/*
	 * Copy one row for COPY TO.
	 *
	 * `slot` is the tuple slot where the data is emitted.
	 */
	void		(*CopyToOneRow) (CopyToState cstate, TupleTableSlot *slot);

	/* Called when COPY TO has ended */
	void		(*CopyToEnd) (CopyToState cstate);
} CopyToRoutine;

#endif							/* COPYAPI_H */
