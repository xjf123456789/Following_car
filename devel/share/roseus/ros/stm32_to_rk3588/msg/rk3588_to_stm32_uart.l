;; Auto-generated. Do not edit!


(when (boundp 'stm32_to_rk3588::rk3588_to_stm32_uart)
  (if (not (find-package "STM32_TO_RK3588"))
    (make-package "STM32_TO_RK3588"))
  (shadow 'rk3588_to_stm32_uart (find-package "STM32_TO_RK3588")))
(unless (find-package "STM32_TO_RK3588::RK3588_TO_STM32_UART")
  (make-package "STM32_TO_RK3588::RK3588_TO_STM32_UART"))

(in-package "ROS")
;;//! \htmlinclude rk3588_to_stm32_uart.msg.html


(defclass stm32_to_rk3588::rk3588_to_stm32_uart
  :super ros::object
  :slots (_Rk3588_To_Stm32 ))

(defmethod stm32_to_rk3588::rk3588_to_stm32_uart
  (:init
   (&key
    ((:Rk3588_To_Stm32 __Rk3588_To_Stm32) (make-array 20 :initial-element 0 :element-type :char))
    )
   (send-super :init)
   (setq _Rk3588_To_Stm32 __Rk3588_To_Stm32)
   self)
  (:Rk3588_To_Stm32
   (&optional __Rk3588_To_Stm32)
   (if __Rk3588_To_Stm32 (setq _Rk3588_To_Stm32 __Rk3588_To_Stm32)) _Rk3588_To_Stm32)
  (:serialization-length
   ()
   (+
    ;; uint8[20] _Rk3588_To_Stm32
    (* 1    20)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8[20] _Rk3588_To_Stm32
     (princ _Rk3588_To_Stm32 s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8[20] _Rk3588_To_Stm32
   (setq _Rk3588_To_Stm32 (make-array 20 :element-type :char))
   (replace _Rk3588_To_Stm32 buf :start2 ptr-) (incf ptr- 20)
   ;;
   self)
  )

(setf (get stm32_to_rk3588::rk3588_to_stm32_uart :md5sum-) "d26e2a2c893b472f6808d3bff9a6c2b2")
(setf (get stm32_to_rk3588::rk3588_to_stm32_uart :datatype-) "stm32_to_rk3588/rk3588_to_stm32_uart")
(setf (get stm32_to_rk3588::rk3588_to_stm32_uart :definition-)
      "uint8[20] Rk3588_To_Stm32
")



(provide :stm32_to_rk3588/rk3588_to_stm32_uart "d26e2a2c893b472f6808d3bff9a6c2b2")


