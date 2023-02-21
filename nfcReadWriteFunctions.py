import  ctypes
from ctypes import *
import time
from binascii import hexlify, unhexlify
import os,sys

def init_dll(path_):
    # Load the DLL and the function
    #dll = ctypes.WinDLL(os.path.join(sys.path[0],"umf.dll"))    
    dll = path_
    icdev = dll.fw_init(100,115200)
    dll.fw_beep(icdev, 1)
    dll.fw_config_card(icdev, 0x31) #//set card type
    return icdev,dll

def init_nfc(icdev, uid, dll):    
    length = create_string_buffer(8)
    while(1):
        st = dll.fw_inventory(icdev, 0x36, 0, 0, length, uid);       #find single card
        if st != 0 :
            print("nothing found")
            time.sleep(0.5)
        else:
            print("Found a card!")        
            serialNoLen = length.value
            print("SN Len:" + str(int.from_bytes(serialNoLen,byteorder='little')))            
            print( "SN: " + str(int.from_bytes( uid.value,byteorder='little')))
            break

    st = dll.fw_select_uid(icdev, 0x22, uid) #we got chip, select it
    if st != 0 :
            print("Error selecting!")

    st = dll.fw_reset_to_ready(icdev, 0x22, uid);    
    if st != 0 :
            print("Error resetting!")
    secInfo= create_string_buffer(256)
    secInfoLen=create_string_buffer(8)
    st = dll.fw_get_securityinfo(icdev, 0x22, 0x04, 0x02, uid, secInfoLen, secInfo)
    if st != 0 :
            print("Error reading security info!")    


def fw_writeblock(icdev, flags, startblock, blocknum, UID, wlen, rbuffer_data,dll):                
    write_func = dll.fw_writeblock
    write_func.argtypes = [ctypes.c_int, #int
                           ctypes.c_ubyte, #unsigned char
                           ctypes.c_ubyte, #unsigned char
                           ctypes.c_ubyte, #unsigned char
                           ctypes.POINTER(ctypes.c_ubyte), #unsigned char*
                           ctypes.c_ubyte, #unsigned char
                           ctypes.POINTER(ctypes.c_ubyte)]#unsigned char*
    
    write_func.restype = ctypes.c_short
    flags = ctypes.c_ubyte(flags)
    startblock = ctypes.c_ubyte(startblock)
    blocknum = ctypes.c_ubyte(blocknum)
    UID_ptr = ctypes.cast(UID, ctypes.POINTER(ctypes.c_ubyte))
    wlen = ctypes.c_ubyte(wlen)    
    rbuffer = (ctypes.c_ubyte * len(rbuffer_data))(*rbuffer_data)
    # Call the function
    result = write_func(icdev, flags, startblock, blocknum, UID_ptr, wlen, rbuffer)
    return result

def write_bytearray(icdev, flags, startblock, blocknum, UID, byte_array_, dll):
    # Break the bytearray into blocks of 4 bytes each
    blocks = [byte_array_[i:i+4] for i in range(0, len(byte_array_), 4)]
    # Write each block individually
    for i, block in enumerate(blocks):
        wlen = len(block)
        rbuffer = bytearray(block) + bytearray([0] * (4 - wlen))
        #print(hexlify(rbuffer)) #this prints out each block before writing
        result = fw_writeblock(icdev, flags, startblock + i, 1, UID, wlen, rbuffer, dll)
        if result != 0:
            raise Exception("Error writing block")
        
def readBytes(dev, uid, no_bytes, startAddr,dll):
    buffer = []
    hexbuffer =[]
    bytesLeftToRead = no_bytes
    blocksToRead = no_bytes//4
    remainder = no_bytes%4
    if remainder:
        blocksToRead=blocksToRead+1
    bytesreadTotal=0
    for n in range(blocksToRead):    
        dataLen= create_string_buffer(4)
        databuffer= create_string_buffer(4)
        res = dll.fw_readblock(dev, 0x22, startAddr+n, 1, uid, dataLen, databuffer)  #only seems to work with 1
        if res > 0:
            print("Error Reading!")
        hexstr= hexlify(databuffer.raw).decode()
        hexbuffer.append(hexstr) #reads each block as one hex string
        buffer.extend(databuffer.value)        
        bytesread =  int.from_bytes(dataLen.value,byteorder='little')
        bytesreadTotal+=bytesread
        bytesLeftToRead = bytesLeftToRead-bytesread
        #print ("Read " + str( bytesread) + " bytes, " + str(bytesLeftToRead) + " left")
        #print(hexlify(databuffer.raw).decode())        

    print("finished reading " + str(bytesreadTotal))
    # Convert each hex value to bytes
    bytes_arrays = [bytes.fromhex(h) for h in hexbuffer]    
    # Concatenate the arrays of bytes into a single array
    bytes_array = b''.join(bytes_arrays)    
    # Try to convert the bytes to an ASCII string
    try:
        ascii_string = bytes_array.decode("ascii")
    except UnicodeDecodeError:
    # If the bytes contain characters outside the ASCII range, replace them with '?'
        ascii_string = bytes_array.decode("ascii", "replace")    
    #print (buffer)
    #print(ascii_string) #print out the data decoded as ascii
    return bytes_array[:no_bytes]
    #return bytes(buffer[:no_bytes])        