#include "chars.h"
#include "sdk_common.h"
#include "ble_srv_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"


#define FIRST_NAME_VALUE_CHAR_UUID					0x2A8A
#define LAST_NAME_VALUE_CHAR_UUID					0x2A90	
#define AGE_VALUE_CHAR_UUID							0x2A80
#define BIRTH_DATE_VALUE_CHAR_UUID					0x2A85



static uint32_t patient_first_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
	uint32_t            err_code;
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_t    attr_char_value;
	ble_uuid_t          ble_uuid;
	ble_gatts_attr_md_t attr_md;
	
	
	
	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read   = 1;
	char_md.char_props.write  = 1;
	char_md.char_props.notify = 0; 
	char_md.p_char_user_desc  = NULL;
	char_md.p_char_pf         = NULL;
	char_md.p_user_desc_md    = NULL;
	char_md.p_cccd_md         = NULL; 
	char_md.p_sccd_md         = NULL;
	
	
	memset(&attr_md, 0, sizeof(attr_md));

	attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
	attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
	attr_md.vloc       = BLE_GATTS_VLOC_STACK;
	attr_md.rd_auth    = 0;
	attr_md.wr_auth    = 0;
	attr_md.vlen       = 0;
	
	
	
	ble_uuid.type = BLE_UUID_TYPE_BLE;
	ble_uuid.uuid = FIRST_NAME_VALUE_CHAR_UUID;
	
	
	
	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_uuid    = &ble_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len  = sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len   = 20 * sizeof(uint8_t);
	
	
	
	err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle,
		&char_md,
		&attr_char_value,
		&p_cus->custom_value_handles);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}

	return NRF_SUCCESS;
}


static uint32_t patient_last_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
	uint32_t            err_code;
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_t    attr_char_value;
	ble_uuid_t          ble_uuid;
	ble_gatts_attr_md_t attr_md;
	
	
	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read   = 1;
	char_md.char_props.write  = 1;
	char_md.char_props.notify = 0; 
	char_md.p_char_user_desc  = NULL;
	char_md.p_char_pf         = NULL;
	char_md.p_user_desc_md    = NULL;
	char_md.p_cccd_md         = NULL; 
	char_md.p_sccd_md         = NULL;
	
	
	memset(&attr_md, 0, sizeof(attr_md));

	attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
	attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
	attr_md.vloc       = BLE_GATTS_VLOC_STACK;
	attr_md.rd_auth    = 0;
	attr_md.wr_auth    = 0;
	attr_md.vlen       = 0;
	
	
	
	ble_uuid.type = BLE_UUID_TYPE_BLE;
	ble_uuid.uuid = LAST_NAME_VALUE_CHAR_UUID;
	
	
	
	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_uuid    = &ble_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len  = sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len   = 20 * sizeof(uint8_t);
	
	
	
	err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle,
		&char_md,
		&attr_char_value,
		&p_cus->custom_value_handles);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}

	return NRF_SUCCESS;
}



static uint32_t patient_age_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
	uint32_t            err_code;
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_t    attr_char_value;
	ble_uuid_t          ble_uuid;
	ble_gatts_attr_md_t attr_md;
	
	
	
	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read   = 1;
	char_md.char_props.write  = 1;
	char_md.char_props.notify = 0; 
	char_md.p_char_user_desc  = NULL;
	char_md.p_char_pf         = NULL;
	char_md.p_user_desc_md    = NULL;
	char_md.p_cccd_md         = NULL;
	char_md.p_sccd_md         = NULL;
	
	
	memset(&attr_md, 0, sizeof(attr_md));

	attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
	attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
	attr_md.vloc       = BLE_GATTS_VLOC_STACK;
	attr_md.rd_auth    = 0;
	attr_md.wr_auth    = 0;
	attr_md.vlen       = 0;
	
	
	
	ble_uuid.type = BLE_UUID_TYPE_BLE;
	ble_uuid.uuid = AGE_VALUE_CHAR_UUID;
	
	
	
	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_uuid    = &ble_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len  = sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len   = 2 * sizeof(uint8_t);
	
	
	
	err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle,
		&char_md,
		&attr_char_value,
		&p_cus->custom_value_handles);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}

	return NRF_SUCCESS;
}



static uint32_t patient_birth_date_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init)
{
	uint32_t            err_code;
	ble_gatts_char_md_t char_md;
	ble_gatts_attr_md_t cccd_md;
	ble_gatts_attr_t    attr_char_value;
	ble_uuid_t          ble_uuid;
	ble_gatts_attr_md_t attr_md;
	
	
	
	memset(&char_md, 0, sizeof(char_md));

	char_md.char_props.read   = 1;
	char_md.char_props.write  = 1;
	char_md.char_props.notify = 0; 
	char_md.p_char_user_desc  = NULL;
	char_md.p_char_pf         = NULL;
	char_md.p_user_desc_md    = NULL;
	char_md.p_cccd_md         = NULL;
	char_md.p_sccd_md         = NULL;
	
	
	memset(&attr_md, 0, sizeof(attr_md));

	attr_md.read_perm  = p_cus_init->custom_value_char_attr_md.read_perm;
	attr_md.write_perm = p_cus_init->custom_value_char_attr_md.write_perm;
	attr_md.vloc       = BLE_GATTS_VLOC_STACK;
	attr_md.rd_auth    = 0;
	attr_md.wr_auth    = 0;
	attr_md.vlen       = 0;
	
	
	
	ble_uuid.type = BLE_UUID_TYPE_BLE;
	ble_uuid.uuid = BIRTH_DATE_VALUE_CHAR_UUID;
	
	
	
	memset(&attr_char_value, 0, sizeof(attr_char_value));

	attr_char_value.p_uuid    = &ble_uuid;
	attr_char_value.p_attr_md = &attr_md;
	attr_char_value.init_len  = sizeof(uint8_t);
	attr_char_value.init_offs = 0;
	attr_char_value.max_len   = 10 * sizeof(uint8_t);
	
	
	
	err_code = sd_ble_gatts_characteristic_add(p_cus->service_handle,
		&char_md,
		&attr_char_value,
		&p_cus->custom_value_handles);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}

	return NRF_SUCCESS;
}