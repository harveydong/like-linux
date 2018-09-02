#ifndef __REQUIRED_FEATRUES_H_
#define __REQUIRED_FEATRUES_H_
#include "cpufeature.h"

#define NEED_XMM (1<<(X86_FEATRUE_XMM) & 31)
#define NEED_XMM2 (1<<(X86_FEATRUE_XMM2)&31)

#define SSE_MASK (NEED_XMM|NEED_XMM2)
#define NEED_FPU	(1<<(X86_FEATURE_FPU & 31))

# define NEED_PAE	(1<<(X86_FEATURE_PAE & 31))
# define NEED_CX8	(1<<(X86_FEATURE_CX8 & 31))
# define NEED_CMOV	(1<<(X86_FEATURE_CMOV & 31))
# define NEED_3DNOW	(1<<(X86_FEATURE_3DNOW & 31))

#define NEED_PSE	(1<<(X86_FEATURE_PSE) & 31)
#define NEED_PGE	(1<<(X86_FEATURE_PGE) & 31)
#define NEED_MSR	(1<<(X86_FEATURE_MSR & 31))
#define NEED_FXSR	(1<<(X86_FEATURE_FXSR & 31))
#define NEED_LM		(1<<(X86_FEATURE_LM & 31))
#define REQUIRED_MASK0	(NEED_FPU|NEED_PSE|NEED_MSR|NEED_PAE|\
			 NEED_CX8|NEED_PGE|NEED_FXSR|NEED_CMOV|\
			 NEED_XMM|NEED_XMM2)



#define REQUIRED_MASK1	(NEED_LM|NEED_3DNOW)
#define REQUIRED_MASK2	0
#define REQUIRED_MASK3	(NEED_NOPL)
#define REQUIRED_MASK4	0
#define REQUIRED_MASK5	0
#define REQUIRED_MASK6	0
#define REQUIRED_MASK7	0
#endif
