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

<img width="267" height="213" alt="image" src="https://github.com/user-attachments/assets/cb6f559a-ebba-4ae0-a407-3de2a65bbd43" />


### Посещение
<img width="463" height="132" alt="image" src="https://github.com/user-attachments/assets/2b4b0b6a-ed83-4510-a1cb-42efdf749245" />

### Поиск
<img width="509" height="92" alt="image" src="https://github.com/user-attachments/assets/aa8be811-3031-4f9e-ae5a-a1dc2a3bb666" />


### Навигация вперед/назад
<img width="465" height="87" alt="image" src="https://github.com/user-attachments/assets/6321aff6-a2e7-44b1-aaa2-b46982036d24" />
<img width="469" height="92" alt="image" src="https://github.com/user-attachments/assets/e9956d15-df19-47c9-9730-bd797b83839b" />


### Сохранение в Base-64
<img width="528" height="53" alt="image" src="https://github.com/user-attachments/assets/1961639e-4686-4417-a575-6e985cf2d360" />
<img width="298" height="45" alt="image" src="https://github.com/user-attachments/assets/76704c37-1460-4f9e-8826-da3cfbd2db4d" />


###Загрузка из Base-64

<img width="486" height="156" alt="image" src="https://github.com/user-attachments/assets/7ef84fca-3ed5-4be0-a32c-b3d0277c33fa" />
