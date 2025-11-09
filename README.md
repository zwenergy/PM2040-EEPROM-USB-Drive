# PM2040 EEPROM USB Drive
An alternative firmware for the PM2040 flash cart, which turns it into a USB drive to backup and restore EEPROM saves.

## Overview
This FW for the PM2040 flash cart can be used in conjunction with the [PM2040 EEPROM Manager](https://github.com/zwenergy/PM2040-EEPROM-Manager) to externally backup and manage EEPROM images of a Pokemon mini.
When flashed onto a PM2040, this firmware turns the flash cart into a "USB drive" mode for the EEPROM slots.
Connecting it to a computer, the PM2040 will act as a mass storage device, from which the EEPROM backups can be copied from.

**Note: All slots are always shown, even when nothing have been backed up to them yet.**

## Writing / Restore
Currently only the **first slot** can be overwritten via USB.
When any EEPROM backup is copied to the cart (...or more exactly any file which is exactly 8192 bytes large), the first EEPROM slot is overwritten.
The PM2040 is then automatically ejected, while internally the EEPROM slot is re-flashed.
After it, the PM2040 will be connected again.

## Managing Single Save Games
The EEPROM file is a complete image of the internal EEPROM memory, so it contains up to 6 save games.
To further manage single save games, export, merge and create new EEPROM images for the Pokemon mini, you can use a very handy tool made by *thx*:
[Pokémon Mini EEPROM Manager](https://pokeminisaves.github.io/) .

## Firmware choice
For "regular" PM2040 carts with 2 MB Flash chips, use the 2 MB version.
For PM2040 carts with 16 MB Flash chips, use the 16 MB version.
