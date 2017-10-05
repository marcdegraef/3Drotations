
#pragma once

#ifndef _ROTLIBCFLT_H
#define _ROTLIBCFLT_H





int eu2omf (float* eu, float* om, int p);
int eu2axf (float* eu, float* ax, int p);
int eu2quf (float* eu, float* q,  int p);
int om2euf (float* om, float* eu, int p);
int ax2omf (float* ax, float* om, int p);
int qu2euf (float* q,  float* eu, int p);
int ax2hof (float* ax, float* ho, int p);
int ho2axf (float* h,  float* ax, int p);
int om2axf (float* om, float* ax, int p);
int ro2axf (float* ro, float* ax, int p);
int ax2rof (float* ax, float* ro, int p);
int ax2quf (float* ax, float* qu, int p);
int ro2hof (float* ro, float* ho, int p);
int qu2omf (float* qu, float* om, int p);
int om2quf (float* om, float* qu, int p);
int qu2axf (float* qu, float* ax, int p);
int qu2rof (float* qu, float* ro, int p);
int qu2hof (float* qu, float* ho, int p);
int cu2hof (float* ho, float* cu, int p);
int ho2cuf (float* ho, float* cu, int p);
///testing

/////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
// Dependant Codes Start Here
////////////////////////////////////////////////////////////////


int eu2rof (float* eu, float* ro, int p);
int ro2omf (float* ro, float* om, int p);
int ro2euf (float* ro, float* eu, int p);
int eu2hof (float* eu, float* ho, int p);
int om2rof (float* om, float* ro, int p);
int om2hof (float* om, float* ho, int p);
int ax2euf (float* ax, float* eu, int p);
int ro2quf (float* ro, float* qu, int p);
int ho2euf (float* ho, float* eu, int p);
int ho2omf (float* ho, float* om, int p);
int ho2rof (float* ho, float* ro, int p);
int ho2quf (float* ho, float* qu, int p);
int eu2cuf (float* eu, float* cu, int p);
int om2cuf (float* om, float* cu, int p);
int ax2cuf (float* ax, float* cu, int p);
int ro2cuf (float* ro, float* cu, int p);
int qu2cuf (float* qu, float* cu, int p);
int cu2euf (float* cu, float* eu, int p);
int cu2omf (float* cu, float* om, int p);
int cu2axf (float* cu, float* ax, int p);
int cu2rof (float* cu, float* ro, int p);
int cu2quf (float* cu, float* qu, int p);


#endif