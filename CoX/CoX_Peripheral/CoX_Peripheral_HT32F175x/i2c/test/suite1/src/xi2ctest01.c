//*****************************************************************************
//
//! @page xi2c_testcase xcore register test
//!
//! File: @ref xi2c.c
//!
//! <h2>Description</h2>
//! This module implements the test sequence for the xsysctl sub component.<br><br>
//! - \p Board: HT32F175x <br><br>
//! - \p Last-Time(about): 0.5s <br><br>
//! - \p Phenomenon: Success or failure information will be printed on the UART. <br><br>
//! .
//!
//! <h2>Preconditions</h2>
//! The module requires the following options:<br><br>
//! - \p Option-define:
//! <br>(1)None.<br><br>
//! - \p Option-hardware:
//! <br>(1)Connect an USB cable to the development board.<br><br>
//! - \p Option-OtherModule:
//! <br>Connect an COM cable to the development board.<br>
//! .
//! In case some of the required options are not enabled then some or all tests
//! may be skipped or result FAILED.<br>
//!
//! <h2>Test Cases</h2>
//! The module contain those sub tests:<br><br>
//! - \subpage test_xi2c_register
//! .
//! \file xi2c.c
//! \brief xi2c test source file
//! \brief xi2c test header file <br>
//
//*****************************************************************************

#include "test.h"
//*****************************************************************************
//
//!\page test_xsysctl_register test_xi2c_register
//!
//!<h2>Description</h2>
//!Test xi2c register. <br>
//!
//
//*****************************************************************************

unsigned long ulSlave = I2C0_BASE;
unsigned char ucTempData[5];
unsigned char ucTemp[5];
unsigned char ucTempCount = 0;
unsigned char ucTempCount1 = 0;

//*****************************************************************************
//
//! \breif i2c slave interrupt install function
//! 
//! \return none
//
//*****************************************************************************
unsigned long I2CSlaveCallback(void *pvCBData, 
                               unsigned long ulEvent,
                               unsigned long ulMsgParam,
                               void *pvMsgData)
{
    if(ulMsgParam == xI2C_SLAVE_EVENT_RREQ)
    {
        ucTempData[ucTempCount] = I2CDataGet(ulSlave);
        ucTempCount++;
    }
    else if (ulMsgParam == xI2C_SLAVE_EVENT_TREQ)
    {
        I2CDataPut(ulSlave, ucTempData[ucTempCount1]);
        ucTempCount1++;
        if(ucTempCount1 == 4)
        {
            I2CIntDisable(ulSlave, 0);
        }
    }
    return 0;
}

//*****************************************************************************
//
//! \brief Get the Test description of xi2c002 register test.
//!
//! \return the desccription of the xcore001 test.
//
//*****************************************************************************
static char* xI2C001GetTest(void)
{
    return "xI2C, 001, I2C test";
}

//*****************************************************************************
//
//! \brief something should do before the test execute of xi2c002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Setup(void)
{    
    xSysCtlPeripheralEnable2(ulSlave);
    
    xSysCtlPeripheralEnable2(xGPIO_PORTD_BASE);
    xSysCtlPeripheralEnable(SYSCTL_PERIPH_AFIO);
    
    xSPinTypeI2C(I2C0SCK, PD12);
    xSPinTypeI2C(I2C0SDA, PD13);
    
    I2CSlaveInit(ulSlave, I2C_ADDR_7BIT, 0x12, I2C_GENERAL_CALL_DIS);
    I2CEnable(ulSlave);
    I2CIntEnable(ulSlave, I2C_INT_ALL);
    xIntEnable(xSysCtlPeripheralIntNumGet(ulSlave));
    I2CIntCallbackInit(ulSlave, I2CSlaveCallback);
    
    /*I2CMasterInit(ulMaster, SysCtlClockGet());
    I2CEnable(ulMaster);
    I2CMasterWriteS1(ulMaster, 0x12, 'a', xfalse);
    I2CMasterWriteS2(ulMaster, 'b', xfalse);
    I2CMasterWriteS2(ulMaster, 'c', xfalse);
    I2CMasterWriteS2(ulMaster, 'd', xfalse);
    I2CMasterReadS1(ulMaster, 0x12, ucTemp, xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[1], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[2], xfalse);
    I2CMasterReadS2(ulMaster, &ucTemp[3], xtrue);*/
}


//*****************************************************************************
//
//! \brief something should do after the test execute of xsysctl002 test.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001TearDown(void)
{   

}



//*****************************************************************************
//
//! \brief xi2c 002 test execute main body.
//!
//! \return None.
//
//*****************************************************************************
static void xI2C001Execute(void)
{
 
}

//
// xi2c register test case struct.
//
const tTestCase sTestXi2c001Register = {
		xI2C001GetTest,
		xI2C001Setup,
		xI2C001TearDown,
		xI2C001Execute
};

//
// Xi2c test suits.
//
const tTestCase * const psPatternXi2c01[] =
{
    &sTestXi2c001Register,
    0
};