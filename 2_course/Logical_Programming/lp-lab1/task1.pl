% Первая часть задания - предикаты работы со списками

% Ниже - пример кода, который вы можете удалить.

length([],0).
length([_|Y],N):-length(Y,N1), N is N1+1.

%?-length([a,b,c,d],N),write(N).

member(A,[A|_]).
member(A,[_|Z]):-member(A,Z).

%?-member(X,[a,b,c]),write(X).

append([],X,X).
append([A|X],Y,[A|Z]):-append(X,Y,Z).

%?-append([1,2,3],T,[1,2,3,4,5,6]),write(T).

remove(X,[X|T],T).
remove(X,[Y|T],[Y|T1]):-remove(X,T,T1).

%?-remove(b,[r,b,c],R),write(R).

permute([],[]).
permute(L,[X|T]):-remove(X,L,R),permute(R,T).

%?-permute([a,b,c,d],L),write(L).

sublist(S,L):-append(_,L1,L),append(S,_,L1).

%?-sublist([b,c],[a,b,c,d]).

function(1, [X|_], X).
function(N, [_|T], X) :- N1 is N - 1, function(N1, T, X).

%?- function(5,[a,b,c,d,t,g],X).

function1(N, L, X) :- append(Y, [X|_], L),N1 is N-1,length(Y, N1).

%?- function1(5,[a,b,c,d,t,g],X).

geom([X,Y,Z|T]) :-!, (X*Z) =:= (Y*Y), geom([Y,Z|T]).
geom(_).

%?- geom([2,4,8,16,32]).
%?- geom([2,4,8,14,32]).

geom1([X,Y,Z|T]) :-!, (X*Z) =:= (Y*Y), remove(X, [X,Y,Z|T], R), geom1(R).
geom1(_).

%?- geom1([2,4,8,16,32]).
%?- geom1([2,4,8,14,32]).

