% Place your solution here
% Борисов, Кириллов, Данин и Савин инженеры. Один из них автомеханик, другой химик, третий строитель, четвертый радиотехник. 
% Борисов, который обыгрывает в шахматы Данина, но проигрывает Савину, бегает на лыжах лучше того инженера, который моложе его, 
% и ходит в театр чаще, чем тот инженер, который старше Кириллова. Химик, который посещает театр чаще, чем автомеханик, но реже,
% чем строитель, не является ни самым молодым, ни самым старшим из этой четверки. Строитель, который на лыжах бегает хуже, чем радиотехник,
% как правило, проигрывает в шахматных сражениях автомеханику. Самый пожилой из инженеров лучше всех играет в шахматы и чаще всех бывает в театре, 
% а самый молодой лучше всех ходит на лыжах. Назовите профессии каждого из инженеров, если известно, что ни в спорте, ни в приверженности к театру
% среди нет двух одинаковых.
begin(A,[A,_,_,_]).
medium(B,[_,B,_,_]).
medium(C,[_,_,C,_]).
end(D,[_,_,_,D]).

% X раньше (старше/быстрее/чаще посещает театр/играет в шахматы лучше) Y
before(X,Y,[X|Z]):-
    member(Y,Z).
before(X,Y,[_|Z]):-
    before(X,Y,Z).

solve(Engineers):-
    Engineers = [man(A, Aprof), man(B, Bprof), man(C, Cprof),  man(D, Dprof)],
    ['Борисов','Кириллов','Данин','Савин']=[A, B, C, D],
    permutation(['Aвтомеханик','Радиотехник','Химик','Строитель'],[Aprof, Bprof, Cprof, Dprof]),
    
    permutation(Engineers,Age),
    member(Engineer1, Engineers),
    before(man('Борисов', _), Engineer1, Age),
    medium(man(_,'Химик'),Age),
    end(Young, Age),
    begin(Elderly,Age),

    permutation(Engineers,Chess),
    begin(Elderly,Chess),
    before( man('Борисов', _),man('Данин', _), Chess),
    before(man('Савин', _),man('Борисов', _),  Chess),
    before(man(_, 'Aвтомеханик'), man(_, 'Строитель'),  Chess),

    permutation(Engineers, Ski),
    begin(Young, Ski),
    before(man(_, 'Радиотехник'), man(_, 'Строитель'), Ski),
    before(man('Борисов', _), Somebody1, Ski),

    permutation(Engineers, Theatre),
    begin(Elderly,Theatre),
    member(Engineer2, Engineers),
    before(man('Борисов', _), Engineer2,  Theatre),
    before(Engineer2, man('Кириллов', _), Age),
    before(man(_, 'Химик'), man(_, 'Aвтомеханик'), Theatre),
    before(man(_, 'Строитель'),  man(_, 'Химик'), Theatre).
