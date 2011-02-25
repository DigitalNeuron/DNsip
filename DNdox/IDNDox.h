/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM IDNDox.idl
 */

#ifndef __gen_IDNDox_h__
#define __gen_IDNDox_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    IDNdox */
#define IDNDOX_IID_STR "a0f44c90-36cf-11e0-9e42-0800200c9a66"

#define IDNDOX_IID \
  {0xa0f44c90, 0x36cf, 0x11e0, \
    { 0x9e, 0x42, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

class NS_NO_VTABLE NS_SCRIPTABLE IDNdox : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(IDNDOX_IID)

  /* long Add (in long a, in long b); */
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(IDNdox, IDNDOX_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_IDNDOX \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_IDNDOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return _to Add(a, b, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_IDNDOX(_to) \
  NS_SCRIPTABLE NS_IMETHOD Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Add(a, b, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public IDNdox
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDNDOX

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, IDNdox)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* long Add (in long a, in long b); */
NS_IMETHODIMP _MYCLASS_::Add(PRInt32 a, PRInt32 b, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_IDNDox_h__ */
