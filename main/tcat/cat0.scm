;; cat0.scm - very, very simple cat-like utility, only reads from stdin

(use-modules (ice-9 rdelim))

(define (cat)
  (define (cat-line str) (display str) (newline) (cat))
  (let ((line (read-line))) (if (eof-object? line) (quit) (cat-line line))))

(cat)
