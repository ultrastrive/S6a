
#include "interf_ssix.h"

/*Retrieve string value from avp*/
inline int avp_str_value(struct avp *avp, char **val){
	struct avp_hdr hdr = NULL;
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
    *val = hdr->avp_value->os.data;
	return 0;
}

/*Retrieve interger value from avp*/
inline int avp_int_value(struct avp *avp, int *val){
	struct avp_hdr hdr = NULL;
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
    *val = hdr->avp_value->i32;
	return 0;
}

/*Retrieve uint32_t value from avp*/
inline int avp_uint_value(struct avp *avp, int *val){
	struct avp_hdr hdr = NULL;
	CHECK_FCT( fd_msg_avp_hdr( avp, &hdr ) );
    *val = hdr->avp_value->u32;
	return 0;
}

/*Retrieves string value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
inline int get_str_value(struct msg **msg, struct dict_object *dict, char **val){
	struct avp *avp = NULL;	
	/*if the message or target is null return*/
	if(!msg || !val)
		return 1;

	/*check for 'dict' type avp inside message 'msg'*/
	CHECK_FCT( fd_msg_search_avp ( *msg, dict, &avp) );
	if (avp) 		
		return avp_str_value(avp, val);	
	return 1;	
}

/*Retrieves int value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
inline int get_int_value(struct msg **msg, struct dict_object *dict, int *val){
	struct avp *avp = NULL;

	/*if the message or target is null return*/
	if(!msg || !val)
		return 1;

	/*check for 'dict' type avp inside message 'msg'*/
	CHECK_FCT( fd_msg_search_avp ( *msg, dict, &avp) );
	if (avp) 
		return avp_int_value(avp, val);
	return 1;	
}

/*Retrieves uint32_t value of the first avp indicated by 'dict' with in  message 'msg' and store the resulting pointer to 'target'*/
inline int get_uint_value(struct msg **msg, struct dict_object *dict, uint32_t *val){
	struct avp *avp = NULL;

	/*if the message or target is null return*/
	if(!msg || !val)
		return 1;

	/*check for 'dict' type avp inside message 'msg'*/
	CHECK_FCT( fd_msg_search_avp ( *msg, dict, &avp) );
	if (avp) 
		return avp_uint_value(avp, val);
	return 1;	
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
inline int get_str_value_gavp(struct avp *gavp, struct dict_object *dict, char **val){
	struct avp *avp = NULL;

	/*if the message or target is null return*/
	if(!gavp || !val)
		return 1;

	/*check for 'dict' type avp inside message 'gavp'*/
	ss_avp_search_avp( gavp, dict, &avp, MSG_BRW_FIRST_CHILD);
	if (avp) 
		return avp_str_value(avp, val);
	return 1;	
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
inline int get_uint_value_gavp(struct avp *gavp, struct dict_object *dict, uint32_t *val){
	struct avp *avp = NULL;

	/*if the message or target is null return*/
	if(!gavp || !val)
		return 1;

	/*check for 'dict' type avp inside message 'gavp'*/
	ss_avp_search_avp( gavp, dict, &avp, MSG_BRW_FIRST_CHILD);
	if (avp) 
		return avp_uint_value(avp, val);
	return 1;	
}

/*Retrieves string value of the first avp indicated by 'dict' with in group avp 'gavp' and store the resulting pointer to 'target'*/
inline int get_int_value_gavp(struct avp *gavp, struct dict_object *dict, int *val){
	struct avp *avp = NULL;

	/*if the message or target is null return*/
	if(!gavp || !val)
		return 1;

	/*check for 'dict' type avp inside message 'gavp'*/
	ss_avp_search_avp( gavp, dict, &avp, MSG_BRW_FIRST_CHILD);
	if (avp) 
		return avp_int_value(avp, val);
	return 1;	
}

/*Retrieves multiple string values of multiple similar AVPs found in a message 'msg'*/
inline int get_str_array(struct msg ** msg, struct dict_object * dict, char *** val){

	struct avp * avp, *avp2;
	char ** temp;
	size_t num = 0;
	if(msg || val || dict)
			return 1;

	fd_msg_search_avp ( *msg, dict, &avp);
	while(avp){
		if((temp = realloc(temp, sizeof(char *) * (num + 1))) == NULL)
			return 1;
		avp_str_value(avp, temp + num);
		num ++;
		ss_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT );
		avp = avp2;
	}
		
	if(temp){
		*val = temp;
		return 0;
	}
	
	return 1;
}

/*Retrieves multiple string values of multiple similar AVPs found in a group AVP 'gavp'*/
inline int get_str_gavp_array(struct avp * gavp, struct dict_object * dict, char *** val){

	struct avp * avp, *avp2;
	char ** temp;
	size_t num = 0;
	if(gavp || val)
			return 1;

	ss_avp_search_avp ( gavp, dict, &avp, MSG_BRW_FIRST_CHILD );
	while(avp){
		if((temp = realloc(temp, sizeof(char *) * (num + 1))) == NULL)
			return 1;
		avp_str_value(avp, temp + num);
		num ++;
		ss_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT );
		avp = avp2;
	}
		
	if(temp){
		*val = temp;
		return 0;
	}
	
	return 1;
}

/*Retrieves multiple integer values of multiple similar AVPs found in a group AVP 'gavp'*/
inline int get_int_gavp_array(struct avp * gavp, struct dict_object * dict, int ** val){

	struct avp * avp, *avp2;
	int * temp;
	size_t num = 0;
	if(gavp || val)
			return 1;

	
	ss_avp_search_avp ( gavp, dict, &avp, MSG_BRW_FIRST_CHILD );
	while(avp){
		if((temp = realloc(temp, sizeof(int) * (num + 1))) == NULL)
			return 1;
		avp_int_value(avp, temp + num);
		num ++;
		ss_avp_search_avp ( avp, dict, &avp, MSG_BRW_NEXT );
		avp = avp2;
	}
		
	if(temp){
		*val = temp;
		return 0;
	}
	
	return 1;
}

/*Retrieves multiple uint32_t values of multiple similar AVPs found in message structure 'msg'*/
inline int get_uint_array(struct msg * msg, struct dict_object * dict, uint32_t ** val){

	struct avp * avp, *avp2;
	uint32_t * temp;
	size_t num = 0;
	if(gavp || val)
			return 1;

	
	fd_msg_search_avp ( *msg, dict, &avp);
	while(avp){
		if((temp = realloc(temp, sizeof(uint32_t) * (num + 1))) == NULL)
			return 1;
		avp_uint_value(avp, temp + num);
		num ++;
		ss_avp_search_avp ( avp, dict, &avp2, MSG_BRW_NEXT );
		avp = avp2;
	}
		
	if(temp){
		*val = temp;
		return 0;
	}
	
	return 1;
}

/*Retrieves Destination-Host avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_destination_host(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_dest_host, ret);
}

/*Retrieves originating host avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_origin_host(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_origin_host, ret);
}

/*Retrieves Destination-Realm avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_destination_host(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_dest_realm, ret);
}

/*Retrieves originating realm avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_origin_host(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_origin_realm, ret);
}

/*Retrieves User-Name (imsi) avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_user_name(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_user_name, ret);
}

/*TODO:SUPPORTED FEATURE*/

/*Retrieves RAT-Type avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_rat_type(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_rat_type, ret);
}

/*Retrieves ULR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ulr_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ulr_flgs, ret);
}

/*Retrieves UE-SRVCC-Capability avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ue_srvcc_capability(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_ue_srvcc_capab, ret);
}

/*Retrieves Visited-PLMN-Id avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_visited_plmn_id(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_visited_plmn_id, ret);
}

/*Retrieves SGSN-Number avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_sgsn_number(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_sgsn_num, ret);
}

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Session avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_homogeneous_support_ims(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_homog_suppr_ims_vop_sess, ret);
}

/*Retrieves GMLC-Address avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_gmlc_address(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_gmlc_addr, ret);
}

/*Retrieves MME-Number-for-MT-SMS avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_mme_number_mt_sms(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_mme_num_for_mt_sms, ret);
}

/*Retrieves SMS-Register-Request avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_sms_register_request(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_sms_reg_req, ret);
}

/*Retrieves Coupled-Node-Diameter-ID avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_coupled_node_id(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_copl_nd_dia_id, ret);
}

/*Retrieves imei avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains imei avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_imei(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_imei, ret);
}

/*Retrieves Software-Version avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Software-Version avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_software_version(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_soft_version, ret);
}

/*Retrieves meid avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains meid avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_meid(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_meid, ret);
}

/*Retrieves Context-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Context-Identifier avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_context_identifier_gavp(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_context_id, ret);
}

/*Retrieves Service-Selection avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Service-Selection avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_service_selection_gavp(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_service_selection, ret);
}

/*Retrieves multiple Service-Selection AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains Service-Selection avps.  
		ret: address of a pointer where the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_service_selection_array(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_service_selection, ret);		
}

/*Retrieves Visited-Network-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Visited-Network-Identifier avp. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_visited_network_identifier_gavp(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_vistd_net_id, ret);
}

/*Retrieves multiple MIP-Home-Agent-Address AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains MIP-Home-Agent-Address avps.  
		ret: address of a pointer where the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_mip_home_agent_address(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_mip_home_agent_addr, ret);		
}

/*Retrieves Visited-PLMN-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Visited-PLMN-Id avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_visited_plmn_id_gavp(struct avp *gavp, char **ret){	

	return get_str_value(gavp, ss_visited_plmn_id, ret);
}

/*Retrieves multiple Visited-PLMN-Id AVPs' values from group avp 
	parameter:
		gavp: a pointer to the group avp that contains Visited-PLMN-Id avp.  
		ret: address of a pointer where the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_visited_plmn_id_array(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_visited_plmn_id, ret);		
}

/*Retrieves Result-Code avp value from group avp 
	parameter:
		msg: a pointer the message pointer.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_result_code(struct msg **msg, uint32_t *ret){	

	return get_uint_value_gavp(msg, ss_result_code, ret);
}

/*Retrieves Error-Diagnostic avp value from message 
	parameter:
		msg: a pointer the message pointer.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_error_diagnostic(struct msg **msg, int *ret){	

	return get_int_value_gavp(msg, ss_err_diagnostic, ret);
}

/*Retrieves ULA-Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ula_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ula_flgs, ret);
}

/*Retrieves Vendor-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Vendor-Id avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_vendor_id_gavp(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_vendor_id, ret);
}

/*Retrieves Experimental-Result-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Experimental-Result-Code avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_experimental_result_code(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_exper_res_code, ret);
}

/*Retrieves Subscriber-Status avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscriber-Status avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_subscriber_status(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_subscr_status, ret);
}

/*Retrieves MSISDN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MSISDN avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_msisdn(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_msisdn, ret);
}

/*Retrieves A-MSISDN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains A-MSISDN avp. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_amsisdn(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_a_msisdn, ret);
}

/*Retrieves STN-SR avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains STN-SR avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_stn_sr(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_stn_sr, ret);
}

/*Retrieves ICS-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ICS-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ics_indicator(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_ics_indicator, ret);
}

/*Retrieves Network-Access-Mode avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Network-Access-Mode avp.
		ret: a pointer to an uint variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_network_access_mode(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_net_access_mode, ret);
}

/*Retrieves Operator-Determined-Barring avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Operator-Determined-Barring avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ics_indicator(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_operator_det_barring, ret);
}

/*Retrieves HPLMN-ODB avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains HPLMN-ODB avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_hplmn_odb(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_hplmn_odb, ret);
}

/*Retrieves Regional-Subscription-Zone-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Regional-Subscription-Zone-Code avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_regional_subscription_zone_code(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_regional_subscrip_zone_code, ret);
}

/*Retrieves Access-Restriction-Data avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Access-Restriction-Data avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_access_restriction_data(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_access_restrict_data, ret);
}

/*Retrieves APN-OI-Replacement avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains APN-OI-Replacement avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_apn_oi_replacement(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_apn_oi_replacement, ret);
}

/*Retrieves 3GPP-Charging-Characteristics avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains 3GPP-Charging-Characteristics avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_3gpp_charging_characteristics(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_3gpp_charging_char, ret);
}

/*Retrieves RAT-Frequency-Selection-Priority-ID avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains RAT-Frequency-Selection-Priority-ID avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_rat_frequency_selection_priority_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_rat_freq_sel_prior_id, ret);
}

/*Retrieves Roaming-Restricted-Due-To-Unsupported-Feature avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Roaming-Restricted-Due-To-Unsupported-Feature avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_roaming_restricted_unsupported_feature(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_roam_restr_dueto_unsuppr_featr, ret);
}

/*Retrieves Subscribed-Periodic-RAU-TAU-Timer avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscribed-Periodic-RAU-TAU-Timer avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_subscribed_periodic_rau_tau_timer(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_subscr_priod_rau_tau_timer, ret);
}

/*Retrieves MPS-Priority avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MPS-Priority avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_mps_priority(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_mps_prio, ret);
}

/*Retrieves VPLMN-LIPA-Allowed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains VPLMN-LIPA-Allowed avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_vplmn_lipa_allowed(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_vplmn_lipa_allow, ret);
}

/*Retrieves Relay-Node-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Relay-Node-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_relay_node_indicator(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_rely_nod_ind, ret);
}

/*Retrieves MDT-User-Consent avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MDT-User-Consent avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_mdt_user_consent(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_mdt_usr_consent, ret);
}

/*Retrieves Subscribed-VSRVCC avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscribed-VSRVCC avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_subscribed_vsrvcc(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_subscr_vsrvcc, ret);
}

/*Retrieves Subscription-Data-Flags avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Subscription-Data-Flags avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_subscription_data_flags(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_subsc_data_flgs, ret);
}

/*Retrieves multiple GMLC-Number AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains GMLC-Number avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_gmlc_number(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_gmlc_num, ret);		
}

/*Retrieves SS-Code avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SS-Code avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ss_code_gavp(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_ss_code, ret);
}

/*Retrieves SS-Status avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SS-Status avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ss_status(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_ss_status, ret);
}

/*Retrieves Notification-To-UE-User avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Notification-To-UE-User avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_notification_ue_user(struct avp *gavp, int *ret){	

	return get_int_value_gavp(gavp, ss_notif_to_ue_user, ret);
}

/*Retrieves Client-Identity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Client-Identity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_client_identity(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_cli_id, ret);
}

/*Retrieves GMLC-Restriction avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains GMLC-Restriction avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_gmlc_restriction(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_gmlc_restr, ret);
}

/*Retrieves multiple PLMN-Client AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PLMN-Client avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic int array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_plmn_client(struct avp *gavp, int **ret){	
	
	return get_int_gavp_array(gavp, ss_plmn_cli, ret);		
}

/*Retrieves ServiceTypeIdentity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ServiceTypeIdentity avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_serviceTypeIdentity(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_servctypeid, ret);
}

/*Retrieves multiple TS-Code AVPs value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains TS-Code avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_ts_code_gavp(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_ts_code, ret);		
}

/*Retrieves Max-Requested-Bandwidth-UL avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Max-Requested-Bandwidth-UL avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_max_requested_bw_ul(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_max_req_band_ul, ret);
}

/*Retrieves Max-Requested-Bandwidth-DL avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Max-Requested-Bandwidth-DL avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_max_requested_bw_dl(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_max_req_band_dl, ret);
}

/*Retrieves All-APN-Configurations-Included-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains All-APN-Configurations-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_all_apn_config_included_indicator(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_all_apn_config_incl_ind, ret);
}

/*Retrieves PDN-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDN-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pdn_type(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_pdn_type, ret);
}

/*Retrieves VPLMN-Dynamic-Address-Allowed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains VPLMN-Dynamic-Address-Allowed avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_vplmn_dynamic_address_allowed(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_vplmn_dyn_addr_allowed, ret);
}

/*Retrieves PDN-GW-Allocation-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDN-GW-Allocation-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pdn_gw_allocation_type(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_pdn_gw_alloc_type, ret);
}

/*Retrieves SIPTO-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SIPTO-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_sipto_permission(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_sipto_permis, ret);
}

/*Retrieves LIPA-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains LIPA-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_lipa_permission(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_lipa_permis, ret);
}

/*Retrieves Restoration-Priority avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Restoration-Priority avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_restoration_priority(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_restor_prio, ret);
}

/*Retrieves SIPTO-Local-Network-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SIPTO-Local-Network-Permission avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_sipto_local_network_permission(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_sipto_local_net_permis, ret);
}

/*Retrieves multiple Served-Party-IP-Address AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Served-Party-IP-Address avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_served_party_ip_address(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_servd_party_ip_addr, ret);		
}

/*Retrieves QoS-Class-Identifier avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains QoS-Class-Identifier avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_qos_class_identifier(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_qos_class_id, ret);
}

/*Retrieves Priority-Level avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Priority-Level avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_priority_level(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_prio_level, ret);
}

/*Retrieves Pre-emption-Capability avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Pre-emption-Capability avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pre_emption_capability(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_pre_emp_capb, ret);
}

/*Retrieves Pre-emption-Vulnerability avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Pre-emption-Vulnerability avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pre_emption_vulnerability(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_pre_emp_vuln, ret);
}

/*Retrieves WLAN-offloadability-EUTRAN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains WLAN-offloadability-EUTRAN avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_wlan_offloadability_eutran(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_wlan_offloadability_eutran, ret);
}

/*Retrieves WLAN-offloadability-UTRAN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains WLAN-offloadability-UTRAN avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_wlan_offloadability_utran(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_wlan_offloadability_utran, ret);
}

/*Retrieves Trace-Reference avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Reference avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_reference_gavp(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_trace_ref, ret);
}

/*Retrieves Trace-Depth avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Depth avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_depth(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_trace_depth, ret);
}

/*Retrieves Trace-NE-Type-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-NE-Type-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_ne_type_list(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_trace_ne_type_list, ret);
}

/*Retrieves Trace-Interface-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Interface-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_interface_list(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_trace_interf_list, ret);
}

/*Retrieves Trace-Event-List avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Event-List avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_event_list(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_trace_event_list, ret);
}

/*Retrieves OMC-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains OMC-Id avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_omc_id(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_omc_id, ret);
}

/*Retrieves Trace-Collection-Entity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Trace-Collection-Entity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_collection_entity(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_trace_coll_entity, ret);
}

/*Retrieves Job-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Job-Type avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_job_type(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_job_type, ret);
}

/*Retrieves multiple Cell-Global-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Cell-Global-Identity avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_cell_global_identity(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_cell_glb_id, ret);		
}

/*Retrieves multiple E-UTRAN-Cell-Global-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains E-UTRAN-Cell-Global-Identity avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_e_utran_cell_global_identity(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_e_utran_cell_glb_id, ret);		
}

/*Retrieves multiple Routing-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Routing-Area-Identity avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_routing_area_identity(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_rout_area_id, ret);		
}

/*Retrieves multiple Location-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Location-Area-Identity avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_location_area_identity(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_loc_area_id, ret);		
}

/*Retrieves multiple Tracking-Area-Identity AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Tracking-Area-Identity avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_tracking_area_identity(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_track_area_id, ret);		
}

/*Retrieves List-Of-Measurements avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains List-Of-Measurements avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_list_of_measurement(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_list_of_measr, ret);
}

/*Retrieves Reporting-Trigger avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Reporting-Trigger avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_reporting_trigger(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_repor_trig, ret);
}

/*Retrieves Report-Interval avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Report-Interval avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_report_interval(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_repor_intrv, ret);
}

/*Retrieves Report-Amount avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Report-Amount avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_report_amount(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_repor_amount, ret);
}

/*Retrieves Event-Threshold-RSRP avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-RSRP avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_event_threshold_rsrp(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_evt_thrsd_rsrp, ret);
}

/*Retrieves Event-Threshold-RSRQ avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-RSRQ avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_event_threshold_rsrq(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_evt_thrsd_rsrq, ret);
}

/*Retrieves Logging-Interval avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Logging-Interval avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_logging_interval(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_log_intrv, ret);
}

/*Retrieves Logging-Duration avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Logging-Duration avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_logging_duration(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_log_dur, ret);
}

/*Retrieves Measurement-Period-LTE avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Period-LTE avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_measurement_period_lte(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_measr_perd_lte, ret);
}

/*Retrieves Measurement-Period-UMTS avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Period-UMTS avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_measurement_period_umts(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_measr_perd_umts, ret);
}

/*Retrieves Collection-Period-RMM-LTE avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Collection-Period-RMM-LTE avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_collection_period_rmm_lte(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_coll_perd_rrm_lte, ret);
}

/*Retrieves Collection-Period-RRM-UMTS avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Collection-Period-RRM-UMTS avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_collection_period_rmm_umts(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_coll_perd_rrm_umts, ret);
}

/*Retrieves Positioning-Method avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Positioning-Method avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_positioning_method(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_pos_meth, ret);
}

/*Retrieves Measurement-Quantity avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Measurement-Quantity avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_measurement_quantity(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_measr_quant, ret);
}

/*Retrieves Event-Threshold-Event-1F avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-Event-1F avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_event_threshold_event_1f(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_evt_thrsd_evt_1f, ret);
}

/*Retrieves Event-Threshold-Event-1I avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Event-Threshold-Event-1I avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_event_threshold_event_1i(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_evt_thrsd_evt_1i, ret);
}	

/*Retrieves multiple MDT-Allowed-PLMN-Id AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains MDT-Allowed-PLMN-Id avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_mdt_allowed_plmn_id(struct avp *gavp, char ***ret){	
	
	return get_str_gavp_array(gavp, ss_mdt_allow_plmn_id, ret);		
}

/*Retrieves Complete-Data-List-Included-Indicator avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Complete-Data-List-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_complete_data_list_included_indicator(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_complete_data_list_incl_ind, ret);
}

/*Retrieves PDP-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDP-Type avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pdp_type(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_pdp_type, ret);
}

/*Retrieves PDP-Address avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains PDP-Address avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pdp_address(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_pdp_addr, ret);
}

/*Retrieves QoS-Subscribed avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains QoS-Subscribed avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_qos_subscribed(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_qos_subscr, ret);
}

/*Retrieves Ext-PDP-Type avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Ext-PDP-Type avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ext_pdp_type(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_ext_pdp_type, ret);
}

/*Retrieves Ext-PDP-Address avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Ext-PDP-Address avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ext_pdp_address(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_ext_pdp_addr, ret);
}

/*Retrieves CSG-Id avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Id avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_csg_id(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_csg_id, ret);
}

/*Retrieves Expiration-Date avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Expiration-Date avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_expiration_date(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_expir_date, ret);
}

/*Retrieves ProSe-Permission avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains ProSe-Permission avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_prose_permission(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_prose_permis, ret);
}

/*Retrieves multiple Reset-ID AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Reset-ID avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_reset_id(struct msg **msg, char ***ret){	
	
	return get_str_array(msg, ss_rst_id, ret);		
}

/*Retrieves Number-Of-Requested-Vectors avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Number-Of-Requested-Vectors avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_number_of_requested_vectors(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_num_of_req_vects, ret);
}

/*Retrieves Immediate-Response-Preferred avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Immediate-Response-Preferred avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_immediate_response_preferred(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_immdt_res_prefrd, ret);
}

/*Retrieves Re-synchronization-Info avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Re-synchronization-Info avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_re_synchronization_info(struct avp *gavp, char **ret){	

	return get_str_value_gavp(gavp, ss_re_synch_info, ret);
}

/*Retrieves Item-Number avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Item-Number avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_item_number(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_item_num, ret);
}

/*Retrieves RAND avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains RAND avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_rand(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_rand, ret);
}

/*Retrieves XRES avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains XRES avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_xres(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_xres, ret);
}

/*Retrieves AUTN avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains AUTN avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_autn(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_autn, ret);
}

/*Retrieves KASME avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains KASME avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_kasme(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_kasme, ret);
}

/*Retrieves Confidentiality-Key avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Confidentiality-Key avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_confidentiality_key(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_confid_key, ret);
}

/*Retrieves Integrity-Key avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Integrity-Key avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_integrity_key(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_integrity_key, ret);
}

/*Retrieves Kc avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Kc avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_kc(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_kc, ret);
}

/*Retrieves SRES avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains SRES avp.  
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_sres(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_sres, ret);
}

/*Retrieves Cancellation-Type avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_cancellation_type(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_cancel_type, ret);
}

/*Retrieves CLR-Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_clr_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_clr_flgs, ret);
}

/*Retrieves IDR- Flags avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_idr_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_idr_flgs, ret);
}

/*Retrieves IMS-Voice-Over-PS-Sessions-Supported avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ims_voice_over_ps_sessions_supported(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_ims_voice_ovr_ps_sess_suprt, ret);
}

/*Retrieves Last-UE-Activity-Time avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_last_ue_activity_time(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_last_ue_actv_tm, ret);
}

/*Retrieves IDA- Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_ida_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_ida_flgs, ret);
}

/*Retrieves User-State avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Complete-Data-List-Included-Indicator avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_user_state(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_usr_state, ret);
}

/*Retrieves Geographical-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Geographical-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_geographical_information(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_geo_info, ret);
}

/*Retrieves Geodetic-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Geodetic-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_geodetic_information(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_geodetic_info, ret);
}

/*Retrieves Current-Location-Retrieved avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Current-Location-Retrieved avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_current_location_retrieved(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_curr_loc_retrvd, ret);
}

/*Retrieves Age-Of-Location-Information avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Age-Of-Location-Information avp.
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_age_of_location_information(struct avp *gavp, uint32_t *ret){	

	return get_uint_value_gavp(gavp, ss_age_of_loc_info, ret);
}

/*Retrieves CSG-Access-Mode avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Access-Mode avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_csg_access_mode(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_csg_accss_mode, ret);
}

/*Retrieves CSG-Membership-Indication avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains CSG-Membership-Indication avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_csg_membership_indication(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_csg_memb_ind, ret);
}

/*Retrieves Time-Zone avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Time-Zone avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_time_zone(struct avp *gavp, unsigned char **ret){	

	return get_str_value_gavp(gavp, ss_tm_zn, ret);
}

/*Retrieves Daylight-Saving-Time avp value from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Daylight-Saving-Time avp.
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_daylight_saving_time(struct avp *gavp, int *ret){	
	return get_int_value_gavp(gavp, ss_daylit_sv_tm, ret);
}

/*Retrieves DSR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_dsr_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_dsr_flgs, ret);
}

/*Retrieves Context-Identifier avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_context_identifier(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_context_id, ret);
}

/*Retrieves multiple Context-Identifier AVPs' values from group avp 
	parameter:
		gavp: a pointer to a group avp that contains Context-Identifier avp.  
		ret: address of a pointer where a the resulting pointer to a dynamic uint32_t array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_context_identifier_array(struct msg **msg, uint32_t **ret){	
	
	return get_uint_array(msg, ss_context_id, ret);		
}
/*Retrieves Trace-Reference avp value from from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_trace_reference(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_trace_ref, ret);
}

/*Retrieves multiple TS-Code AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_ts_code(struct msg **msg, char ***ret){	
	
	return get_str_array(msg, ss_ts_code, ret);		
}

/*Retrieves multiple SS-Code AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_ss_code(struct msg **msg, char ***ret){	
	
	return get_str_array(msg, ss_ss_code, ret);		
}

/*Retrieves DSA-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_dsa_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_dsa_flgs, ret);
}

/*Retrieves PUR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pur_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_pur_flgs, ret);
}

/*Retrieves PUA-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_pua_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_pua_flgs, ret);
}

/*Retrieves multiple User-Id AVPs value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: address of a pointer where a the resulting pointer to a dynamic string array that stores the values will be stored.The last element of the array is always NULL. It should be freed unless the return value is 1(failure).
	returns: 0 on success 1 on failure
*/
inline int ss_get_user_id(struct msg **msg, char ***ret){	
	
	return get_str_array(msg, ss_usr_id, ret);		
}

/*Retrieves Visited-Network-Identifier avp value from message
	parameter:
		msg: a pointer to the message pointer.  
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_visited_network_identifier(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_vistd_net_id, ret);
}

/*Retrieves Service-Selection avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_get_service_selection(struct msg **msg, char **ret){	

	return get_str_value(msg, ss_service_selection, ret);
}

/*Retrieves Alert-Reason avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_alert_reason(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_alert_reason, ret);
}

/*Retrieves NOR-Flags avp value from message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to an uint32_t variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_nor_flags(struct msg **msg, uint32_t *ret){	

	return get_uint_value(msg, ss_nor_flgs, ret);
}

/*Retrieves Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value from message 
	parameter:
		msg: a pointer the message pointer. 
		ret: a pointer to an int variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_get_homogeneous_support_ims_vop_sessions(struct msg **msg, int *ret){	

	return get_int_value(msg, ss_homog_suppr_ims_vop_sess, ret);
}
