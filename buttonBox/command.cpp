/****************************************Copyright(c)*****************************************************
**                            Shenzhen Yuejiang Technology Co., LTD.
**
**                                 http://www.dobot.cc
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.cpp
** Latest modified Date:2016-10-24
** Latest Version:      V2.0.0
** Descriptions:        main body
**
**--------------------------------------------------------------------------------------------------------
** Created by:          liyi
** Created date:        2016-10-24
** Version:             V1.0.0
** Descriptions:        Command API
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "command.h"
#include "Protocol.h"
#include "ProtocolID.h"

/*********************************************************************************************************
** Function name:       SetEndEffectorParams
** Descriptions:        Set end effector parameters
** Input parameters:    endEffectorParams, isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorParams(EndEffectorParams *endEffectorParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(EndEffectorParams);
    memcpy(tempMessage.params, (uint8_t *)endEffectorParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetEndEffectorLaser
** Descriptions:        Set the laser output
** Input parameters:    on,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorLaser(bool on, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorLaser;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = on;

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       GetPose
** Descriptions:        Get Robot Pose
** Input parameters:    Pose structure
** Output parameters:   none
** Returned value:      true
*********************************************************************************************************/
int GetPoseCmd(Pose *pose, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolGetPose;
    tempMessage.rw = false;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 0;
    
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    // Wait for the response message
    while (RingBufferGetCount(&gSerialProtocolHandler.rxPacketQueue) == 0);

    // Read the response message
    Message response;
    MessageRead(&gSerialProtocolHandler, &response);

    // Check if the response is valid
    if (response.id != ProtocolGetPose) {
        return -1;
    }

    // Copy the pose data from the response message
    memcpy(&pose->x, &response.params[0], sizeof(float));
    memcpy(&pose->y, &response.params[1], sizeof(float));
    memcpy(&pose->z, &response.params[2], sizeof(float));
    memcpy(&pose->r, &response.params[3], sizeof(float));
    memcpy(&pose->jointAngle, &response.params[4], sizeof(float) * 4);

    // Save the queued command index if requested
    //if (queuedCmdIndex != NULL) {
     //   *queuedCmdIndex = response.index;
    //}

    return 0;
}
/*********************************************************************************************************
** Function name:       SetEndEffectorSuctionCup
** Descriptions:        Set the suctioncup output
** Input parameters:    suck,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorSuctionCup(bool suck, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorSuctionCup;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = suck;
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

//ak
int _set_end_effector_suction_cup(bool enable)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorSuctionCup;
    tempMessage.rw = 0x03;
    tempMessage.paramsLen = 2;
    
    tempMessage.params[0] = 0x01; // First parameter is always 0x01
    
    if (enable)
        tempMessage.params[1] = 0x01; // Enable suction cup
    else
        tempMessage.params[1] = 0x00; // Disable suction cup
    
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

//ak
int clear()
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolFunctionALARMBase;
    tempMessage.rw = true;
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}


int SetHomeCmd(bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolHOMECmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 0;
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}



/*********************************************************************************************************
** Function name:       SetEndEffectorGripper
** Descriptions:        Set the gripper output
** Input parameters:    grip,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetEndEffectorGripper(bool grip, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolEndEffectorGripper;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = 1;
    tempMessage.params[0] = grip;
    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGJointParams
** Descriptions:        Sets the joint jog parameter
** Input parameters:    jogJointParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGJointParams(JOGJointParams *jogJointParams, bool isQueued, uint64_t *queuedCmdIndex)
{
  
    Message tempMessage;
    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGJointParams);
    memcpy(tempMessage.params, (uint8_t *)jogJointParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCoordinateParams
** Descriptions:        Sets the axis jog parameter
** Input parameters:    jogCoordinateParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCoordinateParams(JOGCoordinateParams *jogCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)jogCoordinateParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCommonParams
** Descriptions:        Sets the jog common parameter
** Input parameters:    jogCommonParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCommonParams(JOGCommonParams *jogCommonParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCommonParams);
    memcpy(tempMessage.params, (uint8_t *)jogCommonParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetJOGCmd
** Descriptions:        Execute the jog function
** Input parameters:    jogCmd,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetJOGCmd(JOGCmd *jogCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolJOGCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(JOGCmd);
    memcpy(tempMessage.params, (uint8_t *)jogCmd, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJointParams
** Descriptions:        Sets the articulation point parameter
** Input parameters:    ptpJointParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPJointParams(PTPJointParams *ptpJointParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJointParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJointParams);
    memcpy(tempMessage.params, (uint8_t *)ptpJointParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCoordinateParams
** Descriptions:        Sets the coordinate position parameter
** Input parameters:    ptpCoordinateParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCoordinateParams(PTPCoordinateParams *ptpCoordinateParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCoordinateParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCoordinateParams);
    memcpy(tempMessage.params, (uint8_t *)ptpCoordinateParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPJumpParams
** Descriptions:        Set the gate type parameter
** Input parameters:    ptpJumpParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPJumpParams(PTPJumpParams *ptpJumpParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPJumpParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPJumpParams);
    memcpy(tempMessage.params, (uint8_t *)ptpJumpParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCommonParams
** Descriptions:        Set point common parameters
** Input parameters:    ptpCommonParams,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCommonParams(PTPCommonParams *ptpCommonParams, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCommonParams;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCommonParams);
    memcpy(tempMessage.params, (uint8_t *)ptpCommonParams, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}

/*********************************************************************************************************
** Function name:       SetPTPCmd
** Descriptions:        Execute the position function
** Input parameters:    ptpCmd,isQueued
** Output parameters:   queuedCmdIndex
** Returned value:      true
*********************************************************************************************************/
int SetPTPCmd(PTPCmd *ptpCmd, bool isQueued, uint64_t *queuedCmdIndex)
{
    Message tempMessage;

    memset(&tempMessage, 0, sizeof(Message));
    tempMessage.id = ProtocolPTPCmd;
    tempMessage.rw = true;
    tempMessage.isQueued = isQueued;
    tempMessage.paramsLen = sizeof(PTPCmd);
    memcpy(tempMessage.params, (uint8_t *)ptpCmd, tempMessage.paramsLen);

    MessageWrite(&gSerialProtocolHandler, &tempMessage);

    return true;
}



