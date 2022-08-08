:- ['my_tree.pl'].
 
brother_in_law(X, Husband) :-
  child(Wife, Parent), child(X, Parent), 
  child(R, Wife), child(R, Husband), 
  X\= Husband,
  male(X).