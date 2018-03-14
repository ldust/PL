(define (cube-root x)
    (define (square a) (* a a))

    (define (cube a) (* a a a))

    (define (improve guess x)
        (/ (+ (/ x (square guess)) (* 2 guess)) 3)
    )
    (define (average a b) (/ (+ a b) 2))

    (define (good? guess x)
        (< (abs (- (cube guess) x)) 0.0001))
    
    (define (cube-root-itr guess x)
        (if (good? guess x)
            guess
            (cube-root-itr (improve guess x) x)))

    (cube-root-itr 10.0 x))

(cube-root 2333.0)

