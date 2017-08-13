(load "wire.scm")
(load "agenda.scm")

;; inverter
(define (inverter input output)
  (define (invert-input)
    (let ((new-value (logical-not (get-signal input))))
      (after-delay inverter-delay
                   (lambda ()
                     (set-signal! output new-value)))))
  (add-action! input invert-input)
  'ok)

(define (logical-not s)
  (cond ((= s 0) 1)
        ((= s 1) 0)
        (else (error "LOGICAL-NOT: Invalid signal" s))))

;; and-gate
(define (and-gate a1 a2 output)
  (define (and-action-procedure)
    (let ((new-value
            (logical-and (get-signal a1) (get-signal a2))))
      (after-delay and-gate-delay
                   (lambda ()
                     (set-signal! output new-value)))))
  (add-action! a1 and-action-procedure)
  (add-action! a2 and-action-procedure)
  'ok)

(define (logical-and a1 a2)
  (cond ((= a1 0) 0)
        ((= a2 0) 0)
        ((and (= a1 1) (= a2 1)) 1)
        (else (error "LOGICAL-AND: Invalid signal" a1 a2))))

;; or-gate
(define (or-gate o1 o2 output)
  (define (or-action-procedure)
    (let ((new-value
            (logical-or (get-signal o1) (get-signal o2))))
      (after-delay or-gate-delay
                   (lambda ()
                     (set-signal! output new-value)))))
  (add-action! o1 or-action-procedure)
  (add-action! o2 or-action-procedure)
  'ok)

(define (logical-or o1 o2)
  (cond ((= o1 1) 1)
        ((= o2 1) 1)
        ((and (= o1 0) (= o2 0)) 1)
        (else (error "LOGICAL-OR: Invalid signal" o1 o2))))
