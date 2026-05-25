# Лабороторная работа №2
## Браузерная история
Реализована система хранения истории браузера

Каждая запись содержит
- URL страницы
- дату и время посещения
- флаг закладки

Реализовано
- Навигация "назад вперед"
- отчистка истории
- поиск по домену
- просмотр истории за заданный период времени
- загрузка и истории  Base64-файла
  
## Использовался двусвязный список
### Основные преимущества
1. Двусвязный список удобен для реализации переходов назад и вперед, так как каждый элемент хранит ссылки и на предыдущую, и на следующую страницу.
2. Добавление и удаление страниц выполняется быстро, без смещения остальных элементов структуры.
3. Двусвязный список хорошо подходит для хранения истории браузера, потому что позволяет легко удалять “будущую” историю после перехода назад и открытия новой страницы.

## Пример работы
### Меню

<img width="505" height="35" alt="image" src="https://github.com/user-attachments/assets/bebed335-6906-4866-807d-4a18cccf170c" />



### Посещение
<img width="487" height="163" alt="image" src="https://github.com/user-attachments/assets/ea30c764-b887-45f6-b47b-1cb643194228" />


### Поиск
<img width="494" height="159" alt="image" src="https://github.com/user-attachments/assets/5cef81e3-c7d2-4b4d-be1e-5493ec51ddd9" />



### Навигация вперед/назад
<img width="491" height="90" alt="image" src="https://github.com/user-attachments/assets/ef0c49c9-b4f6-4302-8a93-309c1732b884" />

<img width="497" height="91" alt="image" src="https://github.com/user-attachments/assets/25f4ab82-2204-4278-b602-b27cbcfc1ac0" />



### Сохранение в Base-64
<img width="397" height="57" alt="image" src="https://github.com/user-attachments/assets/9a8c0667-b489-42fa-9977-d43cd8809fea" />

<img width="298" height="45" alt="image" src="https://github.com/user-attachments/assets/76704c37-1460-4f9e-8826-da3cfbd2db4d" />


###Загрузка из Base-64

<img width="485" height="145" alt="image" src="https://github.com/user-attachments/assets/a4072c65-5f21-423c-992a-39d3841abf87" />

