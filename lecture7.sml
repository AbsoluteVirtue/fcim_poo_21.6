fun pow (x: int, y: int) = 
    if y = 0
    then 1
    else x * pow(x, y - 1);

fun pow2 (x, y) = 
    if y = 0
    then 1
    else x * pow(x, y - 1);
    
fun length(a : int list) = 
    if null a
    then 0
    else 1 + length(tl a);

fun sum_list xs =
    case xs of
        [] => 0
      | x::xs' => x + sum_list xs';

fun append (xs,ys) =
    case xs of
        [] => ys
      | x::xs' => x :: append(xs',ys);

fun sum_triple1 (x, y, z) =
    x + y + z;

fun sum_triple2 (triple : int*int*int) =
	   #1 triple + #2 triple + #3 triple;

fun partial_sum (x, y, z) = 
    x + z;

fun append (xs,ys) =
   case xs of
       [] => ys
     | x::xs' => x :: append(xs',ys);

fun same_thing(x,y) = if x=y then "yes" else "no" ;

fun is_three x = if x=3 then "yes" else "no";

(* our n_times function is polymorphic, which lets us use it for numbers, lists,
   or anything else provided f and x "agree"
     - return and argument type of f must be the same here because and only
       because result is passed back to f *)
fun n_times (f,n,x) = 
    if n=0
    then x
    else f (n_times(f,n-1,x));
