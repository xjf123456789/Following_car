// Auto-generated. Do not edit!

// (in-package stm32_to_rk3588.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class rk3588_to_stm32_uart {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Rk3588_To_Stm32 = null;
    }
    else {
      if (initObj.hasOwnProperty('Rk3588_To_Stm32')) {
        this.Rk3588_To_Stm32 = initObj.Rk3588_To_Stm32
      }
      else {
        this.Rk3588_To_Stm32 = new Array(20).fill(0);
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type rk3588_to_stm32_uart
    // Check that the constant length array field [Rk3588_To_Stm32] has the right length
    if (obj.Rk3588_To_Stm32.length !== 20) {
      throw new Error('Unable to serialize array field Rk3588_To_Stm32 - length must be 20')
    }
    // Serialize message field [Rk3588_To_Stm32]
    bufferOffset = _arraySerializer.uint8(obj.Rk3588_To_Stm32, buffer, bufferOffset, 20);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type rk3588_to_stm32_uart
    let len;
    let data = new rk3588_to_stm32_uart(null);
    // Deserialize message field [Rk3588_To_Stm32]
    data.Rk3588_To_Stm32 = _arrayDeserializer.uint8(buffer, bufferOffset, 20)
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'stm32_to_rk3588/rk3588_to_stm32_uart';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd26e2a2c893b472f6808d3bff9a6c2b2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    uint8[20] Rk3588_To_Stm32
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new rk3588_to_stm32_uart(null);
    if (msg.Rk3588_To_Stm32 !== undefined) {
      resolved.Rk3588_To_Stm32 = msg.Rk3588_To_Stm32;
    }
    else {
      resolved.Rk3588_To_Stm32 = new Array(20).fill(0)
    }

    return resolved;
    }
};

module.exports = rk3588_to_stm32_uart;
