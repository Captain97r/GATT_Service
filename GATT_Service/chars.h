#include "ble_cus.h"

/**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t patient_first_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_last_name_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_age_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);


static uint32_t patient_birth_date_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);