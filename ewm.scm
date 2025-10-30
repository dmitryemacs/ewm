(use-modules (ice-9 format))

(define (init)
  (format #t "Initializing EWM\n"))

(define (switch-workspace index)
  (switch-to-workspace index))

(define (move-window window index)
  (move-window-to-workspace window index))
