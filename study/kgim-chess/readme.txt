ФИО: Толстошеев Иван Андреевич
Группа: 322

Задание: 2 / Шахматы

Работа с изображениями simple [+]
Работа также с изображениями medium [+]
Работа также с изображением maniac [+]
Выделения связных областей путем последовательного сканирования [+]
Математическая морфология [+]
Коррекция контрастности [+]
Фильтр шумоподавления [+]

Система: kdevelop,QT4,C++ (в Windows QT4 и MinGW)
ОС: Windows.
Аппаратура: Core Duo T2250 1.83 GHz, 1G RAM, GeForceGo 7300.

Комментарии:

Алгоритм: 
методом интегральных прекций находим доску. После этого "разбиваем" ее
на квадратики, не влючающие границы клеток(черные полоски). Если нужно, делается автоконтраст (в случае если дипазаон яркостей меньше 128).
Делаем average фильтр, если был автоконтраст. После этого делаем медианный.
После этого строится общая гистограмма "по клеточкам". На ней находим 2
пика - правый из них принадлежит белым клеткам, а левый черным клеткам. Все что 
выше правого пика и ниже левого - это фигуры и шум.
Убираем шум открытием и закрытием, затем находим связные области площадью больше
100 пикселей. Это фигуры. Считаем для каждой экстранситет и компактность. Выясняем
их тип.

Интерфейс:
Интерфейс сделан в классическом стиле. Для того чтобы посмотреть как работуют все
фильтры по очереди нужно выбрать Proceed->Proceed image by step.

Примечание:
исходный код класса ImageProcessor полность написан мной, тогда как
код класса ImageViewer переписан заново с одноименного примера QT.

