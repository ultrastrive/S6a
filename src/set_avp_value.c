
#include "ssix_interface.h"
#include "internal.h"

#define SS_SET_I32( value, avp)	{				\
	union avp_value v;							\
	v.i32= value;								\
	SS_CHECK(fd_msg_avp_setvalue(avp,&v));		\
}

#define SS_SET_U32( value, avp)  {					\
	union avp_value v;								\
	v.u32 = value;									\
	SS_CHECK(fd_msg_avp_setvalue(avp,&v));			\
}

#define SS_SET_OCTET( value, avp, len)  {			\
	union avp_value v;								\
	v.os.data = value;								\
	v.os.len = len;									\
	SS_CHECK(fd_msg_avp_setvalue(avp,&v));			\
}

/*Sets string values in AVP of type 'dict' and add it to a message 'msg'*/
static inline int set_str_value(avp_or_msg **msg_avp, struct dict_object *dict, unsigned char *val, size_t len){

	struct avp *avp = NULL;	

	/*Create an empty AVP of type 'dict'*/
	SS_CHECK(fd_msg_avp_new(dict,0,&avp));

	if (avp){ 	

		/*Set the value 'val' in to 'avp'*/
		SS_SET_OCTET( val, avp, len);

		/*Add 'avp' in to the message 'msg'*/
		SS_CHECK(fd_msg_avp_add(*msg_avp,MSG_BRW_LAST_CHILD,avp));	
		return 0;	
	}	

	return 1;
}

/*Sets integer values in AVP of type 'dict' and add it to a message 'msg'*/
static inline int set_int_value(avp_or_msg **msg_avp, struct dict_object *dict,  int32_t val){
	struct avp *avp = NULL;

	/*Create an empty AVP of type 'dict'*/
	SS_CHECK(fd_msg_avp_new(dict,0,&avp));

	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_I32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		SS_CHECK(fd_msg_avp_add(*msg_avp,MSG_BRW_LAST_CHILD,avp));	
		return 0;	
	}

	return 1;
}

/*Sets unsigned integer values in AVP of type 'dict' and add it to a message 'msg'*/
static inline  int set_uint_value(avp_or_msg **msg_avp, struct dict_object *dict, uint32_t val){
	struct avp *avp = NULL;

	/*Create an empty AVP of type 'dict'*/
	SS_CHECK(fd_msg_avp_new(dict,0,&avp));
	if (avp){
		/*Set the value 'val' in to 'avp'*/
		SS_SET_U32( val, avp);

		/*Add 'avp' in to the message 'msg'*/
		SS_CHECK(fd_msg_avp_add(*msg_avp,MSG_BRW_LAST_CHILD,avp));	
		return 0;	
	}

	return 1;
}

/*Sets Destination-Host avp value to message */
int ss_set_destination_host(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_destination_host, val, len);
}

/*Sets originating host avp value to message */
int ss_set_origin_host(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_origin_host, val, len);
}

/*Sets Destination-Realm avp value to message */
int ss_set_destination_realm(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_destination_realm, val, len);
}

/*Sets originating realm avp value to message */
int ss_set_origin_realm(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_origin_realm, val, len);
}

/*Sets User-Name (imsi) avp value to message */
int ss_set_user_name(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_user_name, val, len);
}

/*Sets RAT-Type avp value to message */
int ss_set_rat_type(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_rat_type, val);
}

/*Sets ULR-Flags avp value to message */
int ss_set_ulr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_ulr_flags, val);
}

/*Sets UE-SRVCC-Capability avp value to message */
int ss_set_ue_srvcc_capability(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_ue_srvcc_capability, val);
}

/*Sets Visited-PLMN-Id avp value to message */
int ss_set_visited_plmn_id(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_visited_plmn_id, val, len);
}

/*Sets SGSN-Number avp value to message */
int ss_set_sgsn_number(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_sgsn_number, val, len);
}

/*Sets Homogeneous-Support-of-IMS-Voice-Over-PS-Sessions avp value to message */
int ss_set_homogeneous_support_of_ims_voice_over_ps_sessions(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_homogeneous_support_of_ims_voice_over_ps_sessions, val);
}

/*Sets GMLC-Address avp value to message*/
int ss_set_gmlc_address(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_gmlc_address, val, len);
}

/*Sets MME-Number-for-MT-SMS avp value to message */
int ss_set_mme_number_for_mt_sms(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_mme_number_for_mt_sms, val, len);
}

/*Sets SMS-Register-Request avp value to message*/
int ss_set_sms_register_request(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_sms_register_request, val);
}

/*Sets Coupled-Node-Diameter-ID avp value to message*/
int ss_set_coupled_node_diameter_id(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_coupled_node_diameter_id, val, len);
}

/*Sets imei avp value to group avp*/
int ss_set_imei(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_imei, val, len);
}

/*Sets Software-Version avp value to group avp */
int ss_set_software_version(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_software_version, val, len);
}

/*Sets 3gpp2-meid avp value to group avp*/
int ss_set_3gpp2_meid(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_3gpp2_meid, val, len);
}

/*Sets MIP-Home-Agent-Address avp value to group avp*/
int ss_set_mip_home_agent_address(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_mip_home_agent_address, val, len);
}

/*Sets MIP-Home-Agent-Host avp value to group avp */
int ss_set_mip_home_agent_host(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_mip_home_agent_host, val, len);
}

/*Sets Result-Code avp value to message*/
int ss_set_result_code(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_result_code, val);
}

/*Sets Error-Diagnostic avp value to message*/
int ss_set_error_diagnostic(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_error_diagnostic, val);
}

/*Sets ULA-Flags avp value to message */
int ss_set_ula_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_ula_flags, val);
}

/*Sets Vendor-Id avp value to group avp */
int ss_set_vendor_id(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_vendor_id, val);
}

/*Sets Auth-Application-Id avp value and add it to group AVP*/
int ss_set_auth_application_id(struct avp **gavp, uint32_t val){
	return set_uint_value((avp_or_msg **)gavp, ss_auth_application_id, val);
}

/*Sets Experimental-Result-Code avp value to group avp*/
int ss_set_experimental_result_code(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_experimental_result_code, val);
}

/*Sets Subscriber-Status avp value to group avp*/
int ss_set_subscriber_status(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_subscriber_status, val);
}

/*Sets MSISDN avp value to group avp*/
int ss_set_msisdn(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_msisdn, val, len);
}

/*Sets A-MSISDN avp value to group avp */
int ss_set_a_msisdn(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_a_msisdn, val, len);
}

/*Sets STN-SR avp value to group avp*/
int ss_set_stn_sr(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_stn_sr, val, len);
}

/*Sets ICS-Indicator avp value to group avp */
int ss_set_ics_indicator(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_ics_indicator, val);
}

/*Sets Network-Access-Mode avp value to group avp */
int ss_set_network_access_mode(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_network_access_mode, val);
}

/*Sets Operator-Determined-Barring avp value to group avp*/
int ss_set_operator_determined_barring(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_operator_determined_barring, val);
}

/*Sets HPLMN-ODB avp value to group avp*/
int ss_set_hplmn_odb(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_hplmn_odb, val);
}

/*Sets Regional-Subscription-Zone-Code avp value to group avp*/
int ss_set_regional_subscription_zone_code(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_regional_subscription_zone_code, val, len);
}

/*Sets Access-Restriction-Data avp value to group avp */
int ss_set_access_restriction_data(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_access_restriction_data, val);
}

/*Sets APN-OI-Replacement avp value to group avp */
int ss_set_apn_oi_replacement(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_apn_oi_replacement, val, len);
}

/*Sets 3GPP-Charging-Characteristics avp value to group avp */
int ss_set_3gpp_charging_characteristics(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_3gpp_charging_characteristics, val, len);
}

/*Sets RAT-Frequency-Selection-Priority-ID avp value to group avp */
int ss_set_rat_frequency_selection_priority_id(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_rat_frequency_selection_priority_id, val);
}

/*Sets Roaming-Restricted-Due-To-Unsupported-Feature avp value to group avp*/
int ss_set_roaming_restricted_unsupported_feature(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_roaming_restricted_due_to_unsupported_feature, val);
}

/*Sets Subscribed-Periodic-RAU-TAU-Timer avp value to group avp */
int ss_set_subscribed_periodic_rau_tau_timer(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_subscribed_priodic_rau_tau_timer, val);
}

/*Sets MPS-Priority avp value to group avp */
int ss_set_mps_priority(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_mps_priority, val);
}

/*Sets VPLMN-LIPA-Allowed avp value to group avp */
int ss_set_vplmn_lipa_allowed(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_vplmn_lipa_allowed, val);
}

/*Sets Relay-Node-Indicator avp value to group avp*/
int ss_set_relay_node_indicator(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_relay_node_indicator, val);
}

/*Sets MDT-User-Consent avp value to group avp*/
int ss_set_mdt_user_consent(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_mdt_user_consent, val);
}

/*Sets Subscribed-VSRVCC avp value to group avp*/
int ss_set_subscribed_vsrvcc(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_subscribed_vsrvcc, val);
}

/*Sets Subscription-Data-Flags avp value to group avp*/
int ss_set_subscription_data_flags(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_subscription_data_flags, val);
}

/*Sets multiple GMLC-Number AVPs value to group avp */
int ss_set_gmlc_number(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_gmlc_number, val, len);		
}

/*Sets SS-Status avp value to group avp*/
int ss_set_ss_status(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_ss_status, val, len);
}

/*Sets Notification-To-UE-User avp value to group avp*/
int ss_set_notification_ue_user(struct avp **gavp,  int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_notification_to_ue_user, val);
}

/*Sets Client-Identity avp value to group avp*/
int ss_set_client_identity(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_client_identity, val, len);
}

/*Sets GMLC-Restriction avp value to group avp*/
int ss_set_gmlc_restriction(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_gmlc_restriction, val);
}

/*Sets multiple PLMN-Client AVPs value to group avp*/
int ss_set_plmn_client(struct avp **gavp,  int32_t val){	
	
	return set_int_value((avp_or_msg **)gavp, ss_plmn_client, val);		
}

/*Sets ServiceTypeIdentity avp value to group avp*/
int ss_set_serviceTypeIdentity(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_servicetypeidentity, val);
}

/*Sets Max-Requested-Bandwidth-UL avp value to group avp*/
int ss_set_max_requested_bandwidth_ul(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_max_requested_bandwidth_ul, val);
}

/*Sets Max-Requested-Bandwidth-DL avp value to group avp*/
int ss_set_max_requested_bandwidth_dl(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_max_requested_bandwidth_dl, val);
}

/*Sets All-APN-Configurations-Included-Indicator avp value to group avp*/
int ss_set_all_apn_configuration_included_indicator(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_all_apn_configurations_included_indicator, val);
}

/*Sets PDN-Type avp value to group avp */
int ss_set_pdn_type(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_pdn_type, val);
}

/*Sets VPLMN-Dynamic-Address-Allowed avp value to group avp*/
int ss_set_vplmn_dynamic_address_allowed(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_vplmn_dynamic_address_allowed, val);
}

/*Sets PDN-GW-Allocation-Type avp value to group avp*/
int ss_set_pdn_gw_allocation_type(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_pdn_gw_allocation_type, val);
}

/*Sets SIPTO-Permission avp value to group avp*/
int ss_set_sipto_permission(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_sipto_permission, val);
}

/*Sets LIPA-Permission avp value to group avp*/
int ss_set_lipa_permission(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_lipa_permission, val);
}

/*Sets Restoration-Priority avp value to group avp */
int ss_set_restoration_priority(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_restoration_priority, val);
}

/*Sets SIPTO-Local-Network-Permission avp value to group avp */
int ss_set_sipto_local_network_permission(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_sipto_local_network_permission, val);
}

/*Sets multiple Served-Party-IP-Address AVPs' values to group avp*/
int ss_set_served_party_ip_address(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_served_party_ip_address, val, len);		
}

/*Sets QoS-Class-Identifier avp value to group avp*/
int ss_set_qos_class_identifier(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_qos_class_identifier, val);
}

/*Sets Priority-Level avp value to group avp*/
int ss_set_priority_level(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_priority_level, val);
}

/*Sets Pre-emption-Capability avp value to group avp*/
int ss_set_pre_emption_capability(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_pre_emption_capability, val);
}

/*Sets Pre-emption-Vulnerability avp value to group avp*/
int ss_set_pre_emption_vulnerability(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_pre_emption_vulnerability, val);
}

/*Sets WLAN-offloadability-EUTRAN avp value to group avp*/
int ss_set_wlan_offloadability_eutran(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_wlan_offloadability_eutran, val);
}

/*Sets WLAN-offloadability-UTRAN avp value to group avp */
int ss_set_wlan_offloadability_utran(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_wlan_offloadability_utran, val);
}

/*Sets Trace-Depth avp value to group avp*/
int ss_set_trace_depth(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_trace_depth, val);
}

/*Sets Trace-NE-Type-List avp value to group avp*/
int ss_set_trace_ne_type_list(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_trace_ne_type_list, val, len);
}

/*Sets Trace-Interface-List avp value to group avp */
int ss_set_trace_interface_list(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_trace_interface_list, val, len);
}

/*Sets Trace-Event-List avp value to group avp */
int ss_set_trace_event_list(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_trace_event_list, val, len);
}

/*Sets OMC-Id avp value to group avp */
int ss_set_omc_id(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_omc_id, val, len);
}

/*Sets Trace-Collection-Entity avp value to group avp */
int ss_set_trace_collection_entity(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_trace_collection_entity, val, len);
}

/*Sets Job-Type avp value to group avp */
int ss_set_job_type(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_job_type, val);
}

/*Sets Cell-Global-Identity AVPs' values to group avp*/
int ss_set_cell_global_identity(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_cell_global_identity, val, len);		
}

/*Sets E-UTRAN-Cell-Global-Identity AVPs' values to group avp */
int ss_set_e_utran_cell_global_identity(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_e_utran_cell_global_identity, val, len);		
}

/*Sets Routing-Area-Identity AVPs' values to group avp */
int ss_set_routing_area_identity(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_routing_area_identity, val, len);		
}

/*Sets Location-Area-Identity AVPs' values to group avp*/
int ss_set_location_area_identity(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_location_area_identity, val, len);		
}

/*Sets Tracking-Area-Identity AVPs' values to group avp*/
int ss_set_tracking_area_identity(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_tracking_area_identity, val, len);		
}

/*Sets List-Of-Measurements avp value to group avp*/
int ss_set_list_of_measurements(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_list_of_measurements, val);
}

/*Sets Reporting-Trigger avp value to group avp*/
int ss_set_reporting_trigger(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_reporting_trigger, val);
}

/*Sets Report-Interval avp value to group avp*/
int ss_set_report_interval(struct avp **gavp, int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_report_interval, val);
}

/*Sets Report-Amount avp value to group avp*/
int ss_set_report_amount(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_report_amount, val);
}

/*Sets Event-Threshold-RSRP avp value to group avp*/
int ss_set_event_threshold_rsrp(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_event_threshold_rsrp, val);
}

/*Sets Event-Threshold-RSRQ avp value to group avp*/
int ss_set_event_threshold_rsrq(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_event_threshold_rsrq, val);
}

/*Sets Logging-Interval avp value to group avp */
int ss_set_logging_interval(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_logging_interval, val);
}

/*Sets Logging-Duration avp value to group avp*/
int ss_set_logging_duration(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_logging_duration, val);
}

/*Sets Measurement-Period-LTE avp value to group avp*/
int ss_set_measurement_period_lte(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_measurement_period_lte, val);
}

/*Sets Measurement-Period-UMTS avp value to group avp*/
int ss_set_measurement_period_umts(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_measurement_period_umts, val);
}

/*Sets Collection-Period-RRM-LTE avp value to group avp*/
int ss_set_collection_period_rrm_lte(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_collection_period_rrm_lte, val);
}

/*Sets Collection-Period-RRM-UMTS avp value to group avp*/
int ss_set_collection_period_rrm_umts(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_collection_period_rrm_umts, val);
}

/*Sets Positioning-Method avp value to group avp*/
int ss_set_positioning_method(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_positioning_method, val, len);
}

/*Sets Measurement-Quantity avp value to group avp*/
int ss_set_measurement_quantity(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_measurement_quantity, val, len);
}

/*Sets Event-Threshold-Event-1F avp value to group avp*/
int ss_set_event_threshold_event_1f(struct avp **gavp, int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_event_threshold_event_1f, val);
}

/*Sets Event-Threshold-Event-1I avp value to group avp */
int ss_set_event_threshold_event_1i(struct avp **gavp, int32_t val){	

	return set_int_value((avp_or_msg **)gavp, ss_event_threshold_event_1i, val);
}	

/*Sets multiple MDT-Allowed-PLMN-Id AVPs' values to group avp*/
int ss_set_mdt_allowed_plmn_id(struct avp **gavp, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)gavp, ss_mdt_allowed_plmn_id, val, len);		
}

/*Sets Complete-Data-List-Included-Indicator avp value to group avp*/
int ss_set_complete_data_list_included_indicator(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_complete_data_list_included_indicator, val);
}

/*Sets PDP-Type avp value to group avp*/
int ss_set_pdp_type(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_pdp_type, val, len);
}

/*Sets PDP-Address avp value to group avp*/
int ss_set_pdp_address(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_pdp_address, val, len);
}

/*Sets QoS-Subscribed avp value to group avp*/
int ss_set_qos_subscribed(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_qos_subscribed, val, len);
}

/*Sets Ext-PDP-Type avp value to group avp*/
int ss_set_ext_pdp_type(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_ext_pdp_type, val, len);
}

/*Sets Ext-PDP-Address avp value to group avp*/
int ss_set_ext_pdp_address(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_ext_pdp_address, val, len);
}

/*Sets CSG-Id avp value to group avp*/
int ss_set_csg_id(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_csg_id, val);
}

/*Sets Expiration-Date avp value to group avp*/
int ss_set_expiration_date(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_expiration_date, val, len);
}

/*Sets ProSe-Permission avp value to group avp */
int ss_set_prose_permission(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_prose_permission, val);
}

/*Sets Reset-ID AVPs' values to group avp*/
int ss_set_reset_id(struct msg **msg, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)msg, ss_reset_id, val, len);		
}

/*Sets Number-Of-Requested-Vectors avp value to group avp*/
int ss_set_number_of_requested_vectors(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_number_of_requested_vectors, val);
}

/*Sets Immediate-Response-Preferred avp value to group avp*/
int ss_set_immediate_response_preferred(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_immediate_response_preferred, val);
}

/*Sets Re-synchronization-Info avp value to group avp*/
int ss_set_re_synchronization_info(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_re_synchronization_info, val, len);
}

/*Sets Item-Number avp value to group avp*/
int ss_set_item_number(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_item_number, val);
}

/*Sets RAND avp value to group avp*/
int ss_set_rand(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_rand, val, len);
}

/*Sets XRES avp value to group avp*/
int ss_set_xres(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_xres, val, len);
}

/*Sets AUTN avp value to group avp*/
int ss_set_autn(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_autn, val, len);
}

/*Sets KASME avp value to group avp*/
int ss_set_kasme(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_kasme, val, len);
}

/*Sets Confidentiality-Key avp value to group avp*/
int ss_set_confidentiality_key(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_confidentiality_key, val, len);
}

/*Sets Integrity-Key avp value to group avp*/
int ss_set_integrity_key(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_integrity_key, val, len);
}

/*Sets Kc avp value to group avp*/
int ss_set_kc(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_kc, val, len);
}

/*Sets SRES avp value to group avp*/
int ss_set_sres(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_sres, val, len);
}

/*Sets Cancellation-Type avp value to message*/
int ss_set_cancellation_type(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_cancellation_type, val);
}

/*Sets CLR-Flags avp value to message*/
int ss_set_clr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_clr_flags, val);
}

/*Sets IDR- Flags avp value to message*/
int ss_set_idr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_idr_flags, val);
}

/*Sets IMS-Voice-Over-PS-Sessions-Supported avp value to message*/
int ss_set_ims_voice_over_ps_sessions_supported(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **)msg, ss_ims_voice_over_ps_sessions_supported, val);
}

/*Sets Last-UE-Activity-Time avp value to message*/
int ss_set_last_ue_activity_time(struct msg **msg, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)msg, ss_last_ue_activity_time, val, len);
}

/*Sets IDA-Flags avp value to message*/
int ss_set_ida_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_ida_flags, val);
}

/*Sets User-State avp value to group avp*/
int ss_set_user_state(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_user_state, val);
}

/*Sets Geographical-Information avp value to group avp*/
int ss_set_geographical_information( struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_geographical_information, val, len);
}

/*Sets Geodetic-Information avp value to group avp*/
int ss_set_geodetic_information(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_geodetic_information, val, len);
}

/*Sets Current-Location-Retrieved avp value to group avp*/
int ss_set_current_location_retrieved(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_current_location_retrieved, val);
}

/*Sets Age-Of-Location-Information avp value to group avp*/
int ss_set_age_of_location_information(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **)gavp, ss_age_of_location_information, val);
}

/*Sets CSG-Access-Mode avp value to group avp */
int ss_set_csg_access_mode(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_csg_access_mode, val);
}

/*Sets CSG-Membership-Indication avp value to group avp */
int ss_set_csg_membership_indication(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_csg_membership_indication, val);
}

/*Sets Time-Zone avp value to group avp*/
int ss_set_time_zone(struct avp **gavp, unsigned char *val, size_t len){	

	return set_str_value((avp_or_msg **)gavp, ss_time_zone, val, len);
}

/*Sets Daylight-Saving-Time avp value to group avp*/
int ss_set_daylight_saving_time(struct avp **gavp,  int32_t val){	
	return set_int_value((avp_or_msg **)gavp, ss_daylight_saving_time, val);
}

/*Sets DSR-Flags avp value to message*/
int ss_set_dsr_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_dsr_flags, val);
}

/*Sets Context-Identifier avp value to message */
int ss_set_context_identifier(avp_or_msg **msg_avp, uint32_t val){	

	return set_uint_value(msg_avp, ss_context_identifier, val);
}

/*Sets Trace-Reference avp value to to message*/
int ss_set_trace_reference(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_trace_reference, val, len);
}

/*Sets multiple TS-Code AVPs value to message*/
int ss_set_ts_code(avp_or_msg **msg_avp, unsigned char *val, size_t len){	
	
	return set_str_value(msg_avp, ss_ts_code, val, len);		
}

/*Sets multiple SS-Code AVPs value to message*/
int ss_set_ss_code(avp_or_msg **msg_avp, unsigned char *val, size_t len){	
	
	return set_str_value(msg_avp, ss_ss_code, val, len);		
}

/*Sets DSA-Flags avp value to message*/
int ss_set_dsa_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_dsa_flags, val);
}

/*Sets PUR-Flags avp value to message*/
int ss_set_pur_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **)msg, ss_pur_flags, val);
}

/*Sets PUA-Flags avp value to message*/
int ss_set_pua_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg *)msg, ss_pua_flags, val);
}

/*Sets multiple User-Id AVPs value to message*/
int ss_set_user_id(struct msg **msg, unsigned char *val, size_t len){	
	
	return set_str_value((avp_or_msg **)msg, ss_user_id, val, len);		
}

/*Sets Visited-Network-Identifier avp value to message*/
int ss_set_visited_network_identifier(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_visited_network_identifier, val, len);
}

/*Sets Service-Selection avp value to message*/
int ss_set_service_selection(avp_or_msg **msg_avp, unsigned char *val, size_t len){	

	return set_str_value(msg_avp, ss_service_selection, val, len);
}

/*Sets Alert-Reason avp value to message*/
int ss_set_alert_reason(struct msg **msg,  int32_t val){	

	return set_int_value((avp_or_msg **) msg, ss_alert_reason, val);
}

/*Sets NOR-Flags avp value to message */
int ss_set_nor_flags(struct msg **msg, uint32_t val){	

	return set_uint_value((avp_or_msg **) msg, ss_nor_flags, val);
}

/*Sets Feature-List-ID  avp value to group avp*/
int ss_set_feature_list_id(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **) gavp, ss_feature_list_id, val);
}

/*Sets Feature-List avp value to group avp*/
int ss_set_feature_list(struct avp **gavp, uint32_t val){	

	return set_uint_value((avp_or_msg **) gavp, ss_feature_list, val);
}
