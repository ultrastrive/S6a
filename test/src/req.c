
#include <unistd.h>

#include "ssix_interface.h"
#include "test.h"

/*Set Terminal-Information group AVP and its child AVPs*/
static void set_terminal_info(struct msg ** msg, utf8string *imei, utf8string *soft_ver, octetstring *meid){

	struct avp * tmp_gavp;

	if(!msg)
		return;

	if((!imei) && (!meid) && (!soft_ver))
		return;

	/*Create Terminal-Information group AVP*/
	SS_CHECK( ss_create_terminal_information(&tmp_gavp), "Terminal-Information group AVP created.\n", "Failed to create Terminal-Information group AVP\n");

	/*Set IMEI AVP*/
	if(imei)
		SS_CHECK( ss_set_imei( &tmp_gavp, imei), "IMEI AVP set.\n","Failed to set IMEI AVP\n");

	/*Set Software-Version AVP*/
	if(soft_ver)
		SS_CHECK( ss_set_software_version( &tmp_gavp, soft_ver), "Software-Version AVP set.\n","Failed to set Software-Version AVP\n");

	/*Set 3GPP2-MEID AVP*/
	if(meid)
		SS_CHECK( ss_set_3gpp2_meid( &tmp_gavp, meid), "3GPP2-MEID AVP set.\n","Failed to set 3GPP2-MEID AVP\n");	
	
	/*Add Terminal-Information group AVP in to message*/ 	
	SS_CHECK( ss_add_avp( (msg_or_avp **) msg, tmp_gavp), "Terminal-Information group AVP added in to message\n", "Failed to add Terminal-Information group AVP in to message\n");
}

/*Set Equivalent-PLMN-List group AVP and its child AVPs*/
static void set_eqv_plmn_lst(struct msg ** msg, octetstring * vis_plmn_id){

	struct avp * tmp_gavp = NULL;

	if((!msg) || (!vis_plmn_id))
		return;

	/*Create Equivalent-PLMN-List group AVP*/
	SS_CHECK( ss_create_equivalent_plmn_list(&tmp_gavp), "Equivalent-PLMN-List group AVP created.\n", "Failed to create Equivalent-PLMN-List AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	SS_CHECK( ss_set_visited_plmn_id_gavp( &tmp_gavp, vis_plmn_id), "Visited-PLMN-Id AVP set into Equivalent-PLMN-List.\n","Failed to set Visited-PLMN-Id AVP into Equivalent-PLMN-List\n");

	/*Add Equivalent-PLMN-List into message*/ 	
	SS_CHECK( ss_add_avp( (msg_or_avp **) msg, tmp_gavp), "Equivalent-PLMN-List AVP into into Update-Location-Request message\n", "Failed to add Equivalent-PLMN-List AVP into Update-Location-Request message\n");
}

/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
static void set_spec_apn_info(struct avp ** gavp, utf8string * serv_sel, address * ipv4, address * ipv6, diameterid * host, diameterid * realm, octetstring * vis_net_id){

	struct avp * tmp_gavp = NULL;

	if((!gavp) || (serv_sel))
		return;
	if((!ipv4) && (!ipv6) && (!host) && (!realm))
		return;

	/*Create Specific-APN-Info group AVP*/
	SS_CHECK( ss_create_specific_apn_info(&tmp_gavp), "Specific-APN-Info group AVP created.\n", "Failed to create Specific-APN-Info AVP\n");
	
	/*Set Service-Selection AVP*/
	SS_CHECK( ss_set_service_selection_gavp( &tmp_gavp, serv_sel), "Service-Selection AVP set in Specific-APN-Info AVP.\n","Failed to set Service-Selection AVP in Specific-APN-Info AVP\n");

	/*Add MIP6-Agent-Info group AVP in to Specific-APN-Info*/ 	
	test_set_mip6(&tmp_gavp, ipv4, ipv6, host, realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier_gavp( &tmp_gavp, vis_net_id), "Visited-Network-Identifier AVP set in Specific-APN-Info.\n","Failed to set Visited-Network-Identifier AVP in Specific-APN-Info.\n");

	/*Add Specific-APN-Info into Active-APN AVP*/ 	
	SS_CHECK( ss_add_avp( (msg_or_avp **) &gavp, tmp_gavp), "Specific-APN-Info AVP added into Active-APN AVP\n", "Failed to add Specific-APN-Info AVP into Active-APN AVP\n");
}


/*Set Active-APN group AVP and its child AVPs*/	
static void set_active_apn(struct msg **msg, unsigned32 context_id, utf8string * serv_sel, address * ipv4, address * ipv6, diameterid * host, diameterid * realm, octetstring * vis_net_id){

	struct avp * tmp_gavp = NULL;
	int i;

	if(!msg)
		return;
	if((!serv_sel) && (!ipv4) && (!ipv6) && (!host) && (!realm) && (!vis_net_id))
		return;
	/*Create Active-APN group AVP*/
	SS_CHECK( ss_create_active_apn(&tmp_gavp), "Active-APN group AVP created.\n", "Failed to create Active-APN group AVP\n");

	/*Set Context-Identifier AVP*/
	SS_CHECK( ss_set_context_identifier_gavp( &tmp_gavp, context_id), "context identifier set in Active-APN.\n", "Failed to set Context-Identifier in Active-APN.\n");

	/*Set Service-Selection AVP*/
	SS_CHECK( ss_set_service_selection_gavp( &tmp_gavp, serv_sel), "Service-Selection AVP set in Active-APN AVP.\n","Failed to set Service-Selection AVP in Active-APN AVP\n");

	/*Set MIP6-Agent-Info group AVP and its child AVPs*/
	test_set_mip6(&tmp_gavp, ipv4, ipv6, host, realm);

	/*Set Visited-Network-Identifier AVP*/	
	SS_CHECK( ss_set_visited_network_identifier_gavp( &tmp_gavp, vis_net_id), "Visited-Network-Identifier AVP set in Active-APN AVP.\n","Failed to set Visited-Network-Identifier AVP in Active-APN AVP.\n");

	/*Set Specific-APN-Info group AVP (only 3 AVPs for testing) and its child AVPs*/
	for (i = 1 ; i<3 ; i++)		
		set_spec_apn_info(&tmp_gavp, serv_sel, ipv4, ipv6, host, realm, vis_net_id);	

	/*Add Specific-APN-Info into Active-APN AVP*/ 	
	SS_CHECK( ss_add_avp( (msg_or_avp **) msg, tmp_gavp), "Active-APN AVP added into Update-Location-Request message\n", "Failed to add Active-APN AVP into Update-Location-Request message\n"); 
}

/*'test_types = 0', response should be user unknow*/
/*'test_types = 1', response should be RAT not allowed, */
/*'test_types = 2', response should be roaming not allowed dueto odb feature not supported by MME*/
/*'test_types = any other number' , response should be filled with subscription data of user*/
int test_req_ulr(char * dest_host, int test_type){

	struct msg * ulr = NULL;
	int i;
	size_t len;
	
	if(!dest_host)
		return 1;

	diameterid * destination_host= (diameterid *) dest_host;
	diameterid * destination_realm = (diameterid *)"localdomain";
	utf8string * user_name = (utf8string *)"244444123456789";	
	unsigned32 feature_list_id = 1;
	unsigned32 feature_list = 2; 		
	utf8string * imei = (utf8string *)"2345";
	utf8string * software_version = (utf8string *)"22";
	octetstring * meid = (octetstring *)"2345";
	enum rat_type rat_type = UTRAN;	
	unsigned32 ulr_flags = 0;
	enum ue_srvcc_capability ue_srvcc_capability = UE_SRVCC_SUPPORTED;
	octetstring * visited_plmn_id = (octetstring *)"plmn_id";	
	octetstring  sgsn_number [] = {0x25,0x14,0x56};
	enum homogeneous_support_ims_voice_over_ps_sessions homogeneous_support_ims_voice_over_ps_sessions = SUPPORTED;
	address * gmlc_address = (address *)"gmlc.local";
	unsigned32 context_identifier = 1;
	utf8string * service_selection = (utf8string *)"serviceSelection";
	address  home_agent_address_v4 [] = {0xef,0x00,0x00,0x01};
	address  home_agent_address_v6 [] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0x7f,0x00,0x00,0x01};
	diameterid * home_agent_host_host = (diameterid *) "pdngateway1";
	diameterid * home_agent_host_realm = (diameterid *) "epc.mnc001.mcc001.3gppnetwork.org ";
	octetstring * visited_network_identifier = (octetstring *)"visited-net-id";
	octetstring * mme_number_for_mt_sms = (octetstring *)"mme-23";
	enum sms_register_request sms_register_request = SMS_REGISTRATION_REQUIRED;
	diameterid * coupled_node_diameter_id = (diameterid *)"coupl-node";


	/*Initialize values of AVPs*/	
	if(test_type == 0){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in user unknown response."ANSI_COLOR_RESET"\n");
		user_name = (utf8string *)"244444123456788";
	}
	else if(test_type == 1){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in RAT not allowed response."ANSI_COLOR_RESET"\n");
		rat_type = VIRTUAL;
	}
	else if(test_type == 2){
		
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in roaming not allowed with error diagnostic response."ANSI_COLOR_RESET"\n");
		feature_list = 1;
	}	
	else	
		fprintf(stdout, COLOR_GREEN"\nTest : Initializing ULR test that would result in DIAMER-SUCCESS. "ANSI_COLOR_RESET"\n");

		
		

	/*Waite untill remote peer state is open*/
	len = strlen(dest_host);
	if(ss_peer_state( dest_host, len) != 1)
		fprintf(stdout, "Waiting until connection to remote peer is estabilished ...\n");	
	while(ss_peer_state( dest_host, len) != 1)
		sleep(2);
		
	/*Create Update-Location-Request message*/
	SS_CHECK( ss_create_msg_ulr(&ulr), "Update-Location-Request message Created.\n", "Error in creating Update-Location-Request message.\n");

	/*Set Destination-Host AVP*/	
	SS_CHECK( ss_set_destination_host( &ulr, destination_host), "Destination-Host AVP set.\n","Failed to set Destination-Host AVP\n");
	
	/*Set Destination-Realm AVP*/
	SS_CHECK( ss_set_destination_realm( &ulr, destination_realm), "Destination-Realm AVP set.\n","Failed to set Destination-Realm AVP\n");

	/*Set User-Name AVP*/
	SS_CHECK( ss_set_user_name( &ulr, user_name), "User-Name AVP set.\n","Failed to set User-Name AVP\n");
	
	/*Set Supported-Features group AVP and its child AVPs*/
	test_set_supported_features(&ulr, (unsigned32)VENDOR_ID_3GPP, feature_list_id, feature_list);

	/*Set Terminal-Information group AVP and its child AVPs*/
	set_terminal_info( &ulr, imei, software_version, meid);
	
	/*Set RAT-Type AVP*/
	SS_CHECK( ss_set_rat_type( &ulr, rat_type), "RAT-Type AVP set.\n","Failed to set RAT-Type AVP\n");

	/*Set ULR-Flags AVP*/
	SS_CHECK( ss_set_ulr_flags( &ulr, ulr_flags), "ULR-Flags AVP set.\n","Failed to set ULR-Flags AVP\n");

	/*Set UE-SRVCC-Capability AVP*/
	SS_CHECK( ss_set_ue_srvcc_capability( &ulr, ue_srvcc_capability), "UE-SRVCC-Capability AVP set.\n","Failed to set UE-SRVCC-Capability AVP\n");

	/*Set Visited-PLMN-Id AVP*/
	SS_CHECK( ss_set_visited_plmn_id( &ulr, visited_plmn_id), "Visited-PLMN-Id AVP set.\n","Failed to set Visited-PLMN-Id AVP\n");

	/*Set SGSN-Number AVP*/
	SS_CHECK( ss_set_sgsn_number( &ulr, sgsn_number), "SGSN-Number AVP set.\n","Failed to set SGSN-Number AVP\n");
	
	/*Set Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions AVP*/
	SS_CHECK( ss_set_homogeneous_support_ims_vop_sessions( &ulr, (int)homogeneous_support_ims_voice_over_ps_sessions), "Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP set.\n","Failed to set Homogeneous-Support-of-IMS-Voice-Over-PS-Session AVP\n");

	/*Set GMLC-Address AVP*/
	SS_CHECK( ss_set_gmlc_address( &ulr, gmlc_address), "GMLC-Address AVP set.\n","Failed to set GMLC-Address AVP\n");	

	/*Set Active-APN AVP*/
	for(i = 1; i<3 ; i++)
		set_active_apn(&ulr, context_identifier, service_selection, home_agent_address_v4, home_agent_address_v6, home_agent_host_host, home_agent_host_realm, visited_network_identifier);

	/*Set Equivalent-PLMN-List group AVP and its child AVPs*/
	set_eqv_plmn_lst(&ulr, visited_plmn_id);
	
	/*Set MME-Number-for-MT-SMS AVP*/
	SS_CHECK( ss_set_mme_number_for_mt_sms( &ulr, mme_number_for_mt_sms), "MME-Number-for-MT-SMS AVP set.\n","Failed to set MME-Number-for-MT-SMS AVP.\n");

	/*Set SMS-Register-Request AVP*/
	SS_CHECK( ss_set_sms_register_request( &ulr, sms_register_request), "SMS-Register-Request AVP set.\n","Failed to set SMS-Register-Request AVP.\n");

	/*Set Coupled-Node-Diameter-ID AVP*/
	SS_CHECK( ss_set_coupled_node_diameter_id( &ulr, coupled_node_diameter_id), "Coupled-Node-Diameter-ID AVP set.\n","Failed to set Coupled-Node-Diameter-ID AVP.\n");

	/*send request*/
	SS_CHECK( fd_msg_send( &ulr, test_ans_cb, NULL), "ULR message sent.\n", "Failed to send ULR message.\n");

	return 1;
}
