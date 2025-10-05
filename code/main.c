#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/watchdog.h"
#include "hardware/vreg.h"

// USB-related
#include "bsp/board.h"
#include "tusb_config.h"

// Time to restart after USB rewrite.
#define EJECTTIME_MS 500

extern uint32_t fullUSBWriteDone;

void __not_in_flash_func( writeEEPROMToFlash )( uint8_t* eepromBuff, 
  uint32_t flashAddr, uint32_t eepromSize ) {
  // Not interrupt-safe.
  uint32_t ints = save_and_disable_interrupts();

  flash_range_erase( flashAddr, eepromSize );
  flash_range_program( flashAddr, eepromBuff, eepromSize );
  
  // Restore interrupts.
  restore_interrupts ( ints );
}

void softwareReset()
{
    watchdog_enable( 1, 1 );
    while( 1 );
}

int main(){
  
  // Start USB-related tasks.
  board_init();
  tusb_init();
  
  while ( 1 ) {
    tud_task();
    
    // In case a full rewrite happened, we restart the RP2040 to get back
    if ( fullUSBWriteDone && 
         ( to_ms_since_boot( get_absolute_time() ) - fullUSBWriteDone > EJECTTIME_MS ) ) {
      softwareReset();
    }
  }

  return 0;
}

// USB-related callback functions.

void tud_mount_cb(void)
{
  
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  
}
