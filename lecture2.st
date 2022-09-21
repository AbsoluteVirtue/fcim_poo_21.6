"== https://github.com/gnu-smalltalk/smalltalk/ =="

to fact n (^if : n = 0 then 1 else n * fact n - 1)
(... @! >> (^ : n = 0 >> (1) (n - 1)!)

to True | truthValue |
(
    @ifTrue => (trueBlock (ifFalse (falseBlock (^trueBlock value))))!
    @ifFalse => (falseBlock (ifTrue (trueBlock (^trueBlock value))))!
    @ifTrue => (trueBlock (^trueBlock value))!
    @ifFalse => (falseBlock (^nil))!
    @not => (^false)!
    @& :aBoolean => (^aBoolean)!
    @| :aBoolean => (^true)!
    @eqv :aBoolean => (^aBoolean)!
    @xor :aBoolean => (^aBoolean not)!
    @and :aBlock => (^aBlock value)!
    @or :aBlock => (^true)!
    @printOn :aStream => (aStream nextPutAll :'true')!
)!
