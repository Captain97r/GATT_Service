#include "sdk_common.h"
#include "ble_srv_common.h"
#include <string.h>
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "chars.cpp"






uint32_t ble_service_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init, uint8_t * service_num)
{
	if (p_cus == NULL || p_cus_init == NULL)
	{
		return NRF_ERROR_NULL;																//If parameters are wrong, generate an error
	}

	uint32_t   err_code;
	ble_uuid_t ble_uuid;
	ble_uuid128_t base_uuid = SERVICE_UUID_BASE;
	
	p_cus->evt_handler               = p_cus_init->evt_handler;
	p_cus->conn_handle               = BLE_CONN_HANDLE_INVALID;								// Initialize service structure
	p_cus->uuid_type                 = BLE_UUID_TYPE_VENDOR_BEGIN;
	
	
	//Adding Custom Service UUID to the BLE stack's table
	if (*service_num == 0)
	{		
		err_code =  sd_ble_uuid_vs_add(&base_uuid, &p_cus->uuid_type);
		VERIFY_SUCCESS(err_code);
	}
	
	
	ble_uuid.type = BLE_UUID_TYPE_VENDOR_BEGIN;
	ble_uuid.uuid = CUSTOM_SERVICE_UUID + *service_num;
	
	
	// Add the Custom Service
	err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_cus->service_handle);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}
	
	
	return ble_chars_create(p_cus, p_cus_init, service_num);
}



uint32_t ble_chars_create(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init, uint8_t * service_num)
{
	uint32_t   err_code;
	
	if (*service_num == 0)
	{
		err_code = patient_first_name_value_char_add(p_cus, p_cus_init);
		if (err_code != NRF_SUCCESS)
			return err_code;
	
		err_code = patient_last_name_value_char_add(p_cus, p_cus_init);
		if (err_code != NRF_SUCCESS)
			return err_code;
	
		err_code = patient_age_value_char_add(p_cus, p_cus_init);
		if (err_code != NRF_SUCCESS)
			return err_code;
		
		err_code = patient_birth_date_value_char_add(p_cus, p_cus_init);
		if (err_code != NRF_SUCCESS)
			return err_code;
	}
	
	if (*service_num == 1)
	{
		for (uint8_t num = 1; num <= 8; num++)
		{
			err_code = channel_value_char_add(p_cus, p_cus_init, &num);
			if (err_code != NRF_SUCCESS)
				return err_code;
		}
	}
	
	return err_code;
}



void ble_cus_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context)
{
	ble_cus_t * p_cus = (ble_cus_t *) p_context;
    
	if (p_cus == NULL || p_ble_evt == NULL)
	{
		return;
	}
	
	switch (p_ble_evt->header.evt_id)
	{
	case BLE_GAP_EVT_CONNECTED:
		on_connect(p_cus, p_ble_evt);
		break;

	case BLE_GAP_EVT_DISCONNECTED:
		on_disconnect(p_cus, p_ble_evt);
		break;
		
	case BLE_GATTS_EVT_WRITE:
		on_write(p_cus, (ble_evt_t *)p_ble_evt);
		break;

	default:
	    // No implementation needed.
		break;
	}
}




static void on_connect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
	p_cus->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
	
	ble_cus_evt_t evt;

	evt.evt_type = BLE_CUS_EVT_CONNECTED;

	p_cus->evt_handler(p_cus, &evt);
}





static void on_disconnect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt)
{
	UNUSED_PARAMETER(p_ble_evt);
	p_cus->conn_handle = BLE_CONN_HANDLE_INVALID;
}




static void on_write(ble_cus_t * p_cus, ble_evt_t * p_ble_evt)
{    
	ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
	
	// Check if the handle passed with the event matches the Custom Value Characteristic handle.
	if (p_evt_write->handle == p_cus->custom_value_handles.value_handle)
	{
		p_evt_write->data[0] == 0 ? nrf_gpio_pin_write(LED_4, 1) : nrf_gpio_pin_write(LED_4, 0);
	}
	 // Check if the Custom value CCCD is written to and that the value is the appropriate length, i.e 2 bytes.
	if ((p_evt_write->handle == p_cus->custom_value_handles.cccd_handle)
	   // && (p_evt_write->len == 2)
		)
	{

	        // CCCD written, call application event handler
		if (p_cus->evt_handler != NULL)
		{
			ble_cus_evt_t evt;

			if (ble_srv_is_notification_enabled(p_evt_write->data))
			{
				evt.evt_type = BLE_CUS_EVT_NOTIFICATION_ENABLED;
			}
			else
			{
				evt.evt_type = BLE_CUS_EVT_NOTIFICATION_DISABLED;
			}
			// Call the application event handler.
			p_cus->evt_handler(p_cus, &evt);
		}

	}
}






uint32_t ble_cus_custom_value_update(ble_cus_t * p_cus, uint8_t custom_value) {
	if (p_cus == NULL)
	{
		return NRF_ERROR_NULL;
	}
	
	uint32_t err_code = NRF_SUCCESS;
	ble_gatts_value_t gatts_value;

	// Initialize value struct.
	memset(&gatts_value, 0, sizeof(gatts_value));

	gatts_value.len     = MAX_CHAR_LENGTH * sizeof(uint8_t);
	gatts_value.offset  = 0;
	gatts_value.p_value = &custom_value;

	// Update database.
	err_code = sd_ble_gatts_value_set(p_cus->conn_handle,
		p_cus->custom_value_handles.value_handle,
		&gatts_value);
	if (err_code != NRF_SUCCESS)
	{
		return err_code;
	}
	
	// Send value if connected and notifying.
	if ((p_cus->conn_handle != BLE_CONN_HANDLE_INVALID)) 
	{
		ble_gatts_hvx_params_t hvx_params;

		memset(&hvx_params, 0, sizeof(hvx_params));

		hvx_params.handle = p_cus->custom_value_handles.value_handle;
		hvx_params.type   = BLE_GATT_HVX_NOTIFICATION;
		hvx_params.offset = gatts_value.offset;
		hvx_params.p_len  = &gatts_value.len;
		hvx_params.p_data = gatts_value.p_value;

		err_code = sd_ble_gatts_hvx(p_cus->conn_handle, &hvx_params);
	}
	else
	{
		err_code = NRF_ERROR_INVALID_STATE;
	}

	return err_code;
}