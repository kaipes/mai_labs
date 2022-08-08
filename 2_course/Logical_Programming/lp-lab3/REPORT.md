#№ Отчет по лабораторной работе №3
## по курсу "Логическое программирование"

## Решение задач методом поиска в пространстве состояний

### студент: Каширин К.Д.

## Результат проверки

| Преподаватель     | Дата         |  Оценка       |
|-------------------|--------------|---------------|
| Сошников Д.В. |              |               |
| Левинская М.А.|    23.12     |        5      |

> *Комментарии проверяющих (обратите внимание, что более подробные комментарии возможны непосредственно в репозитории по тексту программы)*


## Введение
Пространство состояний возникает при разбиении решения задачи на отдельные шаги. Здесь выделяется начальное состояние, когда мы еще не выбрали гипотезу, а также конечное состояние, когда мы нашли гипотезу, которая является допустимым решением нашей задачи. Поиск в пространстве состояний можно свести к поиску в графе, где каждое возможное состояние будет являться вершиной, а дуги будут задаваться правилами перехода из одного состояния в другое. 

Prolog отлично подойдет для решения таких задач, поскольку в нем очень удобно описать граф путем перечисления всех друг в виде пар вершин или при помощи правил.
В отличие от императивных языков, где задание графа происходит в матричном предствалении, задание графа таким путем гибкое , поскольку это позволяет нам описывать очень сложные и большие графы, для которых матричное представление нерационально и вообще не всегда возможно.. 

## Задание

Крестьянину нужно переправить волка, козу и капусту с левого берега реки на правый. Как это сделать за минимальное число шагов, если в распоряжении крестьянина имеется двухместная лодка, и нельзя оставлять волка и козу или козу и капусту вместе без присмотра человека.

## Принцип решения

В условии задания описано главное правило: нельзя, чтобы волк оставался с козой или коза с капустой на одном берегу без присмотра человека. Опишем это правило:
```prolog
rule([Human, Wolf, Goat, Cabbage]):- 
	not(((Wolf == Goat), Wolf \= Human)), 
	not(((Goat == Cabbage), Goat \= Human)).
```

Обозначение, что кто-то переправился:
```prolog
shipping(L, R) :-
	(L == left, R = right);
	(L == right, R = left).
```

Далее я реализовал предикаты, которые меняют принадлежность элементов к берегу(левый или правый), а именно перенаправление человека в одиночку, перенаправление человека с волком, перенарпавление человека с капустой, перенаправление человека с козой. Ниже приведен пример кода перенаправления человека с капустой. Для значений `Human` и `Cabbage` мы меняем значение на противоположный берег, проверяем удовлетворяет ли такая перестановка предикату rule . Значений для `Wolf` и `Goat` оставляем прежние. Аналогично, реализую остальные предикаты с другими участниками(волком, козой, в одиночку).
```prolog
ship([Human, Wolf, Goat, Cabbage], [Human_new, Wolf_new, Goat_new, Cabbage_new]):-
	shipping(Human, Human_new), 
	shipping(Cabbage, Cabbage_new),
	rule([Human_new, Wolf, Goat, Cabbage_new]),
	Wolf_new = Wolf, 
	Goat_new = Goat.
```

Предикат поиска в ширину(обход элементов графа, расположенных на одном уровне; по числу итераций алгоритм поиска в ширину не будет прешивать число итераций алгоритма поиска в глубину, но при этом алгоритм является не эффективным по памяти, но при этом гарантирует наикратчайший путь к решению)):
```prolog
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
```

Предикат поиска в длину(рекурсивно проходим вглубь в дерево, пока не дойдем до конца, после алгоритм возвращается на предыдущие вершины до тех пор, пока необработает все листы):
```prolog
search_in_depth(Begin, Finish):-
	get_time(T),
	depth([Begin], Finish, Ans),
	invers(Ans),
	get_time(TT),
	Time is TT - T,
	write('Work time: '), write(Time), write(" seconds"), nl, !.
	#format('~f sec', Time), nl, !.

depth([Finish|T], Finish, [Finish|T]).
depth(List, Finish, Result):-
    add_obj(List, LList),
    depth(LList, Finish, Result).
```

Предикат поиска с итеративным погружением(совместное использование поиска в длину и в ширину; алгоритм поиска с итеративным погружением - это поиск в ширину, но при этом углубление происходит на количество элементов, равное числу итераций, а не на один элемент):
```prolog
search_iter(Begin, Finish):-
	get_time(T),
	count(Limit),
	deeper([Begin], Finish, Ans, Limit), invers(Ans),
	get_time(TT),
	Time is TT - T,
        write('Work time: '), write(Time), write(" seconds"), nl, !.

count(1).
count(A):-
	count(B),
	X is Y + 1.

deeper([Finish|T], Finish, [Finish|T], 0).
deeper(List, Finish, ResList, N):-
	N @> 0, add_obj(List, NewList), N1 is N - 1, deeper(NewList, Finish, ResList, N1).
``` 

## Результаты

Результат поиска в ширину:
```prolog
?- search_in_width([left,left,left,left],[right,right,right,right]).
Human: left, Wolf: left, Goat: left, Cabbage: left
Human: right, Wolf: left, Goat: right, Cabbage: left
Human: left, Wolf: left, Goat: right, Cabbage: left
Human: right, Wolf: right, Goat: right, Cabbage: left
Human: left, Wolf: right, Goat: left, Cabbage: left
Human: right, Wolf: right, Goat: left, Cabbage: right
Human: left, Wolf: right, Goat: left, Cabbage: right
Human: right, Wolf: right, Goat: right, Cabbage: right
Work time 0.0005841255187988281 seconds
true.
```

Результат поиска в длину:
```prolog
?- search_in_depth([left,left,left,left],[right,right,right,right]).
Human: left, Wolf: left, Goat: left, Cabbage: left
Human: right, Wolf: left, Goat: right, Cabbage: left
Human: left, Wolf: left, Goat: right, Cabbage: left
Human: right, Wolf: right, Goat: right, Cabbage: left
Human: left, Wolf: right, Goat: left, Cabbage: left
Human: right, Wolf: right, Goat: left, Cabbage: right
Human: left, Wolf: right, Goat: left, Cabbage: right
Human: right, Wolf: right, Goat: right, Cabbage: right
Work time: 0.0002887248992919922 seconds
true.
```

Результат поиска с итеративным погружением:
```prolog
?- search_iter([left,left,left,left],[right,right,right,right]).
Human: left, Wolf: left, Goat: left, Cabbage: left
Human: right, Wolf: left, Goat: right, Cabbage: left
Human: left, Wolf: left, Goat: right, Cabbage: left
Human: right, Wolf: right, Goat: right, Cabbage: left
Human: left, Wolf: right, Goat: left, Cabbage: left
Human: right, Wolf: right, Goat: left, Cabbage: right
Human: left, Wolf: right, Goat: left, Cabbage: right
Human: right, Wolf: right, Goat: right, Cabbage: right
Work time: 0.0007176399230957031 seconds
true.

```

| Алгоритм поиска |  Длина найденного первым пути  |  Время работы                                |
|-----------------|--------------------------------|----------------------------------------------|
| В глубину       |         8                      |         0.0005841255187988281 секунд         |
| В ширину        |         8                      |         0.000288724899291992   секунд        |
| ID              |         8                      |         0.0007176399230957031 секунд         |

## Выводы

Данная лабораторная работа познакомила меня с тремя алгоритмами поиска: в глубину, в ширину и с итеративным погружением и помогла применить эти алгоритма для решения задач на языке Prolog. На мой взгляд наиболее простой в реализации на языке Prolog - это поиск в глубину.

Определенный алгоритм поиска лучше всего подходит под определенный вид задачи. Выбор алгоритма поиска зависит также от цели. Если существует ограничение по памяти, то безопаснее использовать поиск в глубину, а если требуется наикратчайший путь, то лучше использовать поиск в ширину. В моей задачи все алгоритма поиска справились корректно, но поиск в ширину оказался быстрее. Однако разница по времени между двумя другими алгоритмами незначительным.





