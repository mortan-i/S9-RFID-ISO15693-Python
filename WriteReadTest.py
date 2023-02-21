import ctypes
from ctypes import *
import sys,os
from nfcReadWriteFunctions import *
import ndef

# Load the DLL and the function
dll = ctypes.WinDLL(os.path.join(sys.path[0],"umf.dll"))
icdev = dll.fw_init(100,115200)
dll.fw_beep(icdev, 1)
dll.fw_config_card(icdev, 0x31) #//set card type

#create storage for the uid of the chip
uid= create_string_buffer(256) 
#init the reader and scan for a ISO15693 card (loops forever until a tag is found)
init_nfc(icdev,uid, dll)
flags = 0x22 #taken from SDK example
startblock = 0 #starting block to write to

#using the nfc lib to generate ndef messages
record = ndef.TextRecord("Hello World!")
octets = b''.join(ndef.message_encoder([record]))
blocknum =len(octets)//4 #number of blocks to write
print("Writing length of " + str(len(octets)))
print("Takes up " + str(len(octets)//4) + "blocks")
write_bytearray(icdev, flags, startblock, blocknum, uid, octets,dll)

#read back the data in the rfid
res = readBytes(icdev,uid,len(octets),0,dll) 
message = list(ndef.message_decoder(res))

for msg in message:
   print("decoded: {}".format(msg))