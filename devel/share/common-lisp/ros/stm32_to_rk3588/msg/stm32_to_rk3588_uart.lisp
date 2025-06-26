; Auto-generated. Do not edit!


(cl:in-package stm32_to_rk3588-msg)


;//! \htmlinclude stm32_to_rk3588_uart.msg.html

(cl:defclass <stm32_to_rk3588_uart> (roslisp-msg-protocol:ros-message)
  ((Rk3588_To_Stm32
    :reader Rk3588_To_Stm32
    :initarg :Rk3588_To_Stm32
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 20 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass stm32_to_rk3588_uart (<stm32_to_rk3588_uart>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <stm32_to_rk3588_uart>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'stm32_to_rk3588_uart)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name stm32_to_rk3588-msg:<stm32_to_rk3588_uart> is deprecated: use stm32_to_rk3588-msg:stm32_to_rk3588_uart instead.")))

(cl:ensure-generic-function 'Rk3588_To_Stm32-val :lambda-list '(m))
(cl:defmethod Rk3588_To_Stm32-val ((m <stm32_to_rk3588_uart>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader stm32_to_rk3588-msg:Rk3588_To_Stm32-val is deprecated.  Use stm32_to_rk3588-msg:Rk3588_To_Stm32 instead.")
  (Rk3588_To_Stm32 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <stm32_to_rk3588_uart>) ostream)
  "Serializes a message object of type '<stm32_to_rk3588_uart>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:write-byte (cl:ldb (cl:byte 8 0) ele) ostream))
   (cl:slot-value msg 'Rk3588_To_Stm32))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <stm32_to_rk3588_uart>) istream)
  "Deserializes a message object of type '<stm32_to_rk3588_uart>"
  (cl:setf (cl:slot-value msg 'Rk3588_To_Stm32) (cl:make-array 20))
  (cl:let ((vals (cl:slot-value msg 'Rk3588_To_Stm32)))
    (cl:dotimes (i 20)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:aref vals i)) (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<stm32_to_rk3588_uart>)))
  "Returns string type for a message object of type '<stm32_to_rk3588_uart>"
  "stm32_to_rk3588/stm32_to_rk3588_uart")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'stm32_to_rk3588_uart)))
  "Returns string type for a message object of type 'stm32_to_rk3588_uart"
  "stm32_to_rk3588/stm32_to_rk3588_uart")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<stm32_to_rk3588_uart>)))
  "Returns md5sum for a message object of type '<stm32_to_rk3588_uart>"
  "d26e2a2c893b472f6808d3bff9a6c2b2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'stm32_to_rk3588_uart)))
  "Returns md5sum for a message object of type 'stm32_to_rk3588_uart"
  "d26e2a2c893b472f6808d3bff9a6c2b2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<stm32_to_rk3588_uart>)))
  "Returns full string definition for message of type '<stm32_to_rk3588_uart>"
  (cl:format cl:nil "uint8[20] Rk3588_To_Stm32~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'stm32_to_rk3588_uart)))
  "Returns full string definition for message of type 'stm32_to_rk3588_uart"
  (cl:format cl:nil "uint8[20] Rk3588_To_Stm32~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <stm32_to_rk3588_uart>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'Rk3588_To_Stm32) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 1)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <stm32_to_rk3588_uart>))
  "Converts a ROS message object to a list"
  (cl:list 'stm32_to_rk3588_uart
    (cl:cons ':Rk3588_To_Stm32 (Rk3588_To_Stm32 msg))
))
