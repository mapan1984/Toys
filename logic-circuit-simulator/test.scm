(load "adder.scm")

;; 给线路增加监视
(define (probe name wire)
  (add-action! wire
               (lambda ()
                 (newline)
                 (display "{[name: ")
                 (display name)
                 (display "] [current-time: ")
                 (display (current-time the-agenda))
                 (display "] [new-value = ")
                 (display (get-signal wire))
                 (display "]}")
                 (newline))))

;; 时间-事务 表
(define the-agenda (make-agenda))

;; 逻辑门延时
(define inverter-delay 2)
(define and-gate-delay 3)
(define or-gate-delay 5)

;;; 定义需要的wire
;(define input-1 (make-wire))
;(define input-2 (make-wire))
;(define sum (make-wire))
;(define carry (make-wire))
;
;;; 为sum，carry添加监视
;(probe 'sum sum)
;(probe 'carry carry)
;
;;; 构造半加器
;(half-adder input-1 input-2 sum carry)

(define in (make-wire))
(define out (make-wire))
(probe 'in in)
(probe 'out out)
(inverter in out)
