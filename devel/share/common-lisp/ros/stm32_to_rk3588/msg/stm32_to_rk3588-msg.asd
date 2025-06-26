
(cl:in-package :asdf)

(defsystem "stm32_to_rk3588-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "stm32_to_rk3588_uart" :depends-on ("_package_stm32_to_rk3588_uart"))
    (:file "_package_stm32_to_rk3588_uart" :depends-on ("_package"))
  ))