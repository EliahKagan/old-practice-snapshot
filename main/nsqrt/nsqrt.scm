;; nsqrt.scm - square root by Newton's method, based directly on SICP sec 1.1.7

(define (nsqrt x)
  (define epsilon .001)
  (define (done? r) (< (abs (- (* r r) x)) epsilon))
  (define (iter r) (/ (+ r (/ x r)) 2))
  (define (method r) (if (done? r) r (method (iter r))))
  (method 1.))

(display (nsqrt 2)) (newline)
