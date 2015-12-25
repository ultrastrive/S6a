
#include "internal_ssix.h"

int ss_serv_init(){
	
	struct disp_when data;
	
	memset(&data, 0, sizeof(data));
	data.app = ss_app;

	
	/* Rigister handler for ULR */
	data.command = ss_cmd_ulr;
	CHECK_FCT( fd_disp_register( ss_ulr_ans_cb, DISP_HOW_CC, &data, NULL, NULL ) );

	/* Rigister handler for CLR */
	data.command = ss_cmd_clr;
	CHECK_FCT( fd_disp_register( ss_clr_ans_cb, DISP_HOW_CC, &data, NULL, NULL ) );
	
	return 1;
}
