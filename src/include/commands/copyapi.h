/*-------------------------------------------------------------------------
 *
 * copyapi.h
 *	  API for COPY TO/FROM
 *
 * Copyright (c) 2015-2023, PostgreSQL Global Development Group
 *
 * src/include/command/copyapi.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef COPYAPI_H
#define COPYAPI_H

#include "executor/tuptable.h"

typedef struct CopyToStateData *CopyToState;
extern void *CopyToStateGetOpaque(CopyToState cstate);
extern void CopyToStateSetOpaque(CopyToState cstate, void *opaque);
extern List *CopyToStateGetAttNumList(CopyToState cstate);

extern void CopyToStateSendData(CopyToState cstate, const void *databuf, int datasize);
extern void CopyToStateSendString(CopyToState cstate, const char *str);
extern void CopyToStateSendChar(CopyToState cstate, char c);
extern void CopyToStateSendInt32(CopyToState cstate, int32 val);
extern void CopyToStateSendInt16(CopyToState cstate, int16 val);
extern void CopyToStateFlush(CopyToState cstate);

typedef struct CopyFromStateData *CopyFromState;


typedef void (*CopyToStart_function) (CopyToState cstate, TupleDesc tupDesc);
typedef void (*CopyToOneRow_function) (CopyToState cstate, TupleTableSlot *slot);
typedef void (*CopyToEnd_function) (CopyToState cstate);

/* XXX: just copied from COPY TO routines */
typedef void (*CopyFromStart_function) (CopyFromState cstate, TupleDesc tupDesc);
typedef void (*CopyFromOneRow_function) (CopyFromState cstate, TupleTableSlot *slot);
typedef void (*CopyFromEnd_function) (CopyFromState cstate);

typedef struct CopyFormatRoutine
{
	NodeTag		type;

	bool		is_from;
	Node	   *routine;
}			CopyFormatRoutine;

typedef struct CopyToFormatRoutine
{
	NodeTag		type;

	CopyToStart_function start_fn;
	CopyToOneRow_function onerow_fn;
	CopyToEnd_function end_fn;
}			CopyToFormatRoutine;

/* XXX: just copied from COPY TO routines */
typedef struct CopyFromFormatRoutine
{
	NodeTag		type;

	CopyFromStart_function start_fn;
	CopyFromOneRow_function onerow_fn;
	CopyFromEnd_function end_fn;
}			CopyFromFormatRoutine;

extern CopyToFormatRoutine * GetCopyToFormatRoutine(char *format_name);
extern CopyFromFormatRoutine * GetCopyFromFormatRoutine(char *format_name);

#endif							/* COPYAPI_H */
