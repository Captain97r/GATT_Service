#include "ble_cus.h"


#define FIRST_NAME_VALUE_CHAR_UUID					0x2A8A
#define LAST_NAME_VALUE_CHAR_UUID					0x2A90	
#define AGE_VALUE_CHAR_UUID							0x2A80
#define BIRTH_DATE_VALUE_CHAR_UUID					0x2A85

#define FIRST_CHANNEL_VALUE_CHAR_UUID				0x1400


static uint32_t patient_first_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_last_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_age_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_birth_date_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t channel_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init, uint8_t * number);