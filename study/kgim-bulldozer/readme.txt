ФИО: Толстошеев Иван Андреевич
Группа: 322

Задание №4/OpenGL: Интерактивная анимация (Бульдозер)

Обязательная часть задания [+]
Объекты нетривиальной формы [+]
Зеркальная площадка [-]
Зеркало на бульдозере [-]
Сферическое текстурирование на бульдозере [-]
Тени на площадке [-]
Тени на площадке и объектах [-]
Мягкие тени [-]
Режим с ручным управлением бульдозером с клавиатуры/мыши - [+]
Управление камерой с помощью клавиатуры/мыши [+]
Реалистичность геометрии моделей [+]
Усложненное физическое моделирование [+]
Площадка сложной формы (по высоте) [+]

Cистема: kdevelop+Qt4+ODE
ОС: GNU/Linux 2.6.22.12-0.1-default (Opensuse 10.3)
Аппаратура: Core Duo T2250 1.83 GHz, 1G RAM, GeForceGo 7300.

Коментарии: 

Управление бульдозером осуществляется с помощью стрелочек на клавиатуре и
с помощью клавиш A и D (поворот на месте). Имеется две камеры переключаться
между ними можно использую клавишы 0 и 1. Положение камеры 0 управляется мышью.
(зажатые первая вторая или третья кнопка и колесико). Положение камеры 1 управляется
клавишами W и S. Для того чтобы перейти в ручной режим управления бульдозером, нужно
нажать I. Для перехода в автоматический режим нужно нажать пробел. Для того чтобы
появлялис сложные объекты нужно нажать C (toggle) . Не рекомендую использовать
сложные объекты в автоматическом режиме. Кнопкой Q можно включить/выключить показ
осей координат.

Программа написана с использованием библиотеки ODE. Инога при работе в автоматическом
режиме возможны глюки - но бульдозер все равно справляется с задачей за разумное
время