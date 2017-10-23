#include <errno.h>
#include "libft.h"

char	*get_errno_6(void)
{
	if (errno == 61)
		return ("Timer expired");
	if (errno == 62)
		return ("Out of streams resources");
	if (errno == 63)
		return ("Machine is not on the network");
	if (errno == 64)
		return ("Package not installed");
	if (errno == 65)
		return ("Object is remote");
	if (errno == 66)
		return ("Link has been severed");
	if (errno == 67)
		return ("Advertise error");
	if (errno == 68)
		return ("Srmount error");
	if (errno == 69)
		return ("Communication error on send");
	if (errno == 70)
		return ("Protocol error");
	if (errno == 71)
		return ("Multihop attempted");
	if (errno == 72)
		return ("RFS specific error");
	return (NULL);
}

char	*get_errno_7(void)
{
	if (errno == 73)
		return ("Not a data message");
	if (errno == 74)
		return ("Value too large for defined data type");
	if (errno == 75)
		return ("Name not unique on network");
	if (errno == 76)
		return ("File descriptor in bad state");
	if (errno == 77)
		return ("Remote address changed");
	if (errno == 78)
		return ("Can not access a needed shared library");
	if (errno == 79)
		return ("Accessing a corrupted shared library");
	if (errno == 80)
		return (".lib section in a.out corrupted");
	if (errno == 81)
		return ("Attempting to link in too many shared libraries");
	if (errno == 82)
		return ("Cannot exec a shared library directly");
	if (errno == 83)
		return ("Illegal byte sequence");
	if (errno == 84)
		return ("Interrupted system call should be restarted");
	return (NULL);
}

char	*get_errno_8(void)
{
	if (errno == 85)
		return ("Streams pipe error");
	if (errno == 86)
		return ("Too many users");
	if (errno == 87)
		return ("Socket operation on non-socket");
	if (errno == 88)
		return ("Destination address required");
	if (errno == 89)
		return ("Message too long");
	if (errno == 90)
		return ("Protocol wrong type for socket");
	if (errno == 91)
		return ("Protocol not available");
	if (errno == 92)
		return ("Protocol not supported");
	if (errno == 93)
		return ("Socket type not supported");
	if (errno == 94)
		return ("Operation not supported on transport endpoint");
	if (errno == 95)
		return ("Protocol family not supported");
	if (errno == 96)
		return ("Address family not supported by protocol");
	return (NULL);
}

char	*get_errno_9(void)
{
	if (errno == 97)
		return ("Address already in use");
	if (errno == 98)
		return ("Cannot assign requested address");
	if (errno == 99)
		return ("Network is down");
	if (errno == 100)
		return ("Network is unreachable");
	if (errno == 101)
		return ("Network dropped connection because of reset");
	if (errno == 102)
		return ("Software caused connection abort");
	if (errno == 103)
		return ("Connection reset by peer");
	if (errno == 104)
		return ("No buffer space available");
	if (errno == 105)
		return ("Transport endpoint is already connected");
	if (errno == 106)
		return ("Transport endpoint is not connected");
	if (errno == 107)
		return ("Cannot send after transport endpoint shutdown");
	if (errno == 108)
		return ("Too many references: cannot splice");
	return (NULL);
}

char	*get_errno_10(void)
{
	if (errno == 109)
		return ("Connection timed out");
	if (errno == 110)
		return ("Connection refused");
	if (errno == 111)
		return ("Host is down");
	if (errno == 112)
		return ("No route to host");
	if (errno == 113)
		return ("Operation already in progress");
	if (errno == 114)
		return ("Operation now in progress");
	if (errno == 115)
		return ("Stale NFS file handle");
	if (errno == 116)
		return ("Structure needs cleaning");
	if (errno == 117)
		return ("Not a XENIX named type file");
	if (errno == 118)
		return ("No XENIX semaphores available");
	if (errno == 119)
		return ("Is a named type file");
	if (errno == 120)
		return ("Remote I/O error");
	return (NULL);
}
