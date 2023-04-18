#!/bin/bash

#This is comment

whoami ; cal ; date

echo ------------------

#���������� ������ ������� � ����������
current_dir=$(pwd)
echo $current_dir


echo ------------------

var=5
#�� ����������������
echo 'I will take $var on exam'
#����������������
echo "I will take $var on exam"
#������ '\' - �������������
echo "I will take \$var on exam"
#��� �������
echo I will take $var on exam

echo ----------------

#�������������� ��������
sum=$((5+5))
echo $sum
pow=$((sum*2))
echo $pow

echo ----------------

#��������� ����� � bash
# -eq ==
# -ge >=
# -gt >
# -le <=
# -lt <
# -ne !=

#��������� ����� � bash
# = ������ ��������� ���������
# != ������ �� ���������
# \< (� ����������� [] + ������������ ������� �������) ��� < (� ����������� [[]]) ������ ������ ������ � ������������������ ������
# \> (� ����������� [] + ������������ ������� �������) ��� > (� ����������� [[]]) ������ ������ ������ � ������������������ ������
# -n ����� ������ ������ ����
# -z ����� ������ ����� ����

#if-then-elif-else
#��������� �����
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

#��������� �����
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
# [ $s1 < $s2 ] ��� [ "$s1" < "$s2" ] ��� [ $s1 \< $s2 ] ������� �� � ��������� ������
then
echo $s1 ������ $s2
else
echo $s1 ������ $s2
fi

if [[ $s1 < $s2 ]]
then
echo $s1 ������ $s2
else
echo $s1 ������ $s2
fi

echo

s3=''
if [ -n "$s3" ]
# [ -n $s3 ] ������� �� � ��������� ������
then
echo '����� ������ �� ����� 0'
else
echo '����� ������ ����� 0'
fi

echo -------------------

#���� for
#������� ���� �� ������� ��������� ����������
for var in 'Hello world' 20 $current_dir
do
echo $var
done

echo

#�������������� � �������� ��������
#�������� ������
# -d ���������� �� ���� � �������� �� �� �����������
# -� ���������� �� ����
# -f ���������� �� ���� � �������� �� �� ������
# -r ���������� �� ���� � �������� �� ��� ������
# -w ���������� �� ���� � �������� �� ��� ������
# -x ���������� �� ���� � �������� �� �����������
# -s ���������� �� ���� � �� ������ �� ��
# -nt ����� �� file1 ��� file2
# -ot ������ �� file1 ��� file2
# -O ���������� �� ���� � �������� �� ��� ���������� ������� ������������
# -G ���������� �� ���� � ����������� �� �� ������ �������� ������������

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

#�������������� � �������� �������� � ����������� ���������
file="test.txt"
for var in $(cat $file)
do
echo $var
done

echo

#���� � ����� �
for (( i=1; i <= 5; i++ ))
do
echo $i
done

echo

#���� while
var=5
while [ $var -gt 0 ]
do
echo $var
var=$(($var - 1))
done

echo

#��������� �����
for (( i=1; i<10; i++ ))
do
for (( j=1; j<10; j++ ))
do
echo -n $(($i*$j)) $'\t'
done
echo $'\n'
done

echo --------------------

#��������� ������ ��������� ������
while [ -n "S1" ] #���� � �������� ������ ���-�� ����
do
case "$1" in
-h) echo '��� ������� ������ ��� ������������ � bash' ;;
-f) param_file="$2"
cat $param_file
shift ;;
#shift - ����� ���� ���������� �� ���� ������� ����� (��� ���� ������� ������ ������������ ��������)
#-- �������� ����� �� �����������, �������������� ����� ����� ������� ����������� ��������� ������ � ���������� ��������� ����������
--) shift 
break ;;
*) echo "$1 is not an option" ;;
esac
shift
done

echo ------------------

#������ � �����������
#�������� ����� - ������� �������� (�� ���������)
echo $0

echo

#������������ ���������
echo '������ ��������:' $1
echo '������ ��������:' $2
echo '�����:' $(($1+$2))

echo

#�������� ����������
if [ -n "${!#}" ]
then
echo 'Hello' ${!#}
else
echo 'No parameters found!'
fi

echo

# $# - ������� ���-�� ����������
echo You entered $# paremeters
# ${!#} - ��������� ��������
echo Your last entered paremeter is ${!#}

echo
# $@ - ������ ������� ���������� �������� (������ ��� �������� ������)
for var in "$@"
do
echo $var
#shift
done

echo

# $* - ��� ������� ��������� ����� �������
if [ -n "$*" ]
then
echo $*
else
echo 'no one parameters'
fi

echo --------------------


#read - ���� ������������� � ����������
# -p ��������� �������� ����������
read -p 'Enter your full name: ' first_name last_name
echo "Hello $first_name $last_name!"

# -s �������� ����
# -t ����������� ����� �� �������
#���� �� ��������� ����������, �� ��������� ������ ����� �������� �� ��������� ��������� REPLY
if read -t 5 -s -p 'Enter password: '
then
echo
echo 'loading...'
sleep 3 #������������� ����������
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

#���� � �����
#0 - ����� �����
#1 - ����� ������
#2 - ����� ������

#��������������� ������ ������ � ���� correct_file.txt
ls -l /home/admuser/ 1> correct_file.txt
#��������������� ������ ������ (��������� � ��������������� �����) � ���� error_file.txt
ls -l /home/a_dir/ 2> error_file.txt
#��������������� ��������������� ������� ������ � ������ � ���� ���� output_error_file.txt
ls -l /home/admuser/�������\ ����/ /home/b_dir/ &> output-error_file.txt

#���������� ��������������� ������ ������ � ������� exec
exec 2>>error_file.txt
ls -l /home/c_dir/

#��������������� ������ ����� (���� �� � ����������, � �� �����)
exec 0< test.txt
while read line
do
echo $line
done




cp myscript.sh $current_dir/myscript.txt

