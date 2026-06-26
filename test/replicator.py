import sys
sys.path.append("..")
from SIMDTierra import *

a=Assembler(0)
a.assembleLines("""
Copy1 R0 PC - decr                        #load start
Copy1 loadAddr PC -                       
Copy1 R0 R0 R0                            # template search pattern
Copy1 loadAddr loadAddr - load incr       # load search pattern to data
Copy1 R2 data -                           # end of search pattern
Copy1 R1 PC -                             # find loop
Copy1 loadAddr loadAddr - load incr       # data=soup[loadAddr]
Eq    test R2 data jmpz                   # if not equal, goto find loop
Copy1 PC R1 -                             # goto find loop
Copy1 R2 loadAddr -                       # R2 = end
Copy1 loadAddr R0 -                       # loadAddr = start
Copy1 R1 PC -                             # copy loop
Copy1 loadAddr loadAddr - load incr       # data=soup[loadAddr]
Copy1 storeAddr storeAddr - store incr   # soup[storeAddr]=data
Xor test loadAddr R2 jmpz                       # if PC==R2, goto end
Copy1 PC R1 R1                            # goto copy loop
""")
# add in complement of template pattern
a.soup[a.current()]=instruction("Not1", ~reg("R0"), ~reg("R0"), ~reg("R0"), "jmpz", "full")

assert(a.soup[a.current()]==4294882723)

cpu=CPU()
cpu.registers[reg("PC")]=0
cpu.registers[reg("storeAddr")]=20

for i in range(500):
    if cpu.registers[reg("PC")]>16: break
    cpu.execute()

for i in range(17):
    #print(i,a.soup[i],a.soup[i+20])
    assert(a.soup[i]==a.soup[i+20])
