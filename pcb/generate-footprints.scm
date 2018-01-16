(use-modules (ice-9 optargs)
             (ice-9 format))

(define* (element #:key
           (sflags "")
           (description "")
           (name "")
           (value "")
           (mark-x 0)
           (mark-y 0)
           (text-x 0)
           (text-y 0)
           (text-direction 0)
           (text-scale 100)
           (tsflags "")
           (pads '()))
  (format #f  "Element[~s ~s ~s ~s ~amm ~amm ~amm ~amm ~a ~a ~s]\n(\n~{~a~})"
          sflags description name value mark-x mark-y
          text-x text-y text-direction text-scale tsflags
          pads))

(define* (pad #:key rx1 ry1 rx2 ry2 thickness clearance mask name number sflags)
  (format #f  "  Pad[~amm ~amm ~amm ~amm ~amm ~amm ~amm ~s ~s ~s]\n"
          (exact->inexact rx1)
          (exact->inexact ry1)
          (exact->inexact rx2)
          (exact->inexact ry2) thickness clearance mask name number sflags))

(define (make-dual-row-connector pins-per-row)
  "Generate a footprint for a 2mm pitch surface mount pin header with
two rows of PINS-PER-ROW pins."
  (define thickness 1)
  (define pitch 2)
  (define height 2.6)
  (define drawn-height (- height thickness))
  (define x-start (/ thickness 2))
  (define upper-y-start (+ (/ 1.5 2) (/ thickness 2)))
  (define lower-y-start (- 0 upper-y-start))
  (let loop ((x x-start)
             (pins (- pins-per-row 1))
             (pads '()))
    (let* ((counter (- pins-per-row pins))
           (upper (pad #:rx1 x
                       #:ry1 upper-y-start
                       #:rx2 x
                       #:ry2 (+ upper-y-start drawn-height)
                       #:thickness thickness
                       #:clearance 0
                       #:mask 0
                       #:name (number->string counter)
                       #:number (number->string counter)
                       #:sflags "square"))
           (lower (pad #:rx1 x
                       #:ry1 lower-y-start
                       #:rx2 x
                       #:ry2 (- lower-y-start drawn-height)
                       #:thickness thickness
                       #:clearance 0
                       #:mask 0
                       #:name (number->string (+ counter pins-per-row))
                       #:number (number->string (+ counter pins-per-row))
                       #:sflags "square")))
      (if (zero? pins)
          (element #:description "Amphenol FCI Minitek SMD pin header"
                   #:text-y 25000
                   #:pads (cons upper (cons lower pads)))
          (loop (+ x pitch)
                (- pins 1)
                (cons upper (cons lower pads)))))))
