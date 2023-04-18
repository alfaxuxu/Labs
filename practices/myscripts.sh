#!/bin/bash

#This is comment

whoami ; cal ; date

echo ------------------

#Извлечение вывода команды в переменную
current_dir=$(pwd)
echo $current_dir


echo ------------------

var=5
#Не интерпретируется
echo 'I will take $var on exam'
#Интерпретируется
echo "I will take $var on exam"
#Символ '\' - экранирование
echo "I will take \$var on exam"
#Без ковычек
echo I will take $var on exam

echo ----------------

#Метематические операции
sum=$((5+5))
echo $sum
pow=$((sum*2))
echo $pow

echo ----------------

#Сравнение чисел в bash
# -eq ==
# -ge >=
# -gt >
# -le <=
# -lt <
# -ne !=

#Сравнение строк в bash
# = строки полностью одинаковы
# != строки не одинаковы
# \< (в конструкции [] + использовать двойные ковычки) или < (в конструкции [[]]) первая меньше второй в лексикографическом смысле
# \> (в конструкции [] + использовать двойные ковычки) или > (в конструкции [[]]) первая больше второй в лексикографическом смысле
# -n длина строки больше нуля
# -z длина строки равна нулю

#if-then-elif-else
#Сравнение чисел
if [ $var -eq 5 ] || [ $var -eq 4 ]
then
echo 'success'
elif [ $var -eq 3 ]
then
echo 'okey'
else
echo 'bad!'
fi

echo

#Сравнение строк
user='root'
if [ $user = $USER ]
then
echo 'correct user'
else
user=$USER
fi

echo

s1='abcd'
s2='xyz'
if [ "$s1" \< "$s2" ]
# [ $s1 < $s2 ] или [ "$s1" < "$s2" ] или [ $s1 \< $s2 ] привели бы к неверному ответу
then
echo $s1 меньше $s2
else
echo $s1 больше $s2
fi

if [[ $s1 < $s2 ]]
then
echo $s1 меньше $s2
else
echo $s1 больше $s2
fi

echo

s3=''
if [ -n "$s3" ]
# [ -n $s3 ] привело бы к неверному ответу
then
echo 'длина строки не равна 0'
else
echo 'длина строки равна 0'
fi

echo -------------------

#Цикл for
#Простой цикл со списком различных параметров
for var in 'Hello world' 20 $current_dir
do
echo $var
done

echo

#Взаимодействие с файловой системой
#Проверка файлов
# -d существует ли файл и является ли он директорией
# -е существует ли файл
# -f существует ли файл и является ли он файлом
# -r существует ли файл и доступен ли для чтения
# -w существует ли файл и доступен ли для записи
# -x существует ли файл и является ли исполняемым
# -s существует ли файл и не пустой ли он
# -nt новее ли file1 чем file2
# -ot старше ли file1 чем file2
# -O существует ли файл и является ли его владельцем текущий пользователь
# -G существует ли файл и принадлежит ли он группе текущего пользователя

for file in /home/admuser/*
do
if [ -d "$file" ]
then
echo $file $'\t' is a directory
elif [ -f "$file" ]
then
echo $file $'\t' is a file
fi
done

echo

#Взаимодействие с файловой системой и внутренними командами
file="test.txt"
for var in $(cat $file)
do
echo $var
done

echo

#Цикл в стиле С
for (( i=1; i <= 5; i++ ))
do
echo $i
done

echo

#Цикл while
var=5
while [ $var -gt 0 ]
do
echo $var
var=$(($var - 1))
done

echo

#Вложенные циклы
for (( i=1; i<10; i++ ))
do
for (( j=1; j<10; j++ ))
do
echo -n $(($i*$j)) $'\t'
done
echo $'\n'
done

echo --------------------

#Обработка ключей командной строки
while [ -n "S1" ] #Пока в качестве коючей что-то есть
do
case "$1" in
-h) echo 'Это простой скрипт для ознакомления с bash' ;;
-f) param_file="$2"
cat $param_file
shift ;;
#shift - сдвиг всех параметров на одну позицию влево (при этом стоящий первым безвозвратно теряется)
#-- отделяет ключи от параметиров, соответственно после этого символа завершается обработка ключей и начинается обработка параметров
--) shift 
break ;;
*) echo "$1 is not an option" ;;
esac
shift
done

echo ------------------

#Работа с параметрами
#Название файла - нулевой параметр (по умолчанию)
echo $0

echo

#Передаваемые параметры
echo 'Первый параметр:' $1
echo 'Второй параметр:' $2
echo 'Сумма:' $(($1+$2))

echo

#Проверка параметров
if [ -n "${!#}" ]
then
echo 'Hello' ${!#}
else
echo 'No parameters found!'
fi

echo

# $# - текущее кол-во параметров
echo You entered $# paremeters
# ${!#} - последний параметр
echo Your last entered paremeter is ${!#}

echo
# $@ - список текущих параметров пословно (удобно для перебора циклом)
for var in "$@"
do
echo $var
#shift
done

echo

# $* - все текущие параметры одной строкой
if [ -n "$*" ]
then
echo $*
else
echo 'no one parameters'
fi

echo --------------------


#read - ввод пользователем с клавиатуры
# -p несколько вводимых переменных
read -p 'Enter your full name: ' first_name last_name
echo "Hello $first_name $last_name!"

# -s скрывает ввод
# -t ограничение ввода по времени
#Если не указывать переемнную, то введенные данные будут записаны во временную переменую REPLY
if read -t 5 -s -p 'Enter password: '
then
echo
echo 'loading...'
sleep 3 #Искусственное торможение
if [ $REPLY = 'Pa$$w0rd' ]
then
echo 'Success!'
else
echo 'Fail!'
fi
else
echo 'Sorry, too slow!'
fi

echo --------------------

#Ввод и вывод
#0 - поток ввода
#1 - поток вывода
#2 - поток ошибок

#Перенаправление потока вывода в файл correct_file.txt
ls -l /home/admuser/ 1> correct_file.txt
#Перенаправление потока ошибок (обращение к несуществующему файлу) в файл error_file.txt
ls -l /home/a_dir/ 2> error_file.txt
#Комбинированное перенаправление потоков вывода и ошибок в один файд output_error_file.txt
ls -l /home/admuser/Рабочий\ стол/ /home/b_dir/ &> output-error_file.txt

#Постоянное перенаправление потока ошибок с помощью exec
exec 2>>error_file.txt
ls -l /home/c_dir/

#Перенаправление потока ввода (Ввод не с клавиатуры, а из файла)
exec 0< test.txt
while read line
do
echo $line
done




cp myscript.sh $current_dir/myscript.txt

