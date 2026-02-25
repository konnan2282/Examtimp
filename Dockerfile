# В качестве исходного образа взять ubuntu (используем 20.04 для совместимости с qt5-default)
FROM ubuntu:20.04

# Разместить информацию об авторе как метку
LABEL author="Demidov_241326"

# Переменные окружения для предотвращения интерактивных запросов при установке tzdata
ENV TZ=Europe/Moscow
ENV DEBIAN_FRONTEND=noninteractive

# Установить модули для компиляции qt
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update
RUN apt-get install qt5-default -y
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake -y
RUN apt-get install build-essential -y

# Создать директорию для проекта
# Замените <Surname_group> на вашу фамилию и группу, например Ivanov_123
WORKDIR /Ivanov_123

# Скопировать файлы проекта в контейнер
COPY . .

# Скомпилировать проект в файл с именем hallServer
RUN qmake hallServer.pro && make

# Точка входа (запуск сервера)
# Для работы сервера порт должен быть открыт
EXPOSE 33333
CMD ["./hallServer"]