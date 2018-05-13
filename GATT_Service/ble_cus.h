#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"


#define CUSTOM_SERVICE_UUID_BASE         {0x85, 0xD2, 0xAA, 0x52, 0x0A, 0xAC, \
										  0xCE, 0x88, \
										  0xC6, 0x4C, \
										  0xB9, 0x07, \
										  0xB0, 0xA8, 0xCF, 0xD5}								// Service UUID: d5cfa8b0-07b9-4cc6-88ce-ac0a52aad285 (reversed for small-endian representation)

#define CUSTOM_SERVICE_UUID               0x1400												//Characteristic UUID
#define CUSTOM_VALUE_CHAR_UUID            0x1401												//Value UUID
//#define MAX_CHAR_LENGTH                   NRF_SDH_BLE_GATT_MAX_MTU_SIZE - 3
#define MAX_CHAR_LENGTH                   1




/**@brief   Macro for defining a ble_cus instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_CUS_DEF(_name)     \
static ble_cus_t _name;		   \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_cus_on_ble_evt, &_name)
	
	
	
	
typedef struct ble_cus_s ble_cus_t;								  // Forward declaration of the ble_cus_t type.





typedef enum
{
	BLE_CUS_EVT_NOTIFICATION_ENABLED,                             /**< Custom value notification enabled event. */
	BLE_CUS_EVT_NOTIFICATION_DISABLED,                            /**< Custom value notification disabled event. */
	BLE_CUS_EVT_DISCONNECTED,
	BLE_CUS_EVT_CONNECTED
} ble_cus_evt_type_t;




/**@brief Custom Service event. */
typedef struct
{
	ble_cus_evt_type_t evt_type;                                  /**< Type of event. */
} ble_cus_evt_t;

	



/**@brief Custom Service event handler type. */
typedef void(*ble_cus_evt_handler_t)(ble_cus_t * p_cus, ble_cus_evt_t * p_evt);



	

/**@brief Custom Service init structure. This contains all options and data needed for
 *        initialization of the service.*/
typedef struct
{
	ble_cus_evt_handler_t         evt_handler;                   /**< Event handler to be called for handling events in the Custom Service. */
	uint8_t                       initial_custom_value;          /**< Initial custom value */
	ble_srv_cccd_security_mode_t  custom_value_char_attr_md;     /**< Initial security level for Custom characteristics attribute */
} ble_cus_init_t;




/**@brief Custom Service structure. This contains various status information for the service. */
struct ble_cus_s
{
	ble_cus_evt_handler_t         evt_handler;                    /**< Event handler to be called for handling events in the Custom Service. */
	uint16_t                      service_handle;                 /**< Handle of Custom Service (as provided by the BLE stack). */
	ble_gatts_char_handles_t      custom_value_handles;           /**< Handles related to the Custom Value characteristic. */
	uint16_t                      conn_handle;                    /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
	uint8_t                       uuid_type; 
};






/**@brief Function for initializing the Custom Service.
 *
 * @param[out]  p_cus       Custom Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_cus_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_cus_init(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);



/**@brief Function for adding the Custom Value characteristic.
 *
 * @param[in]   p_cus        Custom Service structure.
 * @param[in]   p_cus_init   Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
static uint32_t custom_value_char_add(ble_cus_t * p_cus, const ble_cus_init_t * p_cus_init);



/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Battery Service.
 *
 * @note 
 *
 * @param[in]   p_ble_evt  Event received from the BLE stack.
 * @param[in]   p_context  Custom Service structure.
 */
void ble_cus_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);




/**@brief Function for handling the Connect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_connect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt);




/**@brief Function for handling the Disconnect event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_disconnect(ble_cus_t * p_cus, ble_evt_t const * p_ble_evt);





/**@brief Function for handling the Write event.
 *
 * @param[in]   p_cus       Custom Service structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
static void on_write(ble_cus_t * p_cus, ble_evt_t * p_ble_evt);





/**@brief Function for updating the custom value.
 *
 * @details The application calls this function when the cutom value should be updated. If
 *          notification has been enabled, the custom value characteristic is sent to the client.
 *
 * @note 
 *       
 * @param[in]   p_cus          Custom Service structure.
 * @param[in]   Custom value 
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */

uint32_t ble_cus_custom_value_update(ble_cus_t * p_cus, uint8_t custom_value);


