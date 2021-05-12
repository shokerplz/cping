#ifndef CPING_ERRORS
/* Create socket errors */
const int FD_NOT_RECEIVED  = -100;
const int TTL_NOT_SET      = -101;
const int TIMEOUT_NOT_SET  = -102;
/* End */

/* ICMP send and receive errors */
const int SENT_FAILED      = 200;
const int RCV_FAILED       = 201;
/* End */

/* GetIP errors */
const int NO_HOST_FOUND	   = 110;
const int NO_ADDRESS_FOUND = 111;
const int NO_RECOVERY_PSB  = 112;
const int TRY_AGAIN_LTR    = 113;
const int DNS_SRV_ERR      = 114;
/* End */

/* Main errors */
const int NO_ADDR          = 211;
const int ARGS_NOT_VALID   = 212;
const int ALL_MEM_ERR	   = 202;
const int IP_NOT_VALID     = 213;
const int UNKNOWN_ERROR    = 255;
/* End */
#endif
