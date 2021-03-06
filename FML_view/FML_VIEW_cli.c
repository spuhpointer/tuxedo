#include <stdio.h>
#include <atmi.h>
#include <fml1632.h>
#include <string.h>
#include <friend.h>
#include <friendfml.h>

int
#if defined(__STDC__) || defined(__cplusplus)
main(int argc, char *argv[])
#else
main(argc, argv)
int argc;
char *argv[];
#endif
{
	/* tpinit */
#if 0
extern int	_TMDLLENTRY tpinit _((TPINIT _TM_FAR *));
#endif
	tpinit((TPINIT *)NULL);
	/* tpalloc */
#if 0
extern char	_TM_FAR * _TMDLLENTRY tpalloc _((char _TM_FAR *, char _TM_FAR *, long));
#endif
	struct friend *friendp = NULL;
#if 0
friendp = (struct friend *)tpalloc("VIEW32", "friend", sizeof(*friendp))
#endif
	if (NULL == (friendp = (struct friend *)tpalloc("VIEW32", "friend", sizeof(*friendp))))
	{
		fprintf(stderr, "tpalloc error line:%d :%s\n",
				__LINE__, tpstrerror(tperrno));
		goto failure;
	}
	/* tpcall */
#if 0
int tpcall(char *svc, char *idata, long ilen, char **odata, long *olen, long flags)
#endif
	long rcv_len = 0;
	friendp->friend_id = 0L;
	memcpy(friendp->fname, "JQ", sizeof("JQ"));
	memcpy(friendp->fmobile, "13344445555", sizeof("13344445555"));

	struct Fbfr32 *fbfr = NULL;
	if (NULL == (fbfr = (struct Fbfr32 *)tpalloc("FML32", NULL, 0)))
	{
		fprintf(stderr, "tpalloc error line :%d :%s\n",
				__LINE__, tpstrerror(tperrno));
		goto failure;
	}

	fprintf(stdout, "before Fvstof32 friend_id :%ld, fname :%s, fmobile :%s\n",
			friendp->friend_id, friendp->fname, friendp->fmobile);
	if (-1 == Fvstof32(fbfr, (char *)friendp, FCONCAT, "friend"))
	{
		fprintf(stderr, "Fvstof32 error :%s\n", Fstrerror32(Ferror32));
		goto failure;
	}
	fprintf(stdout, "Fvstof32\n");
	Fprint32(fbfr);

	if (-1 == tpcall("FVs", (char *)fbfr, 0L, (char **)&fbfr, &rcv_len, 0L))
	{
		fprintf(stderr, "tpcall error :%s\n", tpstrerror(tperrno));
		goto failure;
	}
	fprintf(stdout, "after tpcall\n");
	Fprint32(fbfr);

	if (-1 == Fvftos32(fbfr, (char *)friendp, "friend"))
	{
		fprintf(stderr, "Fvftos32 error :%s\n", Fstrerror32(Ferror32));
		goto failure;
	}

	fprintf(stdout, "after Fvftos32 friend_id :%ld, fname :%s, fmobile :%s\n",
			friendp->friend_id, friendp->fname, friendp->fmobile);
failure:
	/* tpfree */
	if (NULL != friendp)
		tpfree((char *)friendp);
	if (NULL != fbfr)
		tpfree((char *)fbfr);
	/* tpterm */
	tpterm();
}
