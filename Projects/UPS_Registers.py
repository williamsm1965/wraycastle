#!/usr/bin/env python2
#
import smbus
import os
import time
import sys
import struct

def i2cCom (cmd):
        f=os.popen(cmd)
        s=f.read()
        f.close()
        return s

def AlertReset ():
        #Execute a power on reset
        AlertMask =int('11011111',2)
        cmd="sudo i2cget -y 1 0x36 0x0c w"
        s=i2cCom(cmd)
        ConfigMSB= '0x' + s[2] +s[3]
        # converted hex string to integer which also removed EOL from stdout above
        dec=int(ConfigMSB,16)
        AlertBin=bin((dec & AlertMask))
        AlertHex =hex(int(AlertBin,2))
        AlertSTR = str(AlertHex)
        if len(AlertSTR)<4:
                NewAlertSTR='0x0' + AlertSTR[2] + s[4] + s[5]
        else:
                NewAlertSTR='0x' + AlertSTR[2] + AlertSTR[3] + s[4] + s[5]
        cmd="sudo i2cset -y 1 0x36 0x0c " + NewAlertSTR + " w"
        print "New Alert Hex Value  " + NewAlertSTR + '\n'
        s=i2cCom(cmd)

def valrtReg():
        #Check Alert and ALSC flags in Config Register MSB
        cmd="i2cget -f -y 1 0x36 0x14 w"
        #used to popen to redirect stdout from cmdto a variable
        s=i2cCom(cmd)
        ConfigMSB= '0x' + s[2] +s[3]
        ConfigLSB= '0x' + s[4] +s[5]
        valrtMax=int(ConfigMSB,16) *20
        valrtMin=int(ConfigLSB,16)*20
        return valrtMin, valrtMax

def modeReg():
        #Check Alert and ALSC flags in Config Register MSB
        cmd="i2cget -f -y 1 0x36 0x06 w"
        #used to popen to redirect stdout from cmdto a variable
        s=i2cCom(cmd)
        ConfigMSB= '0x' + s[2] +s[3]
        dec=int(ConfigMSB,16)
        qkStmask =int('01000000',2)
        qsBin=bin((dec & qkStmask)>> 6)
        enSlmask =int('00100000',2)
        ensBin=bin((dec & enSlmask)>> 5)
        hibStatmask =int('00010000',2)
        hsBin=bin((dec & hibStatmask)>> 5)
        return qsBin, ensBin, hsBin

def configReg():
        #Check Alert and ALSC flags in Config Register MSB
        cmd="i2cget -f -y 1 0x36 0x0c w"
        #used to popen to redirect stdout from cmdto a variable
        s=i2cCom(cmd)
        ConfigMSB= '0x' + s[2] +s[3]
        # converted hex string to integer which also removed EOL from stdout above
        dec=int(ConfigMSB,16)
        #mask looking at ALERT bit in CONFig Register
        sleepMask =int('10000000',2)
        alertMask =int('00100000',2)
        alscMask =int('01000000',2)
        athdMask = int ('00011111',2)
        #for Sleep Flag shift result of AND with mask to right 7 times
        sleepBin=bin((dec & sleepMask)>> 7)
        #for ALSC shift result of AND with mask to right 6 times
        alscBin=bin((dec & alscMask)>> 6)
        #for Alert Flag shift result of AND with mask to right 5 times
        alertBin=bin((dec & alertMask)>> 5)
        athd=bin((dec & athdMask))
        AlertPercent = 32 - int(athd,2)
        return dec, sleepBin, alscBin, alertBin, AlertPercent

def statusReg():
        cmd="i2cget -f -y 1 0x36 0x1a w"
        #used to popen to redirect stdout from cmdto a variable
        s=i2cCom(cmd)
        statusMSB= '0x' + s[4] +s[5]
        # converted hex string to integer which also removed EOL from stdout above
        dec=int(statusMSB,16)
        #mask looking at Reset Indicator bit bit in CONFig Register
        #xxBin=bin((dec & XXmask)>> 6)
        ENVmask =int('01000000',2)
        envBin=bin((dec & ENVmask)>> 6)
        SCmask =int('00100000',2)
        scBin=bin((dec & SCmask)>> 5)
        HDmask =int('00010000',2)
        hdBin=bin((dec & HDmask)>> 4)
        VRmask =int('00001000',2)
        vrBin=bin((dec & VRmask)>> 3)
        VLmask =int('00000100',2)
        vlBin=bin((dec & VLmask)>> 2)
        VHmask =int('00000010',2)
        vhBin=bin((dec & VHmask)>> 1)
        RImask =int('00000001',2)
        #for RI shift result of AND with mask  0 to the right
        riBin=bin((dec & RImask))
        return dec, envBin, scBin, hdBin, vrBin, vlBin, vhBin, riBin

valrtMin, valrtMax = valrtReg()
qsBin, ensBin, hsBin = modeReg()
dec, sleepBin, alscBin, alertBin, AlertPercent=configReg()
ridec,envBin, scBin, hdBin, vrBin, vlBin, vhBin, riBin = statusReg()

#AlertReset()
#print "Alert Flag reset executed!" +'\n'

print (time.strftime ("%H:%M:%S")) + "    " + (time.strftime("%d/%m/%Y")) +'\n'

print "Mode Register Info: " +'\n'
print "Quick Start Flag = " + str (qsBin[2]) + "." +'\n'
print "Enable Sleep Flag = " + str (ensBin[2]) + "." +'\n'
print "Hibernation Status (RO) Flag = " + str (hsBin[2]) + "." +'\n' +'\n'

print "Voltage Alert Register Info: " +'\n'
print "Voltage Alert Minimum = " + str (valrtMin) + " mV." +'\n'
print "Voltage Alert Maximum = " + str (valrtMax) + " mV." +'\n' +'\n'

print "Status Register Info: " +'\n'
print "Enable Voltage Reset Alert (EnVR) Flag = " + str (envBin[2]) + "." +'\n'
print "SOC change by at least 1% Flag = " + str (scBin[2]) + "." +'\n'
print "SOC low (below ATHD threshold) Flag = " + str (hdBin[2]) + "." +'\n'
print "Voltage Reset (If EnVR is Set) Flag = " + str (vrBin[2]) + "." +'\n'
print "Voltage Low (VCELL below VALRTMIN)  Flag = " + str (vlBin[2]) + "." +'\n'
print "Voltage High (VCELL above VALRTMAX) Flag = " + str (vhBin[2]) + "." +'\n'
print "Reset Indicator Flag = " + str (riBin[2]) + "." +'\n' +'\n'



print "Config Register Info: " +'\n'
print "Force Sleep Bit = " + str (sleepBin[2]) + "." +'\n'
print "Alert Status Flag = " + str (alertBin[2]) + "." +'\n'
print "SOC Change Alert (ALSC) Flag = " + str (alscBin[2]) + "." +'\n'
print "Empty Alert Threshold (ATHD) Percentage = " + str(AlertPercent) + "%" + '\n' +'\n'
