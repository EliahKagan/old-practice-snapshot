;; cat1.scm - Very simple cat-like utility. Major limitations:
;; (a) No support for command-line flags other than - and --.
;; (b) Prints a newline at the end of non-blank files even if one wasn't there.
;; (c) Does not detect read errors.

(use-modules (ice-9 rdelim))

(define (cat port) ; this version of the procedure always returns true
  (let ((line (read-line port)))
    (cond ((eof-object? line) #t)
          (else (display line) (newline) (cat port)))))

(define (cat-in) (cat (current-input-port)))

(define (cat-path path) 

(define (cat-all-paths args)
  (cond ((null? args) '())
        (else (cat-path (car args)) (cat-all-paths (cdr args)))))

(define (cat-all args)
  (if (null? args)
    '()
    (let ((this (car args)) (others (cdr args)))
      (define (again) (cat-all others))
      (cond ((string=? this "--") (cat-all-paths others))
            ((string=? this "-") (cat-in) (again))
            ((string=? this "") (again))
            (else (cat-path this) (again))))))


(let ((args (cdr (command-line)))) (if (null? args) (cat-in) (cat-all args)))
