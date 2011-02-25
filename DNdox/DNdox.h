#ifndef _DN_DOX_H_
#define _DN_DOX_H_

#define DNDOX_CONTRACTID "@in.co.digitalneuron/XPCOMSample/DNdox;1"
#define DNDOX_CLASSNAME "A Simple XPCOM Sample"
#define DNDOX_CID \
  {0xa0f44c90, 0x36cf, 0x11e0, \
    { 0x9e, 0x42, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 }}

#include "IDNDox.h"
#include<windows.h>
class DNdox : public IDNdox
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_IDNDOX

  DNdox();
void CreateImage(HWND window, const char* filename);
int CaptureAnImage(HWND hWnd);
private:
  ~DNdox();

protected:
  /* additional members */
};

#endif