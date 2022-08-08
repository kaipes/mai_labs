

rule([Human, Wolf, Goat, Cabbage]):- 
	not(((Wolf == Goat), Wolf \= Human)), 
	not(((Goat == Cabbage), Goat \= Human)).

shipping(L, R) :-
	(L == left, R = right);
	(L == right, R = left).

ship([Human, Wolf, Goat, Cabbage], [Human_new, Wolf_new, Goat_new, Cabbage_new]):-
	shipping(Human, Human_new),
	rule([Human_new, Wolf, Goat, Cabbage]),
	Wolf_new = Wolf, 
	Goat_new = Goat, 
	Cabbage_new = Cabbage.


ship([Human, Wolf, Goat, Cabbage], [Human_new, Wolf_new, Goat_new, Cabbage_new]):-
	shipping(Human, Human_new), 
	shipping(Wolf, Wolf_new),
	rule([Human_new, Wolf_new, Goat, Cabbage]),
	Goat_new = Goat, 
	Cabbage_new = Cabbage.

ship([Human, Wolf, Goat, Cabbage], [Human_new, Wolf_new, Goat_new, Cabbage_new]):-
	shipping(Human, Human_new), 
	shipping(Goat, Goat_new),
	rule([Human_new, Wolf, Goat_new, Cabbage]),
	Wolf_new = Wolf, 
	Cabbage_new = Cabbage.

ship([Human, Wolf, Goat, Cabbage], [Human_new, Wolf_new, Goat_new, Cabbage_new]):-
	shipping(Human, Human_new), 
	shipping(Cabbage, Cabbage_new),
	rule([Human_new, Wolf, Goat, Cabbage_new]),
	Wolf_new = Wolf, 
	Goat_new = Goat.


add_obj([Head|Tail],[Y, Head|Tail]):-
	ship(Head, Y), not(member(Y, [Head|Tail])).


invers([]).
invers([Head|Tail]):-
	invers(Tail),
	clarify(Head), nl.

clarify([Human, Wolf, Goat, Cabbage]):-
    write("Human: "), write(Human), 
    write(", Wolf: "), write(Wolf),
    write(", Goat: "), write(Goat),
    write(", Cabbage: "), write(Cabbage).



search_in_width(Begin, Finish):-
	get_time(T),
	width([[Begin]], Finish, Ans), invers(Ans),
	get_time(TT),
	Time is TT - T,
    write('Work time '), write(Time), nl, !.



width([[Finish|T]|_], Finish, [Finish|T]).
width([Next|B], Finish, Ans):-
	findall(X, add_obj(Next, X), T), !,
	append(B, T, Bn),
	width(Bn, Finish, Ans).
width([_|T], Finish, Ans):- 
	width(T, Finish, Ans).


search_iter(Begin, Finish):-
	get_time(T),
	count(Limit),
	deeper([Begin], Finish, Ans, Limit), invers(Ans),
	get_time(TT),
	Time is TT - T,
    write('Work time: '), write(Time), write(" seconds"), nl, !.

count(1).
count(X):-
	count(Y),
	X is Y + 1.

deeper([Finish|T], Finish, [Finish|T], 0).
deeper(List, Finish, ResList, N):-
	N @> 0, add_obj(List, NewList), N1 is N - 1, deeper(NewList, Finish, ResList, N1).

search_in_depth(Begin, Finish):-
	get_time(T),
	depth([Begin], Finish, Ans),
	invers(Ans),
	get_time(TT),
	Time is TT - T,
	write('Work time: '), write(Time), write(" seconds"), nl, !.


depth([Finish|T], Finish, [Finish|T]).
depth(List, Finish, Result):-
    add_obj(List, LList),
    depth(LList, Finish, Result).