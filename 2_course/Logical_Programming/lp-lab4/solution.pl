person('Даша').

object('шоколад').
object('деньги').

member(X,[X|L]).
member(X,[L|T]) :- member(X,T).

:-op(200, xfy, ':').

find(Verb, New_verb, Verb_inf, File):-
  member(X, File),
  condition(Verb, New_verb, Verb_inf, X).

condition(Verb, New_verb, Verb_inf, New_verb:Verb_inf:List):-
  member(Verb, List).

gen_verb(File):-
  File=[
  'любить':verb_inf('неинф'):['люблю','любишь','любит','любим','любят','любил','любила', 'любили'],
  'лежать':verb_inf('неинф'):['лежу','лежишь','лежит','лежим','лежат','лежал', 'лежали']
  ].

verb(New_verb, Verb_inf, Verb):-
  gen_verb(File),
  find(Verb, New_verb, Verb_inf, File).

splitting([],_,_).
splitting([X|Y],Y,X).

split(Q,Question,Verb,Word):-
    splitting(Q,X,Question), 
    splitting(X,Y,Verb),
    splitting(Y,Z,Word).

an_q(Q,X):-
    split(Q, Question, Verb, Word),
    Question == 'Что', person(Word),
    verb(New_verb, verb_inf('неинф'), Verb),
    concat(New_verb,"(agent(",Y),
    concat(Y,Word,Z),
    concat(Z,"),object(Y)).",X).

an_q(Q,X):- 
  split(Q, Question, Verb, Word),
  Question == 'Кто', object(Word), 
  verb(New_verb, verb_inf('неинф'), Verb), 
  concat(New_verb, "(agent(Y), object(", Y),
  concat(Y, Word, Z),
  concat(Z, ")).", X).

an_q(Q,X):-
    split(Q, Question, Verb, Word), 
    Question == 'Где', object(Word),
    verb(New_verb, verb_inf('неинф'), Verb),
    concat(New_verb,"(object(",Y),
    concat(Y,Word,Z),
    concat(Z,"),loc(X)).",X).
