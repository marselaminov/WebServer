# WebServer - nginx implementation

1) make<br>
2) ./webserv<br>
   Second argument is optional. You can choose one of configuration files from "configs" folder.<br><br>
   For example:<br>
   ./webserv configs/default.conf (Simple website - http://localhost:7000 and Autoindex implementation - http://localhost:9000(delete subject and checklist when starting autoindex))<br>
   ./webserv configs/tester.conf (launch tester - http://localhost:5000)<br>
3) to test webserver use:<br>
   - run program with test config (./werbserv configs/tester.conf)<br>
   - bash tester/tester<br>
<br><br>
<p align="center">
  АЛГОРИТМ РАБОТЫ ВЕБСЕРВЕРА
  <br>
  <img src="https://www.4stud.info/web-programming/img/cgi.gif" width="80%">
  <br>
</p>
<br><br>
​    Для тестирования работы вебсервера в качестве клиентов использовались:

* Браузер (Google Chrome, Safari и пр)
* Postman (Инстурмент для отправки HTTP-запросов и тестирования API)
* JMeter(Apache JMeter) (Программа для нагрузочного тестирования сервера)

​    В данной реализации требовалось сделать возможным обработку собственного конфигурационного файла, для запуска нескольких серверов на разных IP-адресах с различными параметрами:

* Прослушиваемый порт (listen)
* Имя сервера (server_name)
* Максимальный размер тела HTTP-запроса (client_max_body_size)
* Индексные файлы (index)
* Автоиндекс (autoindex)
* Каталоги (location)
* Префиксный путь (root)
* Доступные методы (allowed_method)
* Страница ошибки (error_page)
* Параметры интерфеса общего шлюза (CGI) - cgi_path, cgi_index, cgi_extension
