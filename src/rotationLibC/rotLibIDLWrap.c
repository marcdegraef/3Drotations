#include "rotLibIDLWrap.h"
#include <stdlib.h> 
 #include <stdio.h>
#include <math.h>

#include "idl_export.h"
#include "rotLibIDLLoopsFlt.h"
#include "rotLibIDLLoopsDbl.h"


int ax2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ax2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ax2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ax2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ax2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ax2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ax2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ax2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int cu2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return cu2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return cu2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int eu2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return eu2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return eu2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ho2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ho2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ho2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int om2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return om2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return om2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int qu2roIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return qu2roLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return qu2roLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2axIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2axLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2axLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2cuIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2cuLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2cuLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2euIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2euLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2euLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2hoIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2hoLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2hoLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2omIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2omLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2omLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int ro2quIDLWrap (int argc, void* argv[]){
  int p, type;
  unsigned long long n;
  IDL_LONG *pIn,  *typeIn;
  IDL_ULONG64 *nIn;

  nIn = (IDL_ULONG64*) argv[2];
  n = (unsigned long long) (*nIn);
  pIn = (IDL_LONG*) argv[3];
  p = (int) (*pIn);
  typeIn = (IDL_LONG*) argv[4];
  type = (int) (*typeIn);

  if (type == 4) { // do the input/output will be stored as float (calcs still done in double)
    return ro2quLoopf ( (float*) argv[0], (float*) argv[1], n, p);
  } else { // double calculation and storage
     return ro2quLoop ( (double*) argv[0], (double*) argv[1], n, p);
  }
}



int IDLRotLibUnload (int argc, void* argv[]){
return 1;
}
