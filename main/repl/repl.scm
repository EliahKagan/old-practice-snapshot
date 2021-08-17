;; repl.scm - replace strings that match a pattern with a second, fixed string

(use-modules (ice-9 rdelim) (ice-9 regex))

(define (repl pattern substitute input)
  (regexp-substitute/global #f pattern input 'pre substitute 'post))

(define (repl-all pattern substitute)
  (define (repl-one input)
    (display (repl pattern substitute input)) (newline)
    (repl-all pattern substitute))
  (let ((line (read-line))) (if (eof-object? line) (quit) (repl-one line))))

(define argv (command-line))
(define argc (length argv))
(define (arg i) (list-ref argv i))

(define (die msg)
  (format (current-error-port) "~a: error: ~a\n" (arg 0) msg) (quit 1))

(cond ((< argc 3) (die "too few arguments"))
      ((> argc 3) (die "too many arguments"))
      (else (repl-all (arg 1) (arg 2))))
