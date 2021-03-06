#ifndef INTERNAL_SSIX
#define INTERNAL_SSIX

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>

#ifdef DEBUG

#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SS_CHECK(__fnc__) {																	\
    int ret = __fnc__;																		\
	if(0 != ret){																			\
		fprintf(stderr, "\x1b[33m""Error : '%s' , call to function %s returns : '%s'""\x1b[0m""\n", strerror(ret), #__fnc__, strerror(ret));	\
		return ret;																			\
	}																						\
}

#else

#define SS_CHECK(__fnc__) {																	\
	int ret = __fnc__;																		\
	if(0 != ret) return ret;																\
}

#endif


#define NO_STATE_MAINTAINED 1			/*Auth-Session-State AVP value for all S6a messages*/
#define VENDOR_ID_3GPP 		10415		/*Vendor-Id AVP value for 3gpp*/
#define SSIX_APPLICATION_ID 16777251	/*Auth-Application-Id AVP value for S6a interface application*/

/*Dictionary objects for AVPs*/
extern struct dict_object * ss_origin_host;
extern struct dict_object * ss_origin_realm;
extern struct dict_object * ss_destination_host;
extern struct dict_object * ss_destination_realm;
extern struct dict_object * ss_session_id;
extern struct dict_object * ss_vendor_specific_application_id;
extern struct dict_object * ss_auth_session_state;
extern struct dict_object * ss_user_name;
extern struct dict_object * ss_vendor_id;
extern struct dict_object * ss_supported_features;
extern struct dict_object * ss_vplmn_csg_subscription_data;
extern struct dict_object * ss_user_id;
extern struct dict_object * ss_feature_list_id;
extern struct dict_object * ss_feature_list;
extern struct dict_object * ss_terminal_information;
extern struct dict_object * ss_mip6_agent_info;
extern struct dict_object * ss_rat_type;
extern struct dict_object * ss_requested_eutran_authentication_info;
extern struct dict_object * ss_requested_utran_geran_authentication_info;
extern struct dict_object * ss_cancellation_type;
extern struct dict_object * ss_ulr_flags;
extern struct dict_object * ss_clr_flags;
extern struct dict_object * ss_idr_flags;
extern struct dict_object * ss_dsr_flags;
extern struct dict_object * ss_pur_flags;
extern struct dict_object * ss_ue_srvcc_capability;	
extern struct dict_object * ss_context_identifier;
extern struct dict_object * ss_service_selection;
extern struct dict_object * ss_alert_reason;
extern struct dict_object * ss_nor_flags;
extern struct dict_object * ss_trace_reference;
extern struct dict_object * ss_ts_code;
extern struct dict_object * ss_ss_code;
extern struct dict_object * ss_visited_plmn_id;
extern struct dict_object * ss_sgsn_number;
extern struct dict_object * ss_homogeneous_support_of_ims_voice_over_ps_sessions;
extern struct dict_object * ss_gmlc_address;
extern struct dict_object * ss_active_apn;
extern struct dict_object * ss_equivalent_plmn_list;
extern struct dict_object * ss_mme_number_for_mt_sms;
extern struct dict_object * ss_sms_register_request;
extern struct dict_object * ss_result_code; 
extern struct dict_object * ss_experimental_result;
extern struct dict_object * ss_error_diagnostic;
extern struct dict_object * ss_ims_voice_over_ps_sessions_supported;
extern struct dict_object * ss_last_ue_activity_time;
extern struct dict_object * ss_ula_flags;
extern struct dict_object * ss_ida_flags;
extern struct dict_object * ss_dsa_flags;
extern struct dict_object * ss_pua_flags;
extern struct dict_object * ss_eps_user_state;
extern struct dict_object * ss_eps_location_information;
extern struct dict_object * ss_local_time_zone;
extern struct dict_object * ss_subscription_data;
extern struct dict_object * ss_reset_id;
extern struct dict_object * ss_authentication_info;
extern struct dict_object * ss_failed_avp;
extern struct dict_object * ss_coupled_node_diameter_id; 

/*Dictionary object for Vendor-Specific-Application-Id AVP child AVPs*/
extern struct dict_object * ss_auth_application_id;
/*Dictionary object for Authentication-Info AVP child AVPs*/
extern struct dict_object * ss_e_utran_vector;
extern struct dict_object * ss_utran_vector;
extern struct dict_object * ss_geran_vector; 

/*Dictionary object for E-UTRAN-Vector/UTRAN-Vector/GERAN-Vector AVP child AVPs*/
extern struct dict_object * ss_item_number;
extern struct dict_object * ss_rand; 
extern struct dict_object * ss_xres;
extern struct dict_object * ss_autn;
extern struct dict_object * ss_kasme; 		/*E-UTRAN-Vector only*/
extern struct dict_object * ss_confidentiality_key; 	/*UTRAN-Vector only*/
extern struct dict_object * ss_integrity_key;	/*UTRAN-Vector only*/
extern struct dict_object * ss_sres; 			/*GERAN-Vector only*/
extern struct dict_object * ss_kc;			/*GERAN-Vector only*/
 
/*Dictionary object for Requested-EUTRAN-Authentication-Info/equested-UTRAN-GE
RAN-Authentication-Info  AVP child AVPs*/
extern struct dict_object * ss_number_of_requested_vectors;
extern struct dict_object * ss_immediate_response_preferred; 
extern struct dict_object * ss_re_synchronization_info;  

/*Dictionary object for Terminal-Information AVP child AVPs*/
extern struct dict_object * ss_imei;
extern struct dict_object * ss_software_version;
extern struct dict_object * ss_3gpp2_meid;

/*Dictionary object for Subscription-Data AVP child AVPs*/
extern struct dict_object * ss_subscriber_status;
extern struct dict_object * ss_msisdn; 
extern struct dict_object * ss_a_msisdn;  
extern struct dict_object * ss_stn_sr; 
extern struct dict_object * ss_ics_indicator;
extern struct dict_object * ss_network_access_mode; 
extern struct dict_object * ss_operator_determined_barring; 
extern struct dict_object * ss_hplmn_odb;
extern struct dict_object * ss_regional_subscription_zone_code;
extern struct dict_object * ss_access_restriction_data;
extern struct dict_object * ss_apn_oi_replacement;
extern struct dict_object * ss_lcs_info;
extern struct dict_object * ss_teleservice_list;
extern struct dict_object * ss_call_barring_info;
extern struct dict_object * ss_3gpp_charging_characteristics;  
extern struct dict_object * ss_ambr; 
extern struct dict_object * ss_apn_configuration_profile;
extern struct dict_object * ss_rat_frequency_selection_priority_id; 
extern struct dict_object * ss_trace_data;
extern struct dict_object * ss_gprs_subscription_data;
extern struct dict_object * ss_csg_subscription_data; 
extern struct dict_object * ss_roaming_restricted_due_to_unsupported_feature;
extern struct dict_object * ss_subscribed_priodic_rau_tau_timer; 
extern struct dict_object * ss_mps_priority;
extern struct dict_object * ss_vplmn_lipa_allowed;
extern struct dict_object * ss_relay_node_indicator; 
extern struct dict_object * ss_mdt_user_consent;
extern struct dict_object * ss_subscribed_vsrvcc; 
extern struct dict_object * ss_prose_subscription_data;
extern struct dict_object * ss_subscription_data_flags;
	

/*Dictionary object for APN-Configuration-Profile AVP child AVPs*/
extern struct dict_object * ss_all_apn_configurations_included_indicator; 
extern struct dict_object * ss_apn_configuration;

/*Dictionary object for APN-Configuration AVP child AVPs*/
extern struct dict_object * ss_served_party_ip_address; 
extern struct dict_object * ss_pdn_type;
extern struct dict_object * ss_eps_subscribed_qos_profile; 
extern struct dict_object * ss_vplmn_dynamic_address_allowed;
extern struct dict_object * ss_visited_network_identifier;
extern struct dict_object * ss_pdn_gw_allocation_type; 
extern struct dict_object * ss_specific_apn_info;	
extern struct dict_object * ss_sipto_permission;
extern struct dict_object * ss_lipa_permission;
extern struct dict_object * ss_restoration_priority;
extern struct dict_object * ss_sipto_local_network_permission;
extern struct dict_object * ss_wlan_offloadability;

/*Dictionary object for EPS-Subscribed-QoS-Profile AVP child AVPs*/
extern struct dict_object * ss_qos_class_identifier; 
extern struct dict_object * ss_allocation_retention_priority;
	
/*Dictionary object for Allocation-Retention-Priority AVP child AVPs*/
extern struct dict_object * ss_priority_level;
extern struct dict_object * ss_pre_emption_capability;
extern struct dict_object * ss_pre_emption_vulnerability; 
 
/*Dictionary object for AMBR AVP child AVPs*/
extern struct dict_object * ss_max_requested_bandwidth_ul;
extern struct dict_object * ss_max_requested_bandwidth_dl;

/*Dictionary object for MIP6-Agent-In AVP child AVPs*/
extern struct dict_object * ss_mip_home_agent_address;
extern struct dict_object * ss_mip_home_agent_host;

/*Dictionary object for Trace-Data AVP child AVPs*/
extern struct dict_object * ss_trace_depth; 
extern struct dict_object * ss_trace_ne_type_list;
extern struct dict_object * ss_trace_interface_list; 
extern struct dict_object * ss_trace_event_list;  
extern struct dict_object * ss_omc_id;  
extern struct dict_object * ss_trace_collection_entity;  
extern struct dict_object * ss_mdt_configuration;

/*Dictionary object for GPRS-Subscription-Data  AVP child AVPs*/
extern struct dict_object * ss_complete_data_list_included_indicator;  
extern struct dict_object * ss_pdp_context;
	
/*Dictionary object for PDP-Context  AVP child AVPs*/
extern struct dict_object * ss_pdp_type; 
extern struct dict_object * ss_pdp_address; 
extern struct dict_object * ss_qos_subscribed;
extern struct dict_object * ss_ext_pdp_type;
extern struct dict_object * ss_ext_pdp_address;  

/*Dictionary object for CSG-Subscription-Data  AVP child AVPs*/
extern struct dict_object * ss_csg_id;   
extern struct dict_object * ss_expiration_date; 

/*Dictionary object for LCS-Info   AVP child AVPs*/
extern struct dict_object * ss_gmlc_number;   
extern struct dict_object * ss_lcs_privacyexception;
extern struct dict_object * ss_mo_lr; 

/*Dictionary object for LCS-PrivacyException AVP child AVPs*/
extern struct dict_object * ss_ss_status; 
extern struct dict_object * ss_notification_to_ue_user; 
extern struct dict_object * ss_external_client;
extern struct dict_object * ss_plmn_client;
extern struct dict_object * ss_service_type; 

/*Dictionary object for External-Client AVP child AVPs*/
extern struct dict_object * ss_client_identity;
extern struct dict_object * ss_gmlc_restriction;
	
/*Dictionary object for Service-Type AVP child AVPs*/
extern struct dict_object * ss_servicetypeidentity;

/*Dictionary object for EPS-User-State AVP child AVPs*/
extern struct dict_object * ss_mme_user_state;
extern struct dict_object * ss_sgsn_user_state;	

/*Dictionary object for EPS-Location-Information AVP child AVPs*/
extern struct dict_object * ss_mme_location_information;
extern struct dict_object * ss_sgsn_locationinformation;
	 
/*Dictionary object for MME-User-State  AVP child AVPs*/
extern struct dict_object * ss_user_state;

/*Dictionary object for MME-LocationInformation AVP child AVPs*/
extern struct dict_object * ss_e_utran_cell_global_identity;
extern struct dict_object * ss_tracking_area_identity;
extern struct dict_object * ss_geographical_information;
extern struct dict_object * ss_geodetic_information;
extern struct dict_object * ss_current_location_retrieved;
extern struct dict_object * ss_age_of_location_information;
extern struct dict_object * ss_user_csg_information;

/*Dictionary object for SGSN-Location-Information AVP child AVPs*/
extern struct dict_object * ss_cell_global_identity;
extern struct dict_object * ss_location_area_identity;
extern struct dict_object * ss_service_area_identity;
extern struct dict_object * ss_routing_area_identity;

/*Dictionary object for User-CSG-Information AVP child AVPs*/
extern struct dict_object * ss_csg_access_mode;
extern struct dict_object * ss_csg_membership_indication;


/*Dictionary object for MDT-Configuration AVP child AVPs*/
extern struct dict_object * ss_job_type;
extern struct dict_object * ss_area_scope;
extern struct dict_object * ss_list_of_measurements;
extern struct dict_object * ss_reporting_trigger;
extern struct dict_object * ss_report_interval;
extern struct dict_object * ss_report_amount;
extern struct dict_object * ss_event_threshold_rsrp;
extern struct dict_object * ss_event_threshold_rsrq;
extern struct dict_object * ss_logging_interval;
extern struct dict_object * ss_logging_duration;
extern struct dict_object * ss_measurement_period_lte;
extern struct dict_object * ss_measurement_period_umts;
extern struct dict_object * ss_collection_period_rrm_lte;
extern struct dict_object * ss_collection_period_rrm_umts;
extern struct dict_object * ss_positioning_method;
extern struct dict_object * ss_measurement_quantity;
extern struct dict_object * ss_event_threshold_event_1f;
extern struct dict_object * ss_event_threshold_event_1i;
extern struct dict_object * ss_mdt_allowed_plmn_id;

/*Dictionary object for Local-Time-Zone AVP child AVPs*/
extern struct dict_object * ss_time_zone;
extern struct dict_object * ss_daylight_saving_time;
	
/*Dictionary object for ProSe-Subscription-Data AVP child AVPs*/
extern struct dict_object * ss_prose_permission;

/*Dictionary object for WLAN-offloadability AVP child AVPs*/
extern struct dict_object * ss_wlan_offloadability_eutran;
extern struct dict_object * ss_wlan_offloadability_utran;

/*Dictionary object for  Experimental-Result AVP child AVPs*/
extern struct dict_object * ss_experimental_result_code;

/*Dictionary object for commands*/
extern struct dict_object * ss_vendor;
extern struct dict_object * ss_app;
extern struct dict_object * ss_cmd_ulr;
extern struct dict_object * ss_cmd_ula;
extern struct dict_object * ss_cmd_air;
extern struct dict_object * ss_cmd_aia;
extern struct dict_object * ss_cmd_clr;
extern struct dict_object * ss_cmd_cla;
extern struct dict_object * ss_cmd_idr;
extern struct dict_object * ss_cmd_ida;
extern struct dict_object * ss_cmd_dsr;
extern struct dict_object * ss_cmd_dsa;
extern struct dict_object * ss_cmd_pur;
extern struct dict_object * ss_cmd_pua;
extern struct dict_object * ss_cmd_rsr;
extern struct dict_object * ss_cmd_rsa;
extern struct dict_object * ss_cmd_nor;
extern struct dict_object * ss_cmd_noa;


/*Initialized the necessary dictionary objects*/
int ss_dict_init();

/*Loads the AVP definition required for S6a interface*/
int ss_dict_load_dict();

#endif
