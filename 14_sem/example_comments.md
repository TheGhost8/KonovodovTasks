#### First example

Пусть есть большой map со сложными ключами, которые непросто сравнивать между собой. Тогда, если мы знаем, где есть элемент с похожим ключом, то можно дать итератор на него и поиск места для вставки по красно-чёрному дереву пройдёт быстрее.

Ключи в этом примере простые, и тем не менее видно ускорение в 10 раз при добавлении подсказки на элемент недалеко.


#### Second example

Пусть так же есть map со сложными ключами и нам нужно вставить много элементов. Но у нас нет подсказки. Тогда можно сохранить возвращаемое значение первой вставки и использовать его как подсказку.
