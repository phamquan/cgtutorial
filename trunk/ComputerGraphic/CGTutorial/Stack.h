#pragma once
#include "afxtempl.h"

template <class T>
class CStack :
	public CTypedPtrList <CPtrList, T>
{
public:

	CStack(void)
	{
	}

	virtual ~CStack(void)
	{
	}

	// Add element to top of stack
    void Push(T newTray )
        { AddHead( newTray ); }

    // Peek at top element of stack
    T Peek()
        { return IsEmpty() ? NULL : GetHead(); }

    // Pop top element off stack
    T Pop()
        { return RemoveHead(); }
};

