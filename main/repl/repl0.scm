;; repl0.scm - replace one string with another (demo)

(use-modules (ice-9 rdelim) (ice-9 regex))

(define (repl pattern substitute input)
  (regexp-substitute/global #f pattern input 'pre substitute 'post))

(define (repl-all pattern substitute)
  (define (repl-one input)
    (display (repl pattern substitute input)) (newline)
    (repl-all pattern substitute))
  (let ((line (read-line))) (if (eof-object? line) (quit) (repl-one line))))

(repl-all "foo" "bar")
