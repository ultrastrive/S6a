
#include "interf_ssix.h"
	
#define SS_SET_I32( value, avp)	{									\
	union avp_value v;											\
	v.i32= value;												\
	CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&v),goto error);			\
}

#define SS_SET_U32( value, avp)  {								 	\
	union avp_value v;											\
	v.u32 = value;												\
	CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&v),goto error);		\
}

#define SS_SET_OCTET( value, avp)  {								\
	union avp_value v;											\
	v.os.data = (unsigned char *)value;							\
	v.os.len = strlen((char *)(value));							\
	CHECK_FCT_DO(fd_msg_avp_setvalue(avp,&v),goto error);		\
}

/*Sets string values in AVP of type 'dict' and add it to a message 'msg'*/
inline int set_str_value(struct msg **msg, struct dict_object *dict, char *val){

	struct avp *avp = NULL;	

	/*if the message or val is null return*/
	if(!msg || !val)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){ 	
		/*Set the value 'val' in to 'avp'*/
		SS_SET_OCTET( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*msg,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets integer values in AVP of type 'dict' and add it to a message 'msg'*/
inline int set_int_value(struct msg **msg, struct dict_object *dict, int val){
	struct avp *avp = NULL;

	/*if the message is null return*/
	if(!msg)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_I32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*msg,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets unsigned integer values in AVP of type 'dict' and add it to a message 'msg'*/
inline int set_uint_value(struct msg **msg, struct dict_object *dict, uint32_t val){
	struct avp *avp = NULL;

	/*if the message is null return*/
	if(!msg)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_U32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*msg,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets string values in AVP of type 'dict' and add the AVP to a group avp 'gavp'*/
inline int set_str_value_gavp(struct avp **gavp, struct dict_object *dict, char *val){
	struct avp *avp = NULL;

	/*if the message or val is null return*/
	if(!gavp || !val)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_OCTET( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*gavp,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets unsigned integer values in AVP of type 'dict' and add the AVP to a group avp 'gavp'*/
inline int set_uint_value_gavp(struct avp **gavp, struct dict_object *dict, uint32_t val){
	struct avp *avp = NULL;

	/*if the message is null return*/
	if(!gavp)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_U32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*gavp,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets integer values in AVP of type 'dict' and add the AVP to a group avp 'gavp'*/
inline int set_int_value_gavp(struct avp **gavp, struct dict_object *dict, int val){
	struct avp *avp = NULL;

	/*if the message is null return*/
	if(!gavp)
		return 1;

	/*Create an empty AVP of type 'dict'*/
	CHECK_FCT_DO(fd_msg_avp_new(dict,0,&avp),goto error);
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_U32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		CHECK_FCT_DO(fd_msg_avp_add(*gavp,MSG_BRW_LAST_CHILD,avp),goto error);	
		return 0;	
	}

	error:
		return 1;	
}

/*Sets Destination-Host avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_destination_host(struct msg **msg, char *val){	

	return set_str_value(msg, ss_dest_host, val);
}

/*Sets originating host avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_origin_host(struct msg **msg, char *val){	

	return set_str_value(msg, ss_origin_host, val);
}

/*Sets Destination-Realm avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_destination_host(struct msg **msg, char *val){	

	return set_str_value(msg, ss_dest_realm, val);
}

/*Sets originating realm avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_origin_host(struct msg **msg, char *val){	

	return set_str_value(msg, ss_origin_realm, val);
}

/*Sets User-Name (imsi) avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_user_name(struct msg **msg, char *val){	

	return set_str_value(msg, ss_user_name, val);
}

/*TODO:SUPPORTED FEATURE*/

/*Sets RAT-Type avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_rat_type(struct msg **msg, int val){	

	return set_int_value(msg, ss_rat_type, val);
}

/*Sets ULR-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ulr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_ulr_flgs, val);
}

/*Sets UE-SRVCC-Capability avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ue_srvcc_capability(struct msg **msg, int val){	

	return set_int_value(msg, ss_ue_srvcc_capab, val);
}

/*Sets Visited-PLMN-Id avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_visited_plmn_id(struct msg **msg, char *val){	

	return set_str_value(msg, ss_visited_plmn_id, val);
}

/*Sets SGSN-Number avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_sgsn_number(struct msg **msg, char *val){	

	return set_str_value(msg, ss_sgsn_num, val);
}

/*Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Session avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_homogeneous_support_ims(struct msg **msg, int val){	

	return set_int_value(msg, ss_homog_suppr_ims_vop_sess, val);
}

/*Sets GMLC-Address avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_gmlc_address(struct msg **msg, char *val){	

	return set_str_value(msg, ss_gmlc_addr, val);
}

/*Sets MME-Number-for-MT-SMS avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mme_number_mt_sms(struct msg **msg, char *val){	

	return set_str_value(msg, ss_mme_num_for_mt_sms, val);
}

/*Sets SMS-Register-Request avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_sms_register_request(struct msg **msg, int val){	

	return set_int_value(msg, ss_sms_reg_req, val);
}

/*Sets Coupled-Node-Diameter-ID avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_coupled_node_id(struct msg **msg, char *val){	

	return set_str_value(msg, ss_copl_nd_dia_id, val);
}

/*Sets imei avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp . 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_imei(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_imei, val);
}

/*Sets Software-Version avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_software_version(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_soft_version, val);
}

/*Sets meid avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp meid avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_meid(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_meid, val);
}

/*Sets Context-Identifier avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Context-Identifier avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_context_identifier_gavp(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_context_id, val);
}

/*Sets Service-Selection avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Service-Selection avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_service_selection_gavp(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_service_selection, val);
}

/*Sets Visited-Network-Identifier avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Visited-Network-Identifier avp. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_visited_network_identifier_gavp(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_vistd_net_id, val);
}

/*Sets MIP-Home-Agent-Address avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp MIP-Home-Agent-Address avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mip_home_agent_address(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_mip_home_agent_addr, val);
}

/*Sets MIP-Home-Agent-Host avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp MIP-Home-Agent-Host avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mip_home_agent_host(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_mip_home_agen_host, val);
}

/*Sets Visited-PLMN-Id avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Visited-PLMN-Id avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_visited_plmn_id_gavp(struct avp **gavp, char *val){	

	return set_str_value(msg, ss_visited_plmn_id, val);
}

/*Sets Result-Code avp value to group avp 
	parameter:
		msg: pointer to the message pointer.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_result_code(struct msg **msg, uint32_t val){	

	return set_uint_value_gavp(msg, ss_result_code, val);
}

/*Sets Error-Diagnostic avp value to message 
	parameter:
		msg: pointer to the message pointer.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_error_diagnostic(struct msg **msg, int val){	

	return set_int_value_gavp(msg, ss_err_diagnostic, val);
}

/*Sets ULA-Flags avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ula_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_ula_flgs, val);
}

/*Sets Vendor-Id avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Vendor-Id avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_vendor_id_gavp(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_vendor_id, val);
}

/*Sets Experimental-Result-Code avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Experimental-Result-Code avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_experimental_result_code(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_exper_res_code, val);
}

/*Sets Subscriber-Status avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Subscriber-Status avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_subscriber_status(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_subscr_status, val);
}

/*Sets MSISDN avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp MSISDN avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_msisdn(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_msisdn, val);
}

/*Sets A-MSISDN avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp A-MSISDN avp. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_amsisdn(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_a_msisdn, val);
}

/*Sets STN-SR avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp STN-SR avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_stn_sr(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_stn_sr, val);
}

/*Sets ICS-Indicator avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp ICS-Indicator avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ics_indicator(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_ics_indicator, val);
}

/*Sets Network-Access-Mode avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		ret: a pointer to an uint variable where the result will be stored.
	returns: 0 on success 1 on failure
*/
inline int ss_set_network_access_mode(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_net_access_mode, val);
}

/*Sets Operator-Determined-Barring avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ics_indicator(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_operator_det_barring, val);
}

/*Sets HPLMN-ODB avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_hplmn_odb(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_hplmn_odb, val);
}

/*Sets Regional-Subscription-Zone-Code avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Regional-Subscription-Zone-Code avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_regional_subscription_zone_code(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_regional_subscrip_zone_code, val);
}

/*Sets Access-Restriction-Data avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Access-Restriction-Data avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_access_restriction_data(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_access_restrict_data, val);
}

/*Sets APN-OI-Replacement avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp APN-OI-Replacement avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_apn_oi_replacement(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_apn_oi_replacement, val);
}

/*Sets 3GPP-Charging-Characteristics avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp 3GPP-Charging-Characteristics avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_3gpp_charging_characteristics(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_3gpp_charging_char, val);
}

/*Sets RAT-Frequency-Selection-Priority-ID avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp RAT-Frequency-Selection-Priority-ID avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_rat_frequency_selection_priority_id(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_rat_freq_sel_prior_id, val);
}

/*Sets Roaming-Restricted-Due-To-Unsupported-Feature avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Roaming-Restricted-Due-To-Unsupported-Feature avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_roaming_restricted_unsupported_feature(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_roam_restr_dueto_unsuppr_featr, val);
}

/*Sets Subscribed-Periodic-RAU-TAU-Timer avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Subscribed-Periodic-RAU-TAU-Timer avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_subscribed_periodic_rau_tau_timer(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_subscr_priod_rau_tau_timer, val);
}

/*Sets MPS-Priority avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp MPS-Priority avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mps_priority(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_mps_prio, val);
}

/*Sets VPLMN-LIPA-Allowed avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp VPLMN-LIPA-Allowed avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_vplmn_lipa_allowed(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_vplmn_lipa_allow, val);
}

/*Sets Relay-Node-Indicator avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Relay-Node-Indicator avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_relay_node_indicator(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_rely_nod_ind, val);
}

/*Sets MDT-User-Consent avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp MDT-User-Consent avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mdt_user_consent(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_mdt_usr_consent, val);
}

/*Sets Subscribed-VSRVCC avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Subscribed-VSRVCC avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_subscribed_vsrvcc(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_subscr_vsrvcc, val);
}

/*Sets Subscription-Data-Flags avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Subscription-Data-Flags avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_subscription_data_flags(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_subsc_data_flgs, val);
}

/*Sets multiple GMLC-Number AVPs value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp GMLC-Number avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_gmlc_number(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_gmlc_num, val);		
}

/*Sets SS-Code avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp SS-Code avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ss_code_gavp(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_ss_code, val);
}

/*Sets SS-Status avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp SS-Status avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ss_status(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_ss_status, val);
}

/*Sets Notification-To-UE-User avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Notification-To-UE-User avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_notification_ue_user(struct avp **gavp, int val){	

	return set_int_value_gavp(gavp, ss_notif_to_ue_user, val);
}

/*Sets Client-Identity avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Client-Identity avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_client_identity(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_cli_id, val);
}

/*Sets GMLC-Restriction avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp GMLC-Restriction avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_gmlc_restriction(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_gmlc_restr, val);
}

/*Sets multiple PLMN-Client AVPs value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp PLMN-Client avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_plmn_client(struct avp **gavp, int val){	
	
	return set_int_value_gavp(gavp, ss_plmn_cli, val);		
}

/*Sets ServiceTypeIdentity avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp ServiceTypeIdentity avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_serviceTypeIdentity(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_servctypeid, val);
}

/*Sets multiple TS-Code AVPs value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp TS-Code avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ts_code_gavp(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_ts_code, val);		
}

/*Sets Max-Requested-Bandwidth-UL avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Max-Requested-Bandwidth-UL avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_max_requested_bw_ul(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_max_req_band_ul, val);
}

/*Sets Max-Requested-Bandwidth-DL avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Max-Requested-Bandwidth-DL avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_max_requested_bw_dl(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_max_req_band_dl, val);
}

/*Sets All-APN-Configurations-Included-Indicator avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp All-APN-Configurations-Included-Indicator avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_all_apn_config_included_indicator(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_all_apn_config_incl_ind, val);
}

/*Sets PDN-Type avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp PDN-Type avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pdn_type(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_pdn_type, val);
}

/*Sets VPLMN-Dynamic-Address-Allowed avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp VPLMN-Dynamic-Address-Allowed avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_vplmn_dynamic_address_allowed(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_vplmn_dyn_addr_allowed, val);
}

/*Sets PDN-GW-Allocation-Type avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp PDN-GW-Allocation-Type avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pdn_gw_allocation_type(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_pdn_gw_alloc_type, val);
}

/*Sets SIPTO-Permission avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp SIPTO-Permission avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_sipto_permission(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_sipto_permis, val);
}

/*Sets LIPA-Permission avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp LIPA-Permission avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_lipa_permission(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_lipa_permis, val);
}

/*Sets Restoration-Priority avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Restoration-Priority avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_restoration_priority(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_restor_prio, val);
}

/*Sets SIPTO-Local-Network-Permission avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp SIPTO-Local-Network-Permission avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_sipto_local_network_permission(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_sipto_local_net_permis, val);
}

/*Sets multiple Served-Party-IP-Address AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_served_party_ip_address(struct avp **gavp, char *val){	
	
	return set_str_gavp(gavp, ss_servd_party_ip_addr, val);		
}

/*Sets QoS-Class-Identifier avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp .
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_qos_class_identifier(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_qos_class_id, val);
}

/*Sets Priority-Level avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Priority-Level avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_priority_level(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_prio_level, val);
}

/*Sets Pre-emption-Capability avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Pre-emption-Capability avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pre_emption_capability(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_pre_emp_capb, val);
}

/*Sets Pre-emption-Vulnerability avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Pre-emption-Vulnerability avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pre_emption_vulnerability(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_pre_emp_vuln, val);
}

/*Sets WLAN-offloadability-EUTRAN avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp WLAN-offloadability-EUTRAN avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_wlan_offloadability_eutran(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_wlan_offloadability_eutran, val);
}

/*Sets WLAN-offloadability-UTRAN avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_wlan_offloadability_utran(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_wlan_offloadability_utran, val);
}

/*Sets Trace-Reference avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp .  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_reference_gavp(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_trace_ref, val);
}

/*Sets Trace-Depth avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_depth(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_trace_depth, val);
}

/*Sets Trace-NE-Type-List avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Trace-NE-Type-List avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_ne_type_list(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_trace_ne_type_list, val);
}

/*Sets Trace-Interface-List avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Trace-Interface-List avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_interface_list(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_trace_interf_list, val);
}

/*Sets Trace-Event-List avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Trace-Event-List avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_event_list(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_trace_event_list, val);
}

/*Sets OMC-Id avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_omc_id(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_omc_id, val);
}

/*Sets Trace-Collection-Entity avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_collection_entity(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_trace_coll_entity, val);
}

/*Sets Job-Type avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_job_type(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_job_type, val);
}

/*Sets multiple Cell-Global-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Cell-Global-Identity avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_cell_global_identity(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_cell_glb_id, val);		
}

/*Sets multiple E-UTRAN-Cell-Global-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp .  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_e_utran_cell_global_identity(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_e_utran_cell_glb_id, val);		
}

/*Sets multiple Routing-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp .  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_routing_area_identity(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_rout_area_id, val);		
}

/*Sets multiple Location-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_location_area_identity(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_loc_area_id, val);		
}

/*Sets multiple Tracking-Area-Identity AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_tracking_area_identity(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_track_area_id, val);		
}

/*Sets List-Of-Measurements avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_list_of_measurement(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_list_of_measr, val);
}

/*Sets Reporting-Trigger avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_reporting_trigger(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_repor_trig, val);
}

/*Sets Report-Interval avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Report-Interval avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_report_interval(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_repor_intrv, val);
}

/*Sets Report-Amount avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Report-Amount avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_report_amount(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_repor_amount, val);
}

/*Sets Event-Threshold-RSRP avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Event-Threshold-RSRP avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_event_threshold_rsrp(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_evt_thrsd_rsrp, val);
}

/*Sets Event-Threshold-RSRQ avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Event-Threshold-RSRQ avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_event_threshold_rsrq(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_evt_thrsd_rsrq, val);
}

/*Sets Logging-Interval avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Logging-Interval avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_logging_interval(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_log_intrv, val);
}

/*Sets Logging-Duration avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Logging-Duration avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_logging_duration(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_log_dur, val);
}

/*Sets Measurement-Period-LTE avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Measurement-Period-LTE avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_measurement_period_lte(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_measr_perd_lte, val);
}

/*Sets Measurement-Period-UMTS avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Measurement-Period-UMTS avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_measurement_period_umts(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_measr_perd_umts, val);
}

/*Sets Collection-Period-RMM-LTE avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Collection-Period-RMM-LTE avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_collection_period_rmm_lte(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_coll_perd_rrm_lte, val);
}

/*Sets Collection-Period-RRM-UMTS avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Collection-Period-RRM-UMTS avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_collection_period_rmm_umts(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_coll_perd_rrm_umts, val);
}

/*Sets Positioning-Method avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Positioning-Method avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_positioning_method(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_pos_meth, val);
}

/*Sets Measurement-Quantity avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Measurement-Quantity avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_measurement_quantity(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_measr_quant, val);
}

/*Sets Event-Threshold-Event-1F avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Event-Threshold-Event-1F avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_event_threshold_event_1f(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_evt_thrsd_evt_1f, val);
}

/*Sets Event-Threshold-Event-1I avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Event-Threshold-Event-1I avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_event_threshold_event_1i(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_evt_thrsd_evt_1i, val);
}	

/*Sets multiple MDT-Allowed-PLMN-Id AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_mdt_allowed_plmn_id(struct avp **gavp, char *val){	
	
	return set_str_value_gavp(gavp, ss_mdt_allow_plmn_id, val);		
}

/*Sets Complete-Data-List-Included-Indicator avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_complete_data_list_included_indicator(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_complete_data_list_incl_ind, val);
}

/*Sets PDP-Type avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pdp_type(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_pdp_type, val);
}

/*Sets PDP-Address avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp PDP-Address avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pdp_address(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_pdp_addr, val);
}

/*Sets QoS-Subscribed avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp QoS-Subscribed avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_qos_subscribed(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_qos_subscr, val);
}

/*Sets Ext-PDP-Type avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Ext-PDP-Type avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ext_pdp_type(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_ext_pdp_type, val);
}

/*Sets Ext-PDP-Address avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Ext-PDP-Address avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ext_pdp_address(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_ext_pdp_addr, val);
}

/*Sets CSG-Id avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp CSG-Id avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_csg_id(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_csg_id, val);
}

/*Sets Expiration-Date avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Expiration-Date avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_expiration_date(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_expir_date, val);
}

/*Sets ProSe-Permission avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_prose_permission(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_prose_permis, val);
}

/*Sets multiple Reset-ID AVPs' values to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_reset_id(struct msg **msg, char *val){	
	
	return set_str_value(msg, ss_rst_id, val);		
}

/*Sets Number-Of-Requested-Vectors avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_number_of_requested_vectors(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_num_of_req_vects, val);
}

/*Sets Immediate-Response-Preferred avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_immediate_response_preferred(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_immdt_res_prefrd, val);
}

/*Sets Re-synchronization-Info avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Re-synchronization-Info avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_re_synchronization_info(struct avp **gavp, char *val){	

	return set_str_value_gavp(gavp, ss_re_synch_info, val);
}

/*Sets Item-Number avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Item-Number avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_item_number(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_item_num, val);
}

/*Sets RAND avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_rand(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_rand, val);
}

/*Sets XRES avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp XRES avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_xres(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_xres, val);
}

/*Sets AUTN avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp AUTN avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_autn(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_autn, val);
}

/*Sets KASME avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp KASME avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_kasme(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_kasme, val);
}

/*Sets Confidentiality-Key avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Confidentiality-Key avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_confidentiality_key(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_confid_key, val);
}

/*Sets Integrity-Key avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Integrity-Key avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_integrity_key(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_integrity_key, val);
}

/*Sets Kc avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Kc avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_kc(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_kc, val);
}

/*Sets SRES avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp SRES avp.  
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_sres(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_sres, val);
}

/*Sets Cancellation-Type avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_cancellation_type(struct msg **msg, int val){	

	return set_int_value(msg, ss_cancel_type, val);
}

/*Sets CLR-Flags avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_clr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_clr_flgs, val);
}

/*Sets IDR- Flags avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_idr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_idr_flgs, val);
}

/*Sets IMS-Voice-Over-PS-Sessions-Supported avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ims_voice_over_ps_sessions_supported(struct msg **msg, int val){	

	return set_int_value(msg, ss_ims_voice_ovr_ps_sess_suprt, val);
}

/*Sets Last-UE-Activity-Time avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_last_ue_activity_time(struct msg **msg, char *val){	

	return set_str_value(msg, ss_last_ue_actv_tm, val);
}

/*Sets IDA- Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ida_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_ida_flgs, val);
}

/*Sets User-State avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Complete-Data-List-Included-Indicator avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_user_state(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_usr_state, val);
}

/*Sets Geographical-Information avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Geographical-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_geographical_information(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_geo_info, val);
}

/*Sets Geodetic-Information avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Geodetic-Information avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_geodetic_information(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_geodetic_info, val);
}

/*Sets Current-Location-Setd avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_current_location_Setd(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_curr_loc_retrvd, val);
}

/*Sets Age-Of-Location-Information avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_age_of_location_information(struct avp **gavp, uint32_t val){	

	return set_uint_value_gavp(gavp, ss_age_of_loc_info, val);
}

/*Sets CSG-Access-Mode avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_csg_access_mode(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_csg_accss_mode, val);
}

/*Sets CSG-Membership-Indication avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_csg_membership_indication(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_csg_memb_ind, val);
}

/*Sets Time-Zone avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Time-Zone avp.  
		ret: a pointer to a pointer where the result will be stored.The value is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_time_zone(struct avp **gavp, unsigned char *val){	

	return set_str_value_gavp(gavp, ss_tm_zn, val);
}

/*Sets Daylight-Saving-Time avp value to group avp 
	parameter:
		gavp: a pointer to a pointer to the group avp Daylight-Saving-Time avp.
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_daylight_saving_time(struct avp **gavp, int val){	
	return set_int_value_gavp(gavp, ss_daylit_sv_tm, val);
}

/*Sets DSR-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_dsr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_dsr_flgs, val);
}

/*Sets Context-Identifier avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_context_identifier(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_context_id, val);
}

/*Sets Trace-Reference avp value to to message 
	parameter:
		msg: a pointer to the message pointer. 
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_trace_reference(struct msg **msg, char *val){	

	return set_str_value(msg, ss_trace_ref, val);
}

/*Sets multiple TS-Code AVPs value to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ts_code(struct msg **msg, char *val){	
	
	return set_str_value(msg, ss_ts_code, val);		
}

/*Sets multiple SS-Code AVPs value to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_ss_code(struct msg **msg, char *val){	
	
	return set_str_value(msg, ss_ss_code, val);		
}

/*Sets DSA-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_dsa_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_dsa_flgs, val);
}

/*Sets PUR-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pur_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_pur_flgs, val);
}

/*Sets PUA-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_pua_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_pua_flgs, val);
}

/*Sets multiple User-Id AVPs value to message
	parameter:
		msg: a pointer to the message pointer.  
		val : a pointer to the value to be  set
	returns: 0 on success 1 on failure
*/
inline int ss_set_user_id(struct msg **msg, char *val){	
	
	return set_str_value(msg, ss_usr_id, val);		
}

/*Sets Visited-Network-Identifier avp value to message
	parameter:
		msg: a pointer to the message pointer.  
		ret: a pointer to a pointer where the result will be stored.The result is a pointer.
	returns: 0 on success 1 on failure
*/
inline int ss_set_visited_network_identifier(struct msg **msg, char *val){	

	return set_str_value(msg, ss_vistd_net_id, val);
}

/*Sets Service-Selection avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_service_selection(struct msg **msg, char *val){	

	return set_str_value(msg, ss_service_selection, val);
}

/*Sets Alert-Reason avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_alert_reason(struct msg **msg, int val){	

	return set_int_value(msg, ss_alert_reason, val);
}

/*Sets NOR-Flags avp value to message 
	parameter:
		msg: a pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_nor_flags(struct msg **msg, uint32_t val){	

	return set_uint_value(msg, ss_nor_flgs, val);
}

/*Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value to message 
	parameter:
		msg: pointer to the message pointer. 
		val: the value to be set
	returns: 0 on success 1 on failure
*/
inline int ss_set_homogeneous_support_ims_vop_sessions(struct msg **msg, int val){	

	return set_int_value(msg, ss_homog_suppr_ims_vop_sess, val);
}
