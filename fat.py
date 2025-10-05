#!/usr/bin/env python3

# Author: zwenergy
# Very simple helper script to create a FAT12.

maxfiles = 3
sizeInBytes = 8192
sectorsPerCluster = 4
bytesPerSector = 512

bytesPerCluster = bytesPerSector * sectorsPerCluster
clusterPerFile = int( sizeInBytes / bytesPerCluster )

def printFAT( startAddr ):
  i = startAddr
  j = 0
  
  while ( j < clusterPerFile ):
    curAddr = startAddr + j
    nextAddr = curAddr + 1
    
    byte0 = curAddr & 0b11111111
    byte1 = ( ( nextAddr & 0b00001111 ) << 4 ) | ( ( curAddr & 0b111100000000 ) >> 8 )
    byte2 = ( nextAddr & 0b111111110000 ) >> 4
  
    if ( j == clusterPerFile - 2 ):
      byte1 = ( ( 0b00001111 ) << 4 ) | ( ( curAddr & 0b111100000000 ) >> 8 )
      byte2 = 255
  
    print( "0x{:02x}".format(byte0) + ", " + "0x{:02x}".format(byte1) + ", " + "0x{:02x}".format(byte2) + "," )
    
    j += 2
    i += 2
    
  print( "" )


printFAT( 3 )


curCnt = 3 + clusterPerFile

for cnt in range(0, maxfiles - 1):
  printFAT( curCnt )
  curCnt += clusterPerFile
  
